#include <stdio.h>
#include <string.h>

#if 2147483647L+1L == -2147483648L
typedef unsigned long ulong32;
#else
typedef unsigned int ulong32;
#endif

//#pragma comment(lib, "aes.lib")

/*
以下函数的源代码已删除, 这些函数经编译后生成的机器码已转移到aes.lib内:
void aes_polynomial_mul(unsigned char x[4], unsigned char y[4], unsigned char z[4]);
void ByteSubInverse(unsigned char *p, int n);
void ShiftRowInverse(unsigned char *p);
void MixColumnInverse(unsigned char *p, unsigned char a[4], int do_mul);
void aes_decrypt(unsigned char *bufin, unsigned char *bufout, unsigned char *key);
请对本程序(MyAes.c)做以下修改:
(1) 重写上述函数
(2) 删除#pragma comment(lib, "aes.lib")
要求:
(1) 除sbox外, 函数中不可以查其它表来代替计算
(2) 修改后的程序必须能正常编译运行
(3) 运行产生的输出结果与本程序一致
*/

unsigned int aes_8bit_mul_mod_0x101(unsigned int x, unsigned int y);
unsigned int aes_8bit_mul_mod_0x11B(unsigned int x, unsigned int y);
unsigned int aes_8bit_inverse(unsigned int x);
void aes_polynomial_mul(unsigned char x[4], unsigned char y[4], unsigned char z[4]);
unsigned int get_msb_mask(unsigned int x);
void rol_a_row(unsigned char *p, int n);
void shr_a_row(unsigned char *p, int n);
void ror_a_row(unsigned char *p, int n);
void get_column(unsigned char *p, int j, int r, unsigned char *q);
void put_column(unsigned char *p, unsigned char *q, int j, int r);

void build_sbox(void);
void build_sbox_inverse(void);
void ByteSub(unsigned char *p, int n);
void ByteSubInverse(unsigned char *p, int n);
void ShiftRow(unsigned char *p);
void ShiftRowInverse(unsigned char *p);
void MixColumn(unsigned char *p, unsigned char a[4], int do_mul);
void MixColumnInverse(unsigned char *p, unsigned char a[4], int do_mul);
void AddRoundKey(unsigned char *p, unsigned char *k);
void aes_init(void);
int  aes_set_key(unsigned char *seed_key, int bits,  unsigned char *key);
void aes_encrypt(unsigned char *bufin, unsigned char *bufout, unsigned char *key);
void aes_decrypt(unsigned char *bufin, unsigned char *bufout, unsigned char *key);

unsigned char sbox[256];
unsigned char sbox_inverse[256];
int key_rounds = 0;


unsigned int aes_8bit_mul_mod_0x101(unsigned int x, unsigned int y)
{
   /* 利用农夫算法求 x * y mod (X^8 + 1); */
   /*      8         0
          X         X
      n = 1 0000 0001 = 0x101
    */
   unsigned int p = 0; /* the product of the multiplication */
   int i;
   for (i=0; i < 8; i++)
   {
      if (y & 1) /* if y is odd, then add the corresponding y to p */
         p ^= x; /* since we're in GF(2^m), addition is an XOR */
      y >>= 1;   /* equivalent to y/2 */
      x <<= 1;   /* equivalent to x*2 */
      if (x & 0x100) /* GF modulo: if x >= 256, then apply modular reduction */
         x ^= 0x101; /* XOR with the primitive polynomial x^8 + 1 */
                     /* Actually, it's is the same as ROL. Commented by Black White. */
   }
   return p;
}

unsigned int aes_8bit_mul_mod_0x11B(unsigned int x, unsigned int y)
{
   /* 利用农夫算法求 x * y mod (X^8 + X^4 + X^3 + X + 1);
      关于农夫算法请参考:
      (1) https://en.wikipedia.org/wiki/Rijndael_Galois_field
      (2) https://en.wikipedia.org/wiki/Multiplication_algorithm
    */
   /*
           8    4 3 10
          X    X X XX
      n = 1 0001 1011 = 0x11B
    */
   unsigned int p = 0; /* the product of the multiplication */
   int i;
   for (i=0; i < 8; i++)
   {
      if (y & 1) /* if y is odd, then add the corresponding y to p */
         p ^= x; /* since we're in GF(2^m), addition is an XOR */
      y >>= 1;   /* equivalent to y/2 */
      x <<= 1;   /* equivalent to x*2 */
      if (x & 0x100) /* GF modulo: if x >= 256, then apply modular reduction */
         x ^= 0x11B; /* XOR with the primitive polynomial x^8 + x^4 + x^3 + x + 1 */

   }
   return p;
}

