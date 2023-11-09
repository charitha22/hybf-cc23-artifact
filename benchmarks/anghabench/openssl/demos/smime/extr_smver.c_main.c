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
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  PKCS7 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char*,char*) ; 
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SMIME_read_PKCS7 (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  X509_STORE_add_cert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_new () ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    BIO *in = NULL, *out = NULL, *tbio = NULL, *cont = NULL;
    X509_STORE *st = NULL;
    X509 *cacert = NULL;
    PKCS7 *p7 = NULL;

    int ret = 1;

    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    /* Set up trusted CA certificate store */

    st = X509_STORE_new();

    /* Read in signer certificate and private key */
    tbio = BIO_new_file("cacert.pem", "r");

    if (!tbio)
        goto err;

    cacert = PEM_read_bio_X509(tbio, NULL, 0, NULL);

    if (!cacert)
        goto err;

    if (!X509_STORE_add_cert(st, cacert))
        goto err;

    /* Open content being signed */

    in = BIO_new_file("smout.txt", "r");

    if (!in)
        goto err;

    /* Sign content */
    p7 = SMIME_read_PKCS7(in, &cont);

    if (!p7)
        goto err;

    /* File to output verified content to */
    out = BIO_new_file("smver.txt", "w");
    if (!out)
        goto err;

    if (!PKCS7_verify(p7, NULL, st, cont, out, 0)) {
        fprintf(stderr, "Verification Failure\n");
        goto err;
    }

    fprintf(stderr, "Verification Successful\n");

    ret = 0;

 err:
    if (ret) {
        fprintf(stderr, "Error Verifying Data\n");
        ERR_print_errors_fp(stderr);
    }
    PKCS7_free(p7);
    X509_free(cacert);
    BIO_free(in);
    BIO_free(out);
    BIO_free(tbio);
    return ret;
}