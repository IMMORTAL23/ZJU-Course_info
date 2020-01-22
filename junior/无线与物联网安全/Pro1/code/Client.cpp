#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <openssl/md5.h>
#include <pthread.h>
#define BUFFSIZE 100
#define MAX_RAMDOM_NUM 1000
#define MAX_KEY_LEN 20
#define random(x) (rand()%x)
using namespace std;
int Nonce = 0;
pthread_t tid;
int sockfd;
unsigned char TK[17]={0};
struct package{
    int Anonce;
    char ACK[30];
    int r;
};
void Xor(char* plain, char* key,char* cipher)
{
    int i=0;
    for(i=0;i<16;i++){
        cipher[i] = plain[i] ^ key[i];
    }
}
void GenerateKey(char* Nonce,unsigned char* TK,unsigned char* key)
{
    char MAC[20]="00:0c:29:c5:22:90";
    char IV[30]={0};
    strcpy(IV,MAC);
    strcat(IV,Nonce);
    char tmp[BUFFSIZE]={0};
    strcpy(tmp,IV);
    strcat(tmp, (char*)TK);
    //printf("%s\n",tmp);
    MD5((unsigned char*)tmp, strlen(tmp), key);
}
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
/*int to char */
void int2char(int num, char * q)
{
    int n=0;
    sprintf(q, "%d", num);
    while(num=num/10) n++;
    n++;
    q[n] = '\0';
}
void* func(void *args)
{
    char * key = (char *)args;
    while (true)
    {
        struct package b;
	    memset(&b,0,sizeof(b));
        int len=recv(sockfd,(char *)&b,sizeof(b),0);
        int Anonce,r;
        if(len>0){
            if(!strcmp(b.ACK,""))//pac1
            {
                
                Anonce = b.Anonce;
                r = b.r;
                printf("RECV: the first handshake\n");
                printf("r      = %d\n",b.r);
                printf("Anonce = %d\n\n",b.Anonce);
                int CNonce = random(MAX_RAMDOM_NUM);
                char MasterKey[MAX_KEY_LEN];
                strcpy(MasterKey,key);
                char ANonce_chr[MAX_KEY_LEN],CNonce_chr[MAX_KEY_LEN];
                int2char(Anonce,ANonce_chr);
                int2char(CNonce,CNonce_chr);
                char tmp[BUFFSIZE];
                strcpy(tmp,ANonce_chr);
                strcat(tmp,CNonce_chr);
                strcat(tmp,MasterKey);
                MD5((unsigned char*)tmp, strlen(tmp), TK);
                send(sockfd,&CNonce,sizeof(CNonce),0);
                send(sockfd,&r,sizeof(r),0);
                printf("SEND: the second handshake\n");
                printf("r      = %d\n",r);
                printf("Cnonce = %d\n\n",CNonce);
            }
            else // pac2
            {
                //static int flag = 0;
                r = b.r;
                printf("RECV: the third handshake\n");
                printf("r      = %d\n",r);
                printf("%s\n",b.ACK);
                //if (flag == 1){
                    send(sockfd,"Completed!\n",strlen("Completed!\n"),0);
                    send(sockfd,&r,sizeof(r),0);
                printf("SEND: the final handshake\n");
                printf("r      = %d\n",r);
                printf("ACK = Completed!\n\n");
                //}
                //flag = 1;
                Nonce = 0; // reinitial the Nonce
            }
            
        }
    }
}
/*
Client 程序接收四个命令行参数： 
1. 目标 AP 的 IP 地址。 
2. 目标 AP 的端口。 
3. 目标 AP 的密码 (MasterKey)。 
4. 需要传递的数据（文本文档，与 Client 程序在同一目录下）。 
例如，如果程序命名为 Client, 则启动命令如下  ./Client 192.168.0.35 1234 z3dg35dg Packet.txt 
*/
int main(int argc, char *argv[])
{
    if (argc !=5)
    {
        printf("the input is invalid!\n");
        return -1;
    }
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket() failed!\n");
        return -1;
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  //具体的IP地址
    serv_addr.sin_port = (atoi(argv[2]));           //端口
    bzero(&(serv_addr.sin_zero), 8);
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        printf("connect() failed!\n");
        close(sockfd);
        return -1;
    }
    printf("Connected and the sockfd is %d\n",sockfd);
    srand((int)time(0));
    char buf[BUFFSIZE];
    //begin to handshake
    int len=send(sockfd,"request",strlen("request"),0); 
    if(len <= 0) {printf("1. send request failed.\n"); return -1;}
	
	//start a thread to recv the message from AP
    pthread_create(&tid, NULL, func, (void *)argv[3]);
    
	
	// begin to transfer the data
	FILE* fp;
    if((fp = fopen(argv[4],"r"))==NULL){
        printf("Can't open the file!\n");
        exit(1);
    }
	
    sleep(4);
        char plain[17]={0};
        while(1)
        {
            unsigned char key[16];
            fgets(plain,17,(FILE*)fp);
            if(feof(fp)) break;
            char Noncechar[10]={0};
            int2char(Nonce,Noncechar);
            GenerateKey(Noncechar,TK, key);
            char cipher[16]={0};
            Xor(plain, (char*)key, cipher);
            unsigned char hexcipher[33]={0};
            unsigned char hexkey[33]={0};
            dump_hex((unsigned char*)cipher,16,hexcipher);
            dump_hex((unsigned char*)key,16,hexkey);
            printf("-------Nonce = %d ----------\n",Nonce);
            printf("Plaintext  = %s\n", plain);
            printf("Ciphertext = %s\n", hexcipher);
            printf("Key = %s\n\n",hexkey);
            send(sockfd,cipher,16,0);
            Nonce++;
            sleep(1);
        }
    send(sockfd,"end",strlen("end"),0);//send "end" as a end label

    fclose(fp);
    
}
