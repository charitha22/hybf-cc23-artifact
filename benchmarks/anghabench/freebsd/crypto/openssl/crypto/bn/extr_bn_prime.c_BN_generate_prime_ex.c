#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  prime_t ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_F_BN_GENERATE_PRIME_EX ; 
 int /*<<< orphan*/  BN_GENCB_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BN_R_BITS_TOO_SMALL ; 
 int BN_is_prime_fasttest_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int BN_prime_checks_for_size (int) ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUMPRIMES ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_probable_prime_dh (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probable_prime (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probable_prime_dh_safe (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int BN_generate_prime_ex(BIGNUM *ret, int bits, int safe,
                         const BIGNUM *add, const BIGNUM *rem, BN_GENCB *cb)
{
    BIGNUM *t;
    int found = 0;
    int i, j, c1 = 0;
    BN_CTX *ctx = NULL;
    prime_t *mods = NULL;
    int checks = BN_prime_checks_for_size(bits);

    if (bits < 2) {
        /* There are no prime numbers this small. */
        BNerr(BN_F_BN_GENERATE_PRIME_EX, BN_R_BITS_TOO_SMALL);
        return 0;
    } else if (add == NULL && safe && bits < 6 && bits != 3) {
        /*
         * The smallest safe prime (7) is three bits.
         * But the following two safe primes with less than 6 bits (11, 23)
         * are unreachable for BN_rand with BN_RAND_TOP_TWO.
         */
        BNerr(BN_F_BN_GENERATE_PRIME_EX, BN_R_BITS_TOO_SMALL);
        return 0;
    }

    mods = OPENSSL_zalloc(sizeof(*mods) * NUMPRIMES);
    if (mods == NULL)
        goto err;

    ctx = BN_CTX_new();
    if (ctx == NULL)
        goto err;
    BN_CTX_start(ctx);
    t = BN_CTX_get(ctx);
    if (t == NULL)
        goto err;
 loop:
    /* make a random number and set the top and bottom bits */
    if (add == NULL) {
        if (!probable_prime(ret, bits, mods))
            goto err;
    } else {
        if (safe) {
            if (!probable_prime_dh_safe(ret, bits, add, rem, ctx))
                goto err;
        } else {
            if (!bn_probable_prime_dh(ret, bits, add, rem, ctx))
                goto err;
        }
    }

    if (!BN_GENCB_call(cb, 0, c1++))
        /* aborted */
        goto err;

    if (!safe) {
        i = BN_is_prime_fasttest_ex(ret, checks, ctx, 0, cb);
        if (i == -1)
            goto err;
        if (i == 0)
            goto loop;
    } else {
        /*
         * for "safe prime" generation, check that (p-1)/2 is prime. Since a
         * prime is odd, We just need to divide by 2
         */
        if (!BN_rshift1(t, ret))
            goto err;

        for (i = 0; i < checks; i++) {
            j = BN_is_prime_fasttest_ex(ret, 1, ctx, 0, cb);
            if (j == -1)
                goto err;
            if (j == 0)
                goto loop;

            j = BN_is_prime_fasttest_ex(t, 1, ctx, 0, cb);
            if (j == -1)
                goto err;
            if (j == 0)
                goto loop;

            if (!BN_GENCB_call(cb, 2, c1 - 1))
                goto err;
            /* We have a safe prime test pass */
        }
    }
    /* we have a prime :-) */
    found = 1;
 err:
    OPENSSL_free(mods);
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    bn_check_top(ret);
    return found;
}