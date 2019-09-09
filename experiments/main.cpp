#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <openssl/bn.h>
#include <openssl/dh.h>
#include <openssl/err.h>
#include <stdint.h>



int main()
{
	BIGNUM *p, *g, *q, *pub_key, *priv_key, *B;
   	p = BN_new();
	g = BN_new();
	q = BN_new();
	pub_key = BN_new();
	priv_key = BN_new();
	B = BN_new();

	const char *cp = "23";
	const char *cg = "5";
	const char *cpriv = "4";
	int status;
    status = BN_dec2bn(&p, cp);
	std::cout<<status<<std::endl;
	
	status = BN_dec2bn(&g, cg);
	std::cout<<status << std::endl;

	status = BN_dec2bn(&priv_key, cpriv);
	std::cout<<status << std::endl;

	status = BN_dec2bn(&B, "10");
	std::cout<<status << std::endl;
	
	DH *dh = DH_new();
	DH_set0_pqg(dh, p, q, g);
	DH_set0_key(dh, NULL, priv_key);
	status = DH_generate_key(dh);
	uint8_t *ptr = new uint8_t[256];
	int ssize = DH_compute_key(ptr, B, dh);
	for(int i=0;i<ssize;i++)
	{

		std::cout<<"numbero: "<<std::dec<<std::setfill('0')<<static_cast<uint16_t>(ptr[i]) << " ";
		//if(i%8 == 0 && i%16 != 0) std::cout<<"  ";
		//if(i%16 == 0) std::cout<<std::endl;
	}
	std::cout<<std::endl;

	delete[] ptr;
	if(status == 0)
	{
		unsigned long err = ERR_get_error();
		char *buf = new char[512];
		ERR_error_string(err, buf);
		std::cout<<buf<<std::endl;
		delete[] buf;
	}
	DH_get0_key(dh, const_cast<const BIGNUM**>(&pub_key), const_cast<const BIGNUM**>(&priv_key));
	DH_get0_pqg(dh, const_cast<const BIGNUM**>(&p), const_cast<const BIGNUM**>(&q), const_cast<const BIGNUM**>(&g));
	int q_size = BN_num_bytes(q);
	int pub_size = BN_num_bytes(pub_key);
	
	const char *pub = new char[pub_size];
	const char *q_s = new char[q_size];

	pub = BN_bn2dec(pub_key);
	q_s = BN_bn2dec(q);

	printf("%s \n", pub);
	printf("%s \n", q_s);

	//std::cout<<std::endl;



	//BIGNUM *priv_key = dh->priv_key;


	DH_free(dh);
	//BN_free(p);
	//BN_free(g);
	//BN_free(pub_key);
	//BN_free(priv_key);


	

    return 0;
}