unsigned int get_msb_mask(unsigned int x)
{
   /* 计算x最高位(最多5位)的掩码:
      如x=0x0A, 则其最高位掩码=0x08;
      如x=0x1D, 则其最高位掩码=0x10;
      aes_8bit_inverse()需要调用本函数
    */
   unsigned int mask = 0x100;
   while(mask !=0 && (mask & x) == 0)
   {
      mask >>= 1;
   }
   return mask;
}

unsigned int aes_8bit_inverse(unsigned int x)
{
   /*      -1      8   4    3
      计算x   mod X + X  + X  + X + 1
      以下x求逆过程用的是扩展欧几里德算法(extended Euclidian algorithm);
      扩展欧几里德算法的证明及步骤请参考教材p.93及p.94;
    */
   /*      8    4 3 10
          X    X X XX
      n = 1 0001 1011 = 0x11B
    */
   unsigned int a1=1, b1=0, a2=0, b2=1;
   unsigned int q, r, t, n, nmask, xmask, shift;
   n = 0x11B; /* 设n为被除数 */
   r = x;     /* x为除数 */
   while(r != 0)
   {
      q = 0;
      nmask = get_msb_mask(n);
      xmask = get_msb_mask(x);
      do
      {
         shift = 0;
         while(xmask < nmask)
         {
            xmask <<= 1;
            shift++;
         }
         if(xmask == nmask)
         {
            q |= 1 << shift; /* q为商 */
            n ^= x << shift; /* n = n - (x << shift);
                                根据有限域GF(2^8)的减法规则,
                                这里的减法不可以产生借位, 所以用异或代替
                              */
         }
         nmask = get_msb_mask(n);
         xmask = get_msb_mask(x);
      } while(n != 0 && nmask >= xmask);
      r = n;

      t = a1;
      a1 = a2;
      a2 = t ^ aes_8bit_mul_mod_0x11B(q, a2); /* a2 = a1 - q*a2; */
      t = b1;
      b1 = b2;
      b2 = t ^ aes_8bit_mul_mod_0x11B(q, b2); /* b2 = b1 - q*b2; */
      n = x;
      x = r;
   }
   return b1;
}


void build_sbox(void)
{
   /* 计算sbox:
      设a∈[0,255], 则
                   -1                8
      sbox[a] = ((a   *  0x1F) mod (X + 1)) ^ 0x63;

               -1
      其中a * a   = 1 mod (X^8+X^4+X^3+X+1);
   */
   int i;
   for(i=0; i<256; i++)
   {
      sbox[i] = aes_8bit_mul_mod_0x101(aes_8bit_inverse(i), 0x1F) ^ 0x63;
   }
}

void build_sbox_inverse(void)
{
   /* 根据sbox生成sbox反查表 */
   int i, j;
   for(i=0; i<256; i++)
   {
      for(j=0; j<256; j++)
      {
         if(sbox[j] == i)
            break;
      }
      sbox_inverse[i] = j;
   }
}

void aes_init(void)
{
   /* 生成sbox及sbox反查表 */
   build_sbox();
   build_sbox_inverse();
}

