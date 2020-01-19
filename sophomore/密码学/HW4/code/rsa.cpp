// rsa.cpp : Defines the entry point for the console application.
/* 
padding modes:
#define RSA_PKCS1_PADDING	1
#define RSA_SSLV23_PADDING	2
#define RSA_NO_PADDING		3
#define RSA_PKCS1_OAEP_PADDING	4
#define RSA_X931_PADDING	5

RSA_PKCS1_PADDING	至少保留11字节用于填充
RSA_PKCS1_OAEP_PADDING 至少保留42字节用于填充
RSA_public_encrypt()的最后参数表示填充方式, 例如
RSA_PKCS1_PADDING方式，如果要加密"ABCDE"，则填充
后的明文如下：
00,02,8个字节随机数,0,"ABCDE"
如果要加密"AB"，则填充后的明文如下：
00,02,11个字节随机数,0,"AB"
其中填充的各个字节随机数值都≠0。
RSA_public_encrypt()的第1个参数表示明文字节长度。
当采用RSA_PKCS1_PADDING填充方式时，函数的第1个参
数值<=RSA_size(prsa)-11，其中RSA_size(prsa)返回
密钥N的字节长度，对于128位密钥，此函数返回16。
当采用RSA_NO_PADDING填充方式时，函数的第1个参数
值必须=RSA_size(prsa)

*/

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/md5.h> 
#include <openssl/sha.h> 
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")

#define N "FF807E694D915875B13F47ACDDA61CE11F62E034150F84660BF34026ABAF8C37"//256 bits big number
#define E "010001"//public key
#define D "45AEF3CB207EAD939BBDD87C8B0F0CFCC5A366A5AF2AC5FE1261D7547C625F51"//private key

/*输入密文字符，将它们转为两个16进制数*/
void dump_hex(unsigned char *p, int n, unsigned char *q)
{
   int i;
   for(i=0; i<n; i++)
   {
      sprintf((char *)&q[i*2], "%02X", p[i]);
   }
   q[i*2] = '\0';
}
/*输入两个16进制数，将它们转为对应ASCII的字符*/
void scan_hex(unsigned char *p, int n, unsigned char *q)
{
   int i;
   for(i=0; i<n; i++)
   {
      sscanf((char *)&p[i*2], "%02X", &q[i]);
   }
}

void swap(unsigned char* A, unsigned char* B){
	unsigned char temp = *A;
	*A = *B;
	*B = temp;
}
/*将两个输入进行异或输出到第二个参数中*/
void xor(unsigned char IV[], unsigned char bufin[]){
	int i;
	for (i=0;i<256;i++){
		bufin[i] = IV[i] ^ bufin[i];
	}
}

