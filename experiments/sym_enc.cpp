#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include "../host.h"

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext);

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext);

int main()
{
//					  "::::::::::::::::::::::::::::::::"
	//std::string key = "c7272c6411e907f5cd9d1080e754c212";
	//std::string iv =  "d3b0d0e074edc9967a3b518df00bad7d";
	//std::string plaintext = "0000002c083200000004726f6f740000000e7373682d636f6e6e656374696f6e000000046e60f6e65fce492512e0110e";
	//unsigned char *real_plaintext = (unsigned char *)"2rootssh-connectionnone��+��W�?";

	//unsigned char *real_key = new unsigned char [key.size()/2];
	//unsigned char *real_iv = new unsigned char [iv.size()/2];
	//unsigned char *real_plaintext = new unsigned char[plaintext.size()/2];
	//int j=0;
	//for(int i=0;i<key.size();i+=2)
	//{
	//	real_key[j++] = Byte(Host::ascii2byte(key[i]), Host::ascii2byte(key[i+1])).get();
	//}

	//j=0;
	//for(int i=0;i<iv.size();i+=2)
	//{
	//	real_iv[j++] = Byte(Host::ascii2byte(iv[i]), Host::ascii2byte(iv[i+1])).get();
	//}

	//j=0;
	//for(int i=0;i<plaintext.size();i+=2)
	//{
	//	real_plaintext[j++] = Byte(Host::ascii2byte(plaintext[i]), Host::ascii2byte(plaintext[i+1])).get();
	//}

	//printf("\n");
	//for(int i=0;i<plaintext.size()/2;i++)
	//{
	//	printf("%x ", real_plaintext[i]);
	//}

	//for(int i=0;i<key.size()/2;i++)
	//{
	//	printf("%x ", real_key[i]);
	//}

	//printf("\n");
	//for(int i=0;i<iv.size()/2;i++)
	//{
	//	printf("%x ", real_iv[i]);
	//}
	unsigned char *real_key = (unsigned char *)"FEDCBA9876543210"; 
	unsigned char *real_iv = (unsigned char *)"0123456789ABCDEF";
	unsigned char *real_plaintext = (unsigned char *) "0123";

	unsigned char ciphertext[128];
	unsigned char decryptedtext[128];
	int decryptedtext_len, ciphertext_len;
	ciphertext_len = encrypt(real_plaintext, 4, real_key, real_iv,
                              ciphertext);

	//BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);

	/* Decrypt the ciphertext */
    //decryptedtext_len = decrypt(ciphertext, ciphertext_len, real_key, real_iv,
    //                            decryptedtext);

    ///* Add a NULL terminator. We are expecting printable text */
    //decryptedtext[decryptedtext_len] = '\0';

    ///* Show the decrypted text */
    //printf("Decrypted text is:\n");
    //printf("%s\n", decryptedtext);


}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

	printf("\n%d\n", plaintext_len);
										//key, iv
	EVP_CipherInit(ctx, EVP_aes_128_cbc(), NULL, (u_char *)iv, 1);
	EVP_CIPHER_CTX_ctrl(ctx, -1, -1, (u_char *)iv);
	EVP_CIPHER_CTX_set_key_length(ctx, 16);
	EVP_CipherInit(ctx, NULL, (u_char *)key, NULL, -1);
	EVP_Cipher(ctx, ciphertext, (u_char *)plaintext, plaintext_len);
	printf("\n");
	for(int i=0;i<plaintext_len;i++)
	{
		printf("%x ", ciphertext[i]);
	}	
	printf("\n");

    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}