int aes_set_key(unsigned char *seed_key, int bits,  unsigned char *key)
{
   /* 根据种子密钥生成真正密钥:
      128bit种子密钥(16字节): 生成(1+10)*4个long32, step=4, loop=10
      192bit种子密钥(24字节): 生成(1+12)*4个long32, step=6, loop=8
      256bit种子密钥(32字节): 生成(1+14)*4个long32, step=8, loop=7
    */
   int i, j, step, loop;
   ulong32 *pk;
   if(seed_key == NULL || key == NULL)
      return 0;
   if(bits == 128)      /* 16字节种子密钥 */
   {
      key_rounds = 10;  /* 加密或解密需要做10轮循环 */
      step = 4;         /* 生成密钥的循环步长为4个long32 */
      loop = 10;        /* 生成密钥需要做10次循环 */
   }
   else if(bits == 192) /* 24字节种子密钥 */
   {
      key_rounds = 12;  /* 加密或解密需要做12轮循环 */
      step = 6;
      loop = 8;
   }
   else if(bits == 256) /* 32字节种子密钥 */
   {
      key_rounds = 14;  /* 加密或解密需要做14轮循环 */
      step = 8;
      loop = 7;
   }
   else
   {
      key_rounds = 0;
      step = 0;
      return 0;
   }
   memcpy(key, seed_key, bits/8);
   pk = (ulong32 *)(key + 4*step);
   for(i=step; i<step+step*loop; i+=step)
   {
      unsigned int r;
      /* 假定生成的密钥k是long32类型的数组, i是其下标,
         则当i!=0 && i%step==0时, k[i]在计算时必须做以
         下特殊处理:
       */
      pk[0] = pk[-1];
      rol_a_row(key+i*4, 1);
      ByteSub(key+i*4, 4);
      r = 1 << ((i-step) / step);
      if(r <= 0x80)
         r = aes_8bit_mul_mod_0x11B(r, 1);
      else
         r = aes_8bit_mul_mod_0x11B(r/4, 4);
      key[i*4] ^= r;
      pk[0] ^= pk[-step];

      for(j=1; j<step; j++) /* i+j是密钥k的下标, 当(i+j)%step != 0时, */
      {                     /* k[i+j]只需做简单的异或处理 */
         if(step == 6 && i == step*loop && j>=step-2 ||
            step == 8 && i == step*loop && j>=step-4)
            break; /* 128-bit key does not need to discard any steps:
                      4 + 4*10 - 0= 4+40 = 44 == 4+4*10
                      192-bit key should discard last 2 steps:
                      6 + 6*8 - 2 = 4+48 = 52 == 4+4*12
                      256-bit key should discard last 4 steps:
                      8 + 8*7 - 4 = 4+56 = 60 == 4+4*14
                    */
         if(step == 8 && j == 4) /* 对于256bit密钥, 当(i+j)%4==0时需做特殊处理 */
         {
            ulong32 k;
            k = pk[3];
            ByteSub((unsigned char *)&k, 4); /* k = scrambled pk[3] */
            pk[4] = k ^ pk[4-8];
         }
         else /* 当(i+j)%step != 0时, k[i+j]只需做以下异或处理 */
            pk[j] = pk[j-step] ^ pk[j-1];
      }
      pk += step;
   } /* for(i=step; i<step+step*loop; i+=step) */
   return 1;
}


void AddRoundKey(unsigned char *p, unsigned char *k)
{
   /* 把p所指向的4*4明文矩阵与k所指向的4*4密钥矩阵做异或运算:
      p -> 4byte * 4byte matrix
      k -> 4byte * 4byte key
    */
   ulong32 *pp, *kk;
   int i;
   pp = (ulong32 *)p;
   kk = (ulong32 *)k;
   for(i=0; i<4; i++)
   {
      pp[i] ^= kk[i];
   }
}

void ByteSub(unsigned char *p, int n)
{
   /* 把p所指向的n字节替换成sbox中的值 */
   int i;
   for(i=0; i<n; i++)
   {
      p[i] = sbox[p[i]];
   }
}

void ByteSubInverse(unsigned char *p, int n)
{
   /* 把p所指向的n字节替换成sbox反查表中的值 */
   int i;
   for(i=0; i<n; i++)
   {
      p[i] = sbox_inverse[p[i]];
   }
}

void rol_a_row(unsigned char *p, int n)
{
   /* 把p所指向的4个字节循环左移n个字节 */
   int i;
   unsigned char t;
   for(i=0; i<n; i++)
   {
      t = p[0];
      memcpy(p, p+1, 3);
      p[3] = t;
   }
}

void shr_a_row(unsigned char *p, int n)
{
   /* 把p所指向的4个字节右移n个字节 */
   int i, j;
   for(i=0; i<n; i++)
   {
      for(j=3; j>=1; j--)
      {
         p[j] = p[j-1];
      }
      p[0] = 0;
   }
}

void ror_a_row(unsigned char *p, int n)
{
   /* 把p所指向的4个字节循环右移n个字节 */
   int i, j;
   unsigned char t;
   for(i=0; i<n; i++)
   {
      t = p[3];
      for(j=3; j>=1; j--)
      {
         p[j] = p[j-1];
      }
      p[0] = t;
   }
}


void ShiftRow(unsigned char *p)
{
   /* 对p所指向的4*4矩阵做逐行循环左移操作:
      第0行: 不移动;
      第1行: 左移1字节
      第2行: 左移2字节
      第3行: 左移3字节
    */
   int i;
   for(i=1; i<4; i++)
   {
      rol_a_row(p+i*4, i);
   }
}
void ShiftRowInverse(unsigned char *p)
{
   /* 对p所指向的4*4矩阵做逐行循环右移操作:
      第0行: 不移动;
      第1行: 右移1字节
      第2行: 右移2字节
      第3行: 右移3字节
    */
   int i;
   for(i=1; i<4; i++)
   {
      ror_a_row(p+i*4, i);
   }
}



