#include "dh.h"
#include "encryption_common.h"


namespace SSH {

DiffieHellman::DiffieHellman()
{
	dh = DH_new();
}

void DiffieHellman::set_p(const BigNum &p)
{
	this->p = p;
}

void DiffieHellman::set_g(const BigNum &g)
{
	this->g = g;
}

BigNum DiffieHellman::get_p() const
{
	return p;
}

BigNum DiffieHellman::get_g() const
{
	return g;
}

void DiffieHellman::generate_keys()
{
	if(!p.is_set())
	{
		std::cout << "P not set!" << std::endl;	//TODO
	}

	if(!g.is_set())
	{
		std::cout << "G not set!" << std::endl; //TODO
	}
	int status = 0;
	status = DH_set0_pqg(dh, p.get0(), NULL, g.get0());
	if(!status)
	{
		handle_error();
	}
	//std::cout<< p << std::endl;
	//std::cout<< "dh.cpp:" << p.get().size() << std::endl;
	//std::cout<< g << std::endl;
	status = DH_generate_key(dh);
	if(!status)
	{
		handle_error();
	}
	DH_get0_key(dh, const_cast<const BIGNUM**>(pub_key.get0_ptr()), const_cast<const BIGNUM**>(priv_key.get0_ptr()));
}

BigNum DiffieHellman::get_pub() const
{
	return pub_key;
}

BigNum DiffieHellman::get_priv() const
{
	return priv_key;
}

void DiffieHellman::set_pub(BigNum &pub)
{
	pub_key = pub;
}

void DiffieHellman::set_priv(BigNum &priv)
{
	priv_key = priv;
}
	
} //namespace SSH
