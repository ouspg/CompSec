/*

Let OpenSSL talk to itself
code CC0 by Hanno Böck

To create self signed cert use:
  openssl req -x509 -newkey rsa:512 -keyout server.key -out server.pem -days 9999 -nodes -subj /CN=a/

*/

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdlib.h>
#include <stdio.h>

void err()
{
	ERR_print_errors_fp(stderr);
	exit(1);
}

int main(int argc, char **argv)
{
	int r, c, step;
	unsigned char buf[4096];
	char *ifi;
	FILE *f;
	char fn[15];
	SSL_CTX *sctx, *cctx;
	SSL *server, *client;
	BIO *sinbio, *soutbio, *cinbio, *coutbio;

	if (argc != 3) {
		step = -1;
	} else {
		step = argv[1][0] - '0';
		ifi = argv[2];
	}

	SSL_library_init();
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();

	if (!(sctx = SSL_CTX_new(TLSv1_method())))
		err();
	if (!SSL_CTX_use_certificate_file(sctx, "server.pem", SSL_FILETYPE_PEM))
		err();
	if (!SSL_CTX_use_PrivateKey_file(sctx, "server.key", SSL_FILETYPE_PEM))
		err();
	if (!(server = SSL_new(sctx)))
		err();

	sinbio = BIO_new(BIO_s_mem());
	soutbio = BIO_new(BIO_s_mem());
	SSL_set_bio(server, sinbio, soutbio);
	SSL_set_accept_state(server);

	if (!(cctx = SSL_CTX_new(TLSv1_method())))
		err();
	if (!(client = SSL_new(cctx)))
		err();

	cinbio = BIO_new(BIO_s_mem());
	coutbio = BIO_new(BIO_s_mem());
	SSL_set_bio(client, cinbio, coutbio);
	SSL_set_connect_state(client);

	c = 0;
	do {

		r = SSL_do_handshake(client);
		if (r == -1) {
			if ((SSL_get_error(client, r) != SSL_ERROR_WANT_WRITE)
			    && (SSL_get_error(client, r) !=
				SSL_ERROR_WANT_READ))
				err();
		}

		r = BIO_read(coutbio, buf, 4096);
		if (r == -1)
			err();
		c++;

		if (c == step) {
#ifdef __AFL_HAVE_MANUAL_CONTROL
			__AFL_INIT();
#endif
			f = fopen(ifi, "rb");
			r = fread(buf, 1, 4096, f);
		} else if (step == -1) {
			sprintf(fn, "packet-%i", c);
			f = fopen(fn, "wb");
			fwrite(buf, 1, r, f);
		}
		BIO_write(sinbio, buf, r);

		r = SSL_do_handshake(server);
		if (r == -1) {
			if ((SSL_get_error(server, r) != SSL_ERROR_WANT_WRITE)
			    && (SSL_get_error(server, r) !=
				SSL_ERROR_WANT_READ))
				err();
		}

		r = BIO_read(soutbio, buf, 4096);
		if (r == -1)
			err();
		c++;
		if (c == step) {
#ifdef __AFL_HAVE_MANUAL_CONTROL
			__AFL_INIT();
#endif
			f = fopen(ifi, "rb");
			r = fread(buf, 1, 4096, f);
		} else if (step == -1) {
			sprintf(fn, "packet-%i", c);
			f = fopen(fn, "wb");
			fwrite(buf, 1, r, f);
		}
		BIO_write(cinbio, buf, r);

		printf("server state: %s / %s\n", SSL_state_string(server),
		       SSL_state_string_long(server));
		printf("client state: %s / %s\n", SSL_state_string(client),
		       SSL_state_string_long(client));
	} while ((!SSL_is_init_finished(server)
		  || !SSL_is_init_finished(client)) && c < 10);

	return 0;
}
