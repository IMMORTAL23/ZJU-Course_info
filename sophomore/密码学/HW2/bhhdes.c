/* Sofware DES functions
 * written 12 Dec 1986 by Phil Karn, KA9Q; large sections adapted from
 * the 1977 public-domain program by Jim Gillogly
 */
/* Those lines marked by [%] are added by Black White(iceman@zju.edu.cn)
   for more readability.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 2147483647L+1L == -2147483648L 
typedef long long32;
typedef unsigned long ulong32;
#else
typedef int long32;           /* In 64-bit systems, long may be 64-bit, */
typedef unsigned int ulong32; /* here we force it to be 32-bit. */
#endif

#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN
#endif

int  des_init(int mode);
void des_set_key(char *key);
void des_encrypt(char *block);
void des_decrypt(char *block);
void des_done(void);
static void sbox_output_perm_table_init(void);
static void perm_init(char perm[16][16][8], char p[64]);
static void permute(char *inblock, char perm[16][16][8], char *outblock);
static void forward_round(int num, ulong32 *block);
static void reverse_round(int num, ulong32 *block);
static long32 f(ulong32 r, unsigned char subkey[8]);

#ifdef LITTLE_ENDIAN
static ulong32 byteswap(ulong32 x);
#endif

/* Tables defined in the Data Encryption Standard documents */

/* initial permutation IP */
static char ip[64] = { /* [%] source Bit58-> target Bit1, Bit50->Bit2, ..., Bit7->Bit64 */
   58, 50, 42, 34, 26, 18, 10,  2,
   60, 52, 44, 36, 28, 20, 12,  4,
   62, 54, 46, 38, 30, 22, 14,  6,
   64, 56, 48, 40, 32, 24, 16,  8,
   57, 49, 41, 33, 25, 17,  9,  1,
   59, 51, 43, 35, 27, 19, 11,  3,
   61, 53, 45, 37, 29, 21, 13,  5,
   63, 55, 47, 39, 31, 23, 15,  7
};

/* final permutation IP^-1 */
static char fp[64] = { /* [%] source Bit1-> target Bit58, Bit2->Bit50, ..., Bit64->Bit7 */
   40,  8, 48, 16, 56, 24, 64, 32,
                        /* ^
                           7 */
   39,  7, 47, 15, 55, 23, 63, 31,
   38,  6, 46, 14, 54, 22, 62, 30,
   37,  5, 45, 13, 53, 21, 61, 29,
   36,  4, 44, 12, 52, 20, 60, 28,
   35,  3, 43, 11, 51, 19, 59, 27,
   34,  2, 42, 10, 50, 18, 58, 26,
     /* ^
       50 */
   33,  1, 41,  9, 49, 17, 57, 25
     /* ^
       58 */
};

/* expansion operation matrix
 * This is for reference only; it is unused in the code
 * as the f() function performs it implicitly for speed
 */
#ifdef notdef
static char plaintext_32bit_expanded_to_48bit_table[48] = 
{
   32,  1,  2,  3,  4,  5, /* [%] source Bit32->target Bit1 */
    4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13,
   12, 13, 14, 15, 16, 17,
   16, 17, 18, 19, 20, 21,
   20, 21, 22, 23, 24, 25,
   24, 25, 26, 27, 28, 29,
   28, 29, 30, 31, 32,  1 
};
#endif

/* permuted choice table (key) */
static char key_perm_table[56] = 
{
   57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
};

/* number left rotations of key_perm_table */
static char key_rol_steps[16] = 
{
   1,2,4,6,8,10,12,14,15,17,19,21,23,25,27,28  /* total steps to rotate left before this round */
/* 1,1,2,2,2,2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 ; steps to rotate left per round
   1 2 3 4 5 6  7  8  9  10 11 12 13 14 15 16; round number [%]
 */
};

/* permuted choice key (table) */
static char key_56bit_to_48bit_table[48] = /* [%] bit 9,18,22,25,35,38,43,54 are removed */
{
   14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
};

