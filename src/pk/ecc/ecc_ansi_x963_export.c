/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */

#include "tomcrypt.h"

/**
  @file ecc_ansi_x963_export.c
  ECC Crypto, Tom St Denis
*/

#ifdef LTC_MECC

/** ECC X9.63 (Sec. 4.3.6) uncompressed export
  @param key     Key to export
  @param out     [out] destination of export
  @param outlen  [in/out]  Length of destination and final output size
  Return CRYPT_OK on success
*/
int ecc_ansi_x963_export(ecc_key *key, unsigned char *out, unsigned long *outlen)
{
   unsigned char buf[ECC_BUF_SIZE];
   unsigned long numlen, xlen, ylen;

   LTC_ARGCHK(key    != NULL);
   LTC_ARGCHK(out    != NULL);
   LTC_ARGCHK(outlen != NULL);

   numlen = key->dp.size;
   xlen = mp_unsigned_bin_size(key->pubkey.x);
   ylen = mp_unsigned_bin_size(key->pubkey.y);

   if (xlen > numlen || ylen > numlen || sizeof(buf) < numlen) {
      return CRYPT_BUFFER_OVERFLOW;
   }

   if (*outlen < (1 + 2*numlen)) {
      *outlen = 1 + 2*numlen;
      return CRYPT_BUFFER_OVERFLOW;
   }

   /* store byte 0x04 */
   out[0] = 0x04;

   /* pad and store x */
   zeromem(buf, sizeof(buf));
   mp_to_unsigned_bin(key->pubkey.x, buf + (numlen - xlen));
   XMEMCPY(out+1, buf, numlen);

   /* pad and store y */
   zeromem(buf, sizeof(buf));
   mp_to_unsigned_bin(key->pubkey.y, buf + (numlen - ylen));
   XMEMCPY(out+1+numlen, buf, numlen);

   *outlen = 1 + 2*numlen;
   return CRYPT_OK;
}

#endif

/* ref:         $Format:%D$ */
/* git commit:  $Format:%H$ */
/* commit time: $Format:%ai$ */