int main()
{
   unsigned char IV[] = "0123456789ABCDEFDEADBEEFBADBEAD!";//32bytes * 8bits
   unsigned char plaintext[] = 
   "01. A quick brown fox jumps over the lazy dog.\n" \
   "02. A quick brown fox jumps over the lazy dog.\n" \
   "03. A quick brown fox jumps over the lazy dog.\n";
   printf("Plaintext= \n");
   puts((char*)plaintext);
   unsigned char ciphertext[300];
   unsigned char bufin[256];
   unsigned char bufout[256];
   int n,i;

   RSA *prsa;
   BIGNUM *pn, *pe, *pd;
   prsa = RSA_new();
   prsa->flags |= RSA_FLAG_NO_BLINDING; /* 在blinding模式下, 使用私钥加密或解密时都会
                                           使用公钥; 设置flags关闭blinding模式 */
   pn = BN_new();
   pe = BN_new();
   pd = BN_new();
   BN_hex2bn(&pn, N); /* N、E、D are in macro definition */
   BN_hex2bn(&pe, E);
   BN_hex2bn(&pd, D);

   /*==============公钥加密,NO_PADDING=================*/
   prsa->n = pn;
   prsa->e = pe;
   prsa->d = NULL;
   n = RSA_size(prsa); /* 返回N的字节数 n = 32*/
   int remain = strlen((const char *)plaintext) % n;//the last block's byte
   memset(bufin, 0, sizeof(bufin));
   puts("Encrypting...");
   printf("ciphertext=\n");
   int plainlen = strlen((const char *)plaintext);
   for(i=0; i < plainlen ; i+=n){
	   strncpy((char *)bufin, (char *)&plaintext[i], n);
	   if(i+n>plainlen) //最后一个明文块
			memset(bufin+remain, 0, sizeof(bufin)-remain);//在最后一块未填满处填入0x00
	   xor(IV,bufin);
	   n = RSA_public_encrypt(n, bufin, bufout, prsa, RSA_NO_PADDING);
	   memcpy(IV,bufout,n);
	   dump_hex(bufout, n, &ciphertext[2*i]);
   }
   //交换最后两块数据
   for(i = plainlen*2-2*n-2*remain ;i < plainlen*2-2*remain ; i++){
	   swap(&ciphertext[i],&ciphertext[i+2*n]);
   }
   ciphertext[plainlen*2] = '\0';//用'\0'截断密文
   printf("%s",ciphertext);
   printf("\n");
  /*================私钥解密,NO_PADDING=================*/
   
   puts("Decrypting...");
   prsa->e = NULL;
   prsa->d = pd;
   //decrypt the secod last block with ECB mode
   scan_hex(&ciphertext[2*plainlen - 2 * remain - 2 * n], n, bufin);
   memset(bufout, 0, sizeof(bufout));
   n = RSA_private_decrypt(n, bufin, bufout, 
       prsa, RSA_NO_PADDING);
   //modify the last cipher block
   unsigned char temp[512];
   dump_hex(bufout, n, temp);
   memcpy(&ciphertext[plainlen*2],temp+2*remain,2*n-2*remain);
   scan_hex(&ciphertext[2*plainlen - 2 * remain],n,bufin);
   xor(bufin,bufout);
   memcpy(&plaintext[2*plainlen-2*remain],bufout,n);
   //swap the blocks
   for(i = plainlen*2-2*n-2*remain ;i < plainlen*2-2*remain ; i++){
	   swap(&ciphertext[i],&ciphertext[i+2*n]);
   }
   //decrypt
   strncpy((char*)IV,"0123456789ABCDEFDEADBEEFBADBEAD!",n);
   for(i=0;i < plainlen-n ; i+=n){
		scan_hex(&ciphertext[2*i], n, bufin);
		memset(bufout, 0, sizeof(bufout));
		n = RSA_private_decrypt(n, bufin, bufout, 
		  prsa, RSA_NO_PADDING);
		xor(IV,bufout);
		memcpy(IV,bufin,n);
		strncpy((char*)&plaintext[i],(const char*)bufout,n);
   }
   
   plaintext[plainlen]='\0';
   printf("plaintext=\n");
   puts((char *)plaintext);
   puts("=================================================");

  /*================数字签名,md-5,sha-1=================*/
    //md-5
    unsigned char M1[17] = {0};//128bits
	unsigned char M1_hex[33] = {0};
    MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx,plaintext,plainlen);
    MD5_Final(M1,&ctx);
	printf("md5=\n");
	dump_hex(M1, 16, M1_hex);
	puts((char *)M1_hex);
	//sha -1 
	unsigned char M2[21] = {0};//160bits
	unsigned char M2_hex[41] = {0};
    SHA1(plaintext, plainlen, M2);
	printf("sha-1=\n");
	dump_hex(M2, 20, M2_hex);
	puts((char *)M2_hex);
	//md-5 + sha-1 
	unsigned char M[65] = {0};
	unsigned char M_hex[129] = {0};
	memcpy ((char*)M,(char*)M1,16);
	memcpy((char*)M+16,(char*)M2,20);
	strcpy ((char*)M_hex,(char*)M1_hex);
	strcat((char*)M_hex,(char*)M2_hex);
	printf("md5+sha-1=\n");
	puts((char*)M_hex);
	//encrypt with private key
	unsigned char signature[37] = {0};
	unsigned char signature_hex[73] = {0};
	plainlen = strlen((char*)M);
	remain = plainlen % n;
	prsa->n = pn;
	prsa->e = NULL;
	prsa->d = pd;
	n = RSA_size(prsa); /* 返回N的字节数 */
	memset(bufin, 0, sizeof(bufin));
	puts("Encrypting...");
	strncpy((char *)bufin, (char *)M, n);
	n = RSA_private_encrypt(n, bufin, bufout,prsa, RSA_NO_PADDING);//加密倒数第二个块
	memcpy(&signature[32],bufout, n);
	memcpy(&M[n+remain],&bufout[remain],n-remain);//填充密文的尾巴
	strncpy((char *)bufin, (char *)(M+n), n);
	n = RSA_private_encrypt(n, bufin, bufout,prsa, RSA_NO_PADDING);// 加密最后一个块
	memcpy(signature,bufout,n);
	M[n+remain]='\0';//截断
	printf("signature=\n");
	dump_hex(signature, 36, signature_hex);
	signature_hex[2*plainlen] = '\0';
	puts((char*)signature_hex);

	//decrypt with public key
	unsigned char M_decry[37] = {0};
	unsigned char M_decry_hex[73];
	prsa->e = pe;
	prsa->d = NULL;
	puts("Decrypting...");
	puts("plaintext=");
	memset(bufout, 0, sizeof(bufout));
	memset(M_decry_hex, 0, sizeof(M_decry_hex));
	n = RSA_public_decrypt(n, signature, bufout, prsa, RSA_NO_PADDING);
	memcpy((M_decry+n),bufout,n);
	memcpy((signature+n+remain),(bufout+remain),n-remain);
	strncpy((char *)bufin, (char *)(signature+n), n);
	n = RSA_public_decrypt(n, bufin, bufout, prsa, RSA_NO_PADDING);
	memcpy(M_decry,bufout,n);
	dump_hex(M_decry, 36, M_decry_hex);
	puts((char *)M_decry_hex);
	//比较两个字符串
	if(strcmp((char*)M_hex,(char*)M_decry_hex)) printf("Signature is correct.\n");
	RSA_free(prsa);
	system("pause");
   return 0;
}
