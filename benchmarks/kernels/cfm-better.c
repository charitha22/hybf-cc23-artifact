

#define BF_ENCRYPT	1
#define BF_DECRYPT	0

/* If you make this 'unsigned int' the pointer variants will work on
 * the Alpha, otherwise they will not.  Strangly using the '8 byte'
 * BF_LONG and the default 'non-pointer' inner loop is the best configuration
 * for the Alpha */
#define BF_LONG unsigned long

#define BF_ROUNDS	16
#define BF_BLOCK	8

typedef struct bf_key_st
	{
	BF_LONG P[BF_ROUNDS+2];
	BF_LONG S[4*256];
	} BF_KEY;

#ifndef NOPROTO
 
void BF_set_key(BF_KEY *key, int len, unsigned char *data);
void BF_ecb_encrypt(unsigned char *in,unsigned char *out,BF_KEY *key,
	int encrypt);
void BF_encrypt(BF_LONG *data,BF_KEY *key,int encrypt);
void BF_cbc_encrypt(unsigned char *in, unsigned char *out, long length,
	BF_KEY *ks, unsigned char *iv, int encrypt);
void BF_cfb64_encrypt(unsigned char *in, unsigned char *out, long length,
	BF_KEY *schedule, unsigned char *ivec, int *num, int encrypt);
void BF_ofb64_encrypt(unsigned char *in, unsigned char *out, long length,
	BF_KEY *schedule, unsigned char *ivec, int *num);
char *BF_options(void);

#else

void BF_set_key();
void BF_ecb_encrypt();
void BF_encrypt();
void BF_cbc_encrypt();
void BF_cfb64_encrypt();
void BF_ofb64_encrypt();
char *BF_options();

#endif



void BF_cfb64_encrypt(in, out, length, schedule, ivec, num,
                      encrypt) unsigned char *in;
unsigned char *out;
long length;
BF_KEY *schedule;
unsigned char *ivec;
int *num;
int encrypt;
{
  register BF_LONG v0, v1, t;
  register int n = *num;
  register long l = length;
  BF_LONG ti[2];
  unsigned char *iv, c, cc;

  iv = (unsigned char *)ivec;
  if (encrypt) {
    while (l--) {
      if (n == 0) {
        n2l(iv, v0);
        ti[0] = v0;
        n2l(iv, v1);
        ti[1] = v1;
        BF_encrypt((unsigned long *)ti, schedule, BF_ENCRYPT);
        iv = (unsigned char *)ivec;
        t = ti[0];
        l2n(t, iv);
        t = ti[1];
        l2n(t, iv);
        iv = (unsigned char *)ivec;
      }
      c = *(in++) ^ iv[n];
      *(out++) = c;
      iv[n] = c;
      n = (n + 1) & 0x07;
    }
  } else {
    while (l--) {
      if (n == 0) {
        n2l(iv, v0);
        ti[0] = v0;
        n2l(iv, v1);
        ti[1] = v1;
        BF_encrypt((unsigned long *)ti, schedule, BF_ENCRYPT);
        iv = (unsigned char *)ivec;
        t = ti[0];
        l2n(t, iv);
        t = ti[1];
        l2n(t, iv);
        iv = (unsigned char *)ivec;
      }
      cc = *(in++);
      c = iv[n];
      iv[n] = cc;
      *(out++) = c ^ cc;
      n = (n + 1) & 0x07;
    }
  }
  v0 = v1 = ti[0] = ti[1] = t = c = cc = 0;
  *num = n;
}
