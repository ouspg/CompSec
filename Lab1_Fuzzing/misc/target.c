/*
	This program is meant to be a fuzzing target for OpenSSL 1.0.1f. It
	creates an OpenSSL server instance, waits for client to initiate a
	TLS handshake and then responds to it with server hello. The message
	that the "client" sends is given as an input after the server is set
	up.

	To compile (enables ASAN and AFL instrumentation, must be 
	enabled for the OpenSSL as well!):
		AFL_USE_ASAN=1 afl-clang-fast target.c -o target openssl/libssl.a openssl/libcrypto.a -I openssl/include -ldl

	Usage:
	* Requires a certificate! Use OpenSSL to create a dummy certificate
	  (RSA 512-bit, not secure but it does not matter during fuzzing):
		openssl req -x509 -newkey rsa:512 -keyout server.key -out server.pem -days 365 -nodes -subj /CN=a/
	* Run the program
		./target
	* After the server instance is initialized, the program will wait for input
	
	Tips and tricks:
	* Use this to set a location for AFL. Check the 'deferred instrumentation'
	  from AFL docs.
		#ifdef __AFL_HAVE_MANUAL_CONTROL //afl deferred instrumentation
		__AFL_INIT();
		#endif
	* You can check what the crash packet looks like by using od, text2pcap
	  and wireshark:
		od -A x -t x1z -v <raw_packet> | text2pcap -T 443,443 - <output_pcap>
*/

/* Standard headers */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

/* OpenSSL headers */
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

/* Error handling */
void err() {
	ERR_print_errors_fp(stderr);
	exit(1);
}

/* Print server state */
void state( SSL *server ) {
	printf("server: %s / %s\n", SSL_state_string(server),
								SSL_state_string_long(server));
}

/* Main program */
int main( int argc, char **argv ) {

	/* Necessary variables */
	uint8_t buf[100] = {0}; //message buffer

	/* Initialize the OpenSSL library */
	SSL_library_init(); //initialize the OpenSSL library, load libssl algorithms
	SSL_load_error_strings(); //load and register human readable error strings
	ERR_load_BIO_strings(); //load and register BIO strings
	OpenSSL_add_all_algorithms(); //load all algorithms
	
	/* Set up the SSL context and use 'server.pem' and 'server'key' as the dummy certificate */
	SSL_CTX *sctx = SSL_CTX_new(TLSv1_method()); //create sctx as new SSL_CTX object, use TLSv1
	SSL_CTX_use_certificate_file(sctx, "server.pem", SSL_FILETYPE_PEM); // Use 'server.pem'
	SSL_CTX_use_PrivateKey_file(sctx, "server.key", SSL_FILETYPE_PEM); // Use 'server.key'
	SSL *server = SSL_new(sctx); //create server SSL structure
	
	/* Initialize server BIO */
	BIO *sreadbio = BIO_new(BIO_s_mem()); //initialize server input BIO
	BIO *swritebio = BIO_new(BIO_s_mem()); //initialize server output BIO
	SSL_set_bio(server, sreadbio, swritebio); //connect sreadbio and swritebio for read and write operations
	SSL_set_accept_state(server); //set the server to wait for the connection

	size_t size = read(STDIN_FILENO, buf, 100); //read from stdin to message buffer
	if (size == -1) { //if cannot read input from stdin
		err();
	}

	BIO_write(sreadbio, buf, size); //"send" data to server (write data to server input BIO)
	state(server); //print server state
	SSL_do_handshake(server); //start server part of the handshake, read the data from BIO
	state(server); //print server state
	
	return 0;
}