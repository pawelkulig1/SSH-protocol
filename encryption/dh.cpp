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

void DiffieHellman::set_q(const BigNum &q)
{
	this->q = q;
}

BigNum DiffieHellman::get_p() const
{
	return p;
}

BigNum DiffieHellman::get_q() const
{
	return q;
}

void DiffieHellman::generate_keys()
{
	if(!p.is_set())
	{
		std::cout << "P not set!" << std::endl;	//TODO
	}

	if(!q.is_set())
	{
		std::cout << "G not set!" << std::endl; //TODO
	}
	int status = 0;
	status = DH_set0_pqg(dh, p.get0(), nullptr, g.get0());
	if(!status)
	{
		handle_error();
	}

	status = DH_generate_key(dh);
	if(!status)
	{
		handle_error();
	}
}

BigNum DiffieHellman::get_pub() const
{
	return pub_key;
}

BigNum DiffieHellman::get_priv() const
{
	return priv_key;
}

	
} //namespace SSH
