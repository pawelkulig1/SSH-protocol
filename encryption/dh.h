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
	void set_p(const BigNum &p);
	void set_q(const BigNum &q);
	BigNum get_p() const;
	BigNum get_q() const;
	void generate_keys();
	BigNum get_pub() const;
	BigNum get_priv() const;
};
} //namespace SSH