/* The (in)famous S-boxes */
static char sbox[8][64] = 
{
   /* S1 */
   14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
    0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
    4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
   15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,

   /* S2 */
   15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
    3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
    0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
   13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,

   /* S3 */
   10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
   13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
   13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
    1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,

   /* S4 */
    7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
   13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
   10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
    3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,

   /* S5 */
    2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
   14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
    4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
   11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,

   /* S6 */
   12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
   10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
    9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
    4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,

   /* S7 */
    4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
   13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
    1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
    6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,

   /* S8 */
   13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
    1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
    7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
    2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

/* 32-bit permutation function P used on the output of the S-boxes */
static char sbox_perm_table[32] = 
{   
   16,  7, 20, 21,
   29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2,  8, 24, 14,
   32, 27,  3,  9,
   19, 13, 30,  6,
   22, 11,  4, 25
};
/* End of DES-defined tables */

/* Lookup tables initialized once only at startup by des_init() */
static long32 (*sbox_output_perm_table)[64]; /*[%] 8 * 64 * long32:
                                                 8 = 8 boxes
                                                64 = 6-bit input
                                            long32 = scattered 32-bit output produced
                                                     from 4-bit original input
                                            */
static char (*iperm)[16][8]; /* Initial and final permutations */
static char (*fperm)[16][8]; /*[%] 16 * 16 * 8byte:
                                   16 = 16 Sections, 4 bits per section
                                   16 = 4-bit input
                                   8  = scattered 64-bit output produced 
                                        from 4-bit original input
                              */

/* 8 6-bit subkeys for each of 16 rounds, initialized by des_set_key() */
static unsigned char (*kn)[8];

/* bit 0 is left-most in byte */
static int bytebit[8] = 
{
/* bit0  bit1  bit2  bit3  bit4  bit5  bit6  bit7 */
   0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};

static int nibblebit[4] = 
{
   0x08, 0x04, 0x02, 0x01
};

static int des_mode;


/* Allocate space and initialize DES lookup arrays
 * mode == 0: standard Data Encryption Algorithm
 * mode == 1: DEA without initial and final permutations for speed
 * mode == 2: DEA without permutations and with 128-byte key (completely
 *            independent subkeys for each round)
 */
int des_init(int mode)
{
   if(sbox_output_perm_table != NULL)
   {
      /* Already initialized */
      return 1;
   }
   des_mode = mode;
   
   if((sbox_output_perm_table = (long32 (*)[64])malloc(sizeof(long32) * 8 * 64)) == NULL)
   {
      return 0;
   }
   sbox_output_perm_table_init();
   kn = (unsigned char (*)[8])malloc(sizeof(char) * 16 * 8);
   if(kn == NULL)
   {
      free((char *)sbox_output_perm_table);
      return 0;
   }
   if(mode == 1 || mode == 2)   /* No permutations */
      return 1;

   iperm = (char (*)[16][8])malloc(sizeof(char) * 16 * 16 * 8);
   if(iperm == NULL)
   {
      free((char *)sbox_output_perm_table);
      free((char *)kn);
      return 0;
   }
   perm_init(iperm, ip);

   fperm = (char (*)[16][8])malloc(sizeof(char) * 16 * 16 * 8);
   if(fperm == NULL)
   {
      free((char *)sbox_output_perm_table);
      free((char *)kn);
      free((char *)iperm);
      return 0;
   }
   perm_init(fperm, fp);   
   return 1;
}

/* Free up storage used by DES */
void des_done(void)
{
   if(sbox_output_perm_table == NULL)
      return;   /* Already done */
   free((char *)sbox_output_perm_table);
   free((char *)kn);
   if(iperm != NULL)
      free((char *)iperm);
   if(fperm != NULL)
      free((char *)fperm);
   sbox_output_perm_table = NULL;
   iperm = NULL;
   fperm = NULL;
   kn = NULL;
}

/* Set key (initialize key schedule array) */
void des_set_key(char *key) /* 64 bits (will use only 56) */
{
   char pc1m[56];      /* place to modify key_perm_table into */
   char pcr[56];       /* place to rotate key_perm_table into */
   register int i, j, b;
   int m;

   /* In mode 2, the 128 bytes of subkey are set directly from the
    * user's key, allowing him to use completely independent
    * subkeys for each round. Note that the user MUST specify a
    * full 128 bytes.
    *
    * I would like to think that this technique gives the NSA a real
    * headache, but I'm not THAT naive.
    */
   if(des_mode == 2)
   {
      for(i=0; i<16; i++) /*[%] i=round */
      {
         for(j=0; j<8; j++) /* 8-byte key per round */
         {
            kn[i][j] = *key++;
         }
      }
      return;
   }

   /* Clear key schedule */
   memset(kn, 0, 16*8);

   for (j=0; j<56; j++) /* convert key_perm_table to bits of key */
   {                    /* [%] j is the target bit number of key */
      b = key_perm_table[j] - 1;   /* integer bit location */
                                   /* [%] b is the source bit number of key, base 0 */
      m = b & 7;        /* [%] m = b % 8; */ /* find bit */ 

      pc1m[j]=(key[b>>3] & bytebit[m]) ? 1 : 0; /* find which key byte b is in */
                                                /* and which bit of that byte */
                                                /* and store 1-bit result */

   }
   for (i=0; i<16; i++) /* key chunk for each iteration */
   {  
      #if 0
      //---------------[%] Not easy to understand----------------
      // for (j=0; j<56; j++)   /* rotate key_perm_table the right amount */
      // {
      //    pcr[j] = pc1m[(b=j+key_rol_steps[i])<(j<28? 28 : 56) ? b: b-28];    
      //    /* rotate left and right halves independently */
      // }
      //---------------------------------------------------------
      #endif
      for(j=0; j<28; j++) /* [%] left half */
      {
         b = (j+key_rol_steps[i]) % 28;//利用数组来进行循环移位，pcr是结果，pclm是移位前的数组，key_rol_step为移位的位数
         pcr[j] = pc1m[b];
      }
      for(j=28; j<56; j++) /* [%] right half */
      {
         b = 28 + (j+key_rol_steps[i]-28) % 28;
         pcr[j] = pc1m[b];
      }

      for (j=0; j<48; j++) /* select bits individually */
      {                    /* [%] Select 48 bits from 56 bits.
                                  j is the target bit number, and 
                                  key_56bit_to_48bit_table[j]-1 is 
                                  the source bit number */
         /* check bit that goes to kn[j] */
         if (pcr[key_56bit_to_48bit_table[j]-1]) /* [%] pcr[key_56bit_to_48bit_table[j]-1] is SourceBit, j is TargetBit */
         {
            /* mask it in if it's there */
            b = j % 6;
            kn[i][j/6] |= bytebit[b] >> 2; /* [%] remove the trailing 2 bits
                                              j=0    1    2    3    4    5
                                     bytebit[b]=0x80 0x40 0x20 0x10 0x08 0x04
                                  bytebit[b]>>2=0x20 0x10 0x08 0x04 0x02 0x01
                                            */
         }
      } /* [%] for (j=0; j<48; j++) */
   } /* [%] for (i=0; i<16; i++) */
}


/* In-place encryption of 64-bit block */
void des_encrypt(char *block)
{
   register int i;
   ulong32 work[2];       /* Working data storage */
   long32 tmp;

   permute(block, iperm, (char *)work);   /* Initial Permutation */
#ifdef LITTLE_ENDIAN
   work[0] = byteswap(work[0]);
   work[1] = byteswap(work[1]);
#endif

   /* Do the 16 rounds */
   for (i=0; i<16; i++)
      forward_round(i, work);

   /* Left/right half swap */
   tmp = work[0];
   work[0] = work[1];   
   work[1] = tmp;

   /*
   L R
   R L'
   L' R' ==> R' L'
             L' R
             R  L ==> L R
    */

#ifdef LITTLE_ENDIAN
   work[0] = byteswap(work[0]);
   work[1] = byteswap(work[1]);
#endif

   permute((char *)work, fperm, block);   /* Inverse initial permutation */
}

/* In-place decryption of 64-bit block */
void des_decrypt(char *block)
{
   register int i;
   ulong32 work[2];   /* Working data storage */
   long32 tmp;

   permute(block, iperm, (char *)work);   /* Initial permutation */

#ifdef LITTLE_ENDIAN
   work[0] = byteswap(work[0]);
   work[1] = byteswap(work[1]);
#endif


   /* Do the 16 rounds in reverse order */
   for (i=15; i >= 0; i--)
      reverse_round(i, work);

   /* Left/right half swap */
   tmp = work[0];
   work[0] = work[1];   
   work[1] = tmp;


#ifdef LITTLE_ENDIAN
   work[0] = byteswap(work[0]);
   work[1] = byteswap(work[1]);
#endif

   permute((char *)work, fperm, block);   /* Inverse initial permutation */
}


/* Permute inblock with perm */
static void permute(char *inblock, char perm[16][16][8], char *outblock) 
{  /* result into outblock, 64 bits */
   register int i, j;
   register char *pin, *pout;      /* ptr to input or output block */
   register char *p, *q;

   if(perm == NULL)
   {
      /* No permutation, just copy */
      memcpy(outblock, inblock, 8);
      return;
   }

   /* Clear output block    */
   memset(outblock, 0, 8);

   pin = inblock;
   for (j = 0; j < 16; j += 2, pin++) /* [%] total 8 loops to permute 64 bits from inblock */
   { /* for each input nibble */
      pout = outblock;
      p = perm[j][(*pin >> 4) & 0x0F];
      q = perm[j + 1][*pin & 0x0F];
      for (i=0; i<8; i++) /* and each output byte */
      {   
         *pout++ |= *p++ | *q++; /* OR the masks together*/
      }
   }
}

/* Do one DES cipher round */
 /* i.e. the num-th one */
static void forward_round(int num, ulong32 *block)
{
   /* The rounds are numbered from 0 to 15. On even rounds
    * the right half is fed to f() and the result exclusive-ORs
    * the left half; on odd rounds the reverse is done.
    */
   if(num & 1)
   {
      block[1] ^= f(block[0], kn[num]);
   } 
   else 
   {
      block[0] ^= f(block[1], kn[num]);
   }
}

static void reverse_round(int num, ulong32 *block)
{
   /* The rounds are numbered from 15 to 0. On odd rounds
    * the right half is fed to f() and the result exclusive-ORs
    * the left half; on even rounds the reverse is done.
    */
   if(num & 1)
   {
      block[0] ^= f(block[1], kn[num]);
   } 
   else 
   {
      block[1] ^= f(block[0], kn[num]);
   }
}

/* The nonlinear function f(r, k), the heart of DES */
                /* 32 bits */  /* 48-bit key for this round */
static long32 f(ulong32 r, unsigned char subkey[8])
{
   register ulong32 rval, rt;
   /* Run E(R) ^ K through sbox_output_perm_table.
    * This code takes advantage of a convenient regularity in
    * E, namely that each group of 6 bits in E(R) feeding
    * a single S-box is a contiguous segment of R.
    */
   rt = (r >> 1) | ((r & 1) ? 0x80000000 : 0); /* [%] rt = ROR(rt, 1); */
   rval = 0;
   /*[%]
   //1 2 3 4 5 6 7 8 9 A B C D E F 10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20
   //20 1 2 3 4 5 6 7 8 9 A B C D E F 10 11 12 13 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F
   //           2       2       1        1           1           0           0
   //           6       2       8        4           0           6           2
   */
   rval |= sbox_output_perm_table[0][((rt >> 26) ^ *subkey++) & 0x3F];
   rval |= sbox_output_perm_table[1][((rt >> 22) ^ *subkey++) & 0x3F];
   rval |= sbox_output_perm_table[2][((rt >> 18) ^ *subkey++) & 0x3F];
   rval |= sbox_output_perm_table[3][((rt >> 14) ^ *subkey++) & 0x3F];
   rval |= sbox_output_perm_table[4][((rt >> 10) ^ *subkey++) & 0x3F];
   rval |= sbox_output_perm_table[5][((rt >> 6) ^ *subkey++) & 0x3F];
   rval |= sbox_output_perm_table[6][((rt >> 2) ^ *subkey++) & 0x3F];
   rt = (r << 1) | ((r & 0x80000000) ? 1 : 0); /* [%] rt = ROL(r, 1); 1C 1D 1E 1F 20 1 */
   rval |= sbox_output_perm_table[7][(rt ^ *subkey) & 0x3F];
   return rval;
}

/* initialize a perm array */
static void perm_init(char perm[16][16][8], char p[64]) /* 64-bit, either init or final */
{
   register int b, j, k;
   int i, m;

   /* Clear the permutation array */
   memset(perm, 0, 16*16*8);
   for(i=0; i<16; i++) /* [%] i=SectionNum, each section contains 4 bits; */ /* each input nibble position */
   {
      for(j=0; j<16; j++) /* [%] j=SectionValue varying from 0 to 15; */ /* each possible input nibble */
      {
         for(k=0; k<64; k++) /* [%] k=TargetBit; */ /* each output bit position */
         {  /* [%] check TargetBit k is concerned with SectionNum i and SectionValue j */
            b = p[k] - 1; /* [%] b=SourceBit; */ /* where does this bit come from */
            if ((b >> 2) != i) /* [%] b/4 != i means this bit does not lie in this section. */
               continue;  /* does it come from input posn? */ /* if not, bit k is 0 */
            if (!(j & nibblebit[b & 3]))
               continue;  /* [%] This bit is not equal to 1; */ /* any such bit in input? */
            /* [%] SourceBit b will result in setting TargetBit k to 1 */
            m = k & 7;  /* [%] m = k % 8; */ /* which bit is this in the byte */                                             
            perm[i][j][k>>3] |= bytebit[m]; 
         }
      }
   }
}

/* Initialize the lookup table for sbox's 6-bit input */
static void sbox_output_perm_table_init(void)
{
   char sbox_perm_table_inverse[32];
   int p, i, s, j, rowcol;
   long32 val;

   /* Compute sbox_perm_table_inverse, the inverse of sbox_perm_table.
    * This is easier to work with
    */
   for(p=0; p<32; p++) /* [%] p=SourceBit */
   {
      for(i=0; i<32; i++) /* [%] i=TargetBit */
      {
         if(sbox_perm_table[i]-1 == p) /* [%] sbox_perm_table[i] ranges within [1,32], so it is base 1, not base 0 */
         {
            sbox_perm_table_inverse[p] = i; /* [%] fill sbox_perm_table_inverse[p] with TargetBit=i */
            break;
         }
      }
   }

   for(s = 0; s < 8; s++) /* For each S-box */
   {
      for(i=0; i<64; i++) /* For each possible input */
      {      
         val = 0;
         /* The row number is formed from the first and last
          * bits; the column number is from the middle 4
          */
         rowcol = (i & 0x20) | ((i & 1) ? 0x10 : 0x00) | ((i >> 1) & 0x0F);
         /* [%] count of rows=4, count of columns=16 */
         /* [%] rowcol = row*16 + col */
         for(j=0; j<4; j++) /* For each output bit */
         {   
            if(sbox[s][rowcol] & nibblebit[j]) /* [%] check bit 0,1,2,3 */
            {
               /* [%] The element contained in sbox_perm_table_inverse is base 0;
                  And 0 stands for the left-most bit, while 31 means the right-most bit.
                  val |= 0x80000000UL >> sbox_perm_table_inverse[4*s + j]; 
                  The above statement is equivalent to the statement below:
                */
               val |= 1L << (31 - sbox_perm_table_inverse[4*s + j]); /* [%] 4*s+j is SourceBit
                                                     sbox_perm_table_inverse[4*s+j] is TargetBit
                                                     left to right: Bit0..Bit31
                                                   */
            }
         }
         sbox_output_perm_table[s][i] = val;
      }
   }
}

#ifdef   LITTLE_ENDIAN
/* Byte swap a long32 */
static ulong32 byteswap(ulong32 x)
{
   register char *cp, tmp;
   cp = (char *)&x;
   tmp = cp[3];
   cp[3] = cp[0];
   cp[0] = tmp;

   tmp = cp[2];
   cp[2] = cp[1];
   cp[1] = tmp;
   return x;
}
#endif

main()
{
   char mykey[]="ABCD1234";
   char p[]="abcdefgh";
   unsigned char c[9];
   int i;
   des_init(0);
   des_set_key(mykey);
   strcpy((char *)c, p);
   des_encrypt((char *)c);
   des_done();
   for(i=0; i<8; i++)
   {
      printf("%02X ", c[i]);
   }
   des_init(0);
   des_set_key(mykey);
   des_decrypt((char *)c);
   des_done();
   puts((char *)c);
}