void get_column(unsigned char *p, int j, int r, unsigned char *q)
{
   /* 从p所指向的4*4矩阵m中提取第j列, 结果是4个unsigned char, 保存到q中;
      参数r指定第j列4个元素中的首元素所在行号, 例如get_column(p, 3, 3, q)
      提取的是: m[3][3], m[0][3], m[1][3], m[2][3]
    */
   int i;
   for(i=0; i<4; i++)
   {
      q[i] = p[(r+i)%4*4+j];
   }
}

void put_column(unsigned char *p, unsigned char *q, int j, int r)
{
   /* 把p所指向4个unsigned char保存到q所指矩阵m中的第j列;
      参数r指定第j列4个元素中的首元素所在行号, 例如put_column(p, q, 2, 2)
      保存的是: m[2][2], m[3][2], m[0][2], m[1][2]
    */
   int i;
   for(i=0; i<4; i++)
   {
      q[(r+i)%4*4+j] = p[i];
   }
}

void MixColumn(unsigned char *p, unsigned char a[4], int do_mul)
{
   /* (1) 对p指向的4*4矩阵m中的4列做乘法运算;
      (2) 这里的乘法是指有限域GF(2^8)多项式模(X^4+1)乘法,具体步骤请参考教材p.61及p.62;
      (3) aes加密时采用的被乘数a为多项式3*X^3 + X^2 + X + 2, 用数组表示为
          unsigned char a[4]={0x03, 0x01, 0x01, 0x02};
      (4) aes解密时采用的被乘数a为加密所用多项式的逆, 即{0x0B, 0x0D, 0x09, 0x0E};
      (5) 矩阵m中的4列按以下顺序分别与a做乘法运算:
          第0列: 由m[0][0], m[1][0], m[2][0], m[3][0]构成
          第3列: 由m[1][3], m[2][3], m[3][3], m[0][3]构成
          第2列: 由m[2][2], m[3][2], m[0][2], m[1][2]构成
          第1列: 由m[3][1], m[0][1], m[1][1], m[2][1]构成
      (6) 乘法所得4列转成4行, 保存到p中, 替换掉p中原有的矩阵;
      (7) do_mul用来控制是否要做乘法运算, 加密最后一轮及解密第一轮do_mul=0;
    */
   unsigned char b[4];
   unsigned char t[4][4];
   int j;
   for(j=0; j<4; j++)
   {
      get_column(p, (4-j)%4, j, b); /* 从p所指矩阵m(明文矩阵)中提取第j列, 保存到数组b中;
                                       第j列首元素的行号为j:
                                       column 0: 0 1 2 3
                                       column 3: 1 2 3 0
                                       column 2: 2 3 0 1
                                       column 1: 3 0 1 2
                                     */
      if(do_mul) /* 在加密最后一轮以及解密第一轮的MixColumn步骤中不需要做乘法; */
         aes_polynomial_mul(a, b, b); /* 其余轮都要做乘法: b = a*b mod (X^4+1); */
      memcpy(t[j], b, 4); /* 把乘法所得结果复制到t中第j行 */
   }
   memcpy(p, t, 4*4); /* 复制t中矩阵到p, 替换掉p中原有矩阵 */
}


void aes_encrypt(unsigned char *bufin, unsigned char *bufout, unsigned char *key)
{
   int i;
   unsigned char a[4] = {0x03, 0x01, 0x01, 0x02}; /* 定义多项式3*X^3+X^2+X+2 */
   unsigned char matrix[4][4];
   memcpy(matrix, bufin, 4*4); /* 复制明文16字节到matrix */
   AddRoundKey((unsigned char *)matrix, key); /* 第0轮只做AddRoundKey() */
   for(i=1; i<=key_rounds; i++)
   {  /* 第1至key_rounds轮, 做以下步骤: ByteSub, ShiftRow, MixColumn, AddRoundKey */
      ByteSub((unsigned char *)matrix, 16);
      ShiftRow((unsigned char *)matrix);
      if(i != key_rounds)
         MixColumn((unsigned char *)matrix, a, 1); /* do mul */
      else
         MixColumn((unsigned char *)matrix, a, 0); /* don't mul */
      AddRoundKey((unsigned char *)matrix, key+i*(4*4));
   }
   memcpy(bufout, matrix, 4*4); /* 密文复制到bufout */
}

