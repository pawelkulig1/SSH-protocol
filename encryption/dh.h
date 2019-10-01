#pragma once
#include "big_num.h" 
#include <openssl/dh.h>

namespace SSH {

class DiffieHellman
{
	BigNum p;
	BigNum g;
	BigNum q;
	BigNum priv_key;
	BigNum pub_key;
	DH *dh;

public:
	DiffieHellman();
	//DiffieHellman(const DiffieHellman &df2);
	void set_p(const BigNum &g);
	void set_g(const BigNum &q);
	BigNum get_p() const;
	BigNum get_g() const;
	void generate_keys();
	BigNum get_pub() const;
	BigNum get_priv() const;
	void set_priv(BigNum &priv);
	void set_pub(BigNum &pub);
};
} //namespace SSH