main()
{
   unsigned char seed_key[3][100] = 
   {
      "0123456789ABCDEF", /* 16 bytes */
      "0123456789ABCDEF012345678", /* 24 bytes */
      "0123456789ABCDEF0123456789ABCDEF" /* 32 bytes */
   };
   int key_size[3] = {128, 192, 256};
   unsigned char key[(56+4)*4]; /* 128bit: 40+4, 192bit: 48+4, 256bit: 56+4 */
   unsigned char plaintext[100] = "A Quick BrownFox";
   unsigned char ciphertext[100];
   int i, k;
   char buf[100];
   aes_init(); /* 计算sbox及sbox反查表 */
   for(k=0; k<3; k++)
   {
      printf("Encrypting by using %d-bit seed_key...\n", key_size[k]);
      printf("plaintext=%s\n", plaintext);
      printf("seed_key=%s\n", seed_key[k]);
      aes_set_key(seed_key[k], key_size[k], key);
                                       /* 把128位即16字节种子密钥转化成176字节密钥 */
                                       /* 192位(24字节)及256位(32字节)种子密钥设置:
                                          aes_set_key(seed_key, 192, key);
                                          aes_set_key(seed_key, 256, key);
                                        */
      aes_encrypt(plaintext, ciphertext, key); /* aes加密 */
      for(i=0; i<16; i++)
      {
         sprintf(buf+i*2, "%02X", ciphertext[i]);
      }
      printf("ciphertext=%s\n", buf);
      /* 128-bit密钥产生的密文: C037F19D4AEA8E7172B176B9D4CE1D62
         192-bit密钥产生的密文: F51C8DD5F7052264650126DC70D402F5
         256-bit密钥产生的密文: 2687C0D61E803718F6D11A0384C81229
       */
      puts("Decrypting...");
      aes_decrypt(ciphertext, plaintext, key); /* aes解密 */
      printf("plaintext=%s\n", plaintext);
     puts("==========================================");
   }
   return 1;
}

void aes_polynomial_mul(unsigned char x[4], unsigned char y[4], unsigned char z[4]){
   //x[4] = {0x03, 0x01, 0x01, 0x02}    高次系数在x[0]
   unsigned char temp[4] = {0};
   unsigned char multipulicant[4][4];
   int j ;
   for(int i=0; i<4 ; i++){
      for(j=0;j<4;j++){
         multipulicant[i][j] = x[j];
      }
      rol_a_row(multipulicant[i],3-i);
   }
   for(int i=0;i<4;i++){
      for(j=0;j<4;j++){
         temp[i] ^= aes_8bit_mul_mod_0x11B(multipulicant[i][j],y[j]);
      }
   }
   memcpy(z,temp,4);
}

void MixColumnInverse(unsigned char *p, unsigned char a[4], int do_mul){
   unsigned char b[4];
   unsigned char t[4][4];
   int j;
   for(j=0; j<4; j++)
   {
      memcpy(b , j*4+p , 4);//从密文矩阵中取出一行赋值给b
      if(do_mul) /* 在加密最后一轮以及解密第一轮的MixColumn步骤中不需要做乘法; */
         aes_polynomial_mul(a, b, b);
      put_column(b, (unsigned char*)t, (4-j)%4, j); 
   }
   memcpy(p, t, 4*4); /* 复制t中矩阵到p, 替换掉p中原有矩阵 */
}

void aes_decrypt(unsigned char *bufin, unsigned char *bufout, unsigned char *key){
   int i;
   unsigned char a[4] = {0x0b, 0x0d, 0x09, 0x0e}; /* 定义多项式3*X^3+X^2+X+2 */
   unsigned char matrix[4][4];
   memcpy(matrix, bufin, 4*4); /* 复制密文16字节到matrix */
   
   for(i=key_rounds; i>=1; i--)
   {  /* 第1至key_rounds轮, 做以下步骤: ByteSub, ShiftRow, MixColumn, AddRoundKey */
      AddRoundKey((unsigned char *)matrix, key+i*(4*4));
      if(i != key_rounds)
         MixColumnInverse((unsigned char *)matrix, a, 1); /* do mul */
      else
         MixColumnInverse((unsigned char *)matrix, a, 0); /* don't mul */
      ShiftRowInverse((unsigned char *)matrix);
      ByteSubInverse((unsigned char *)matrix, 16);
   }
   AddRoundKey((unsigned char *)matrix, key); /* 第0轮只做AddRoundKey() */
   memcpy(bufout, matrix, 4*4); /* 明文复制到bufout */
}