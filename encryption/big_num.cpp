#include "big_num.h"
#include <cstring>
namespace SSH {
BigNum::BigNum()
{
	bn = BN_new();
	const char *c = "0";
	int size = BN_hex2bn(&bn, c);
	if(size != 1)
		std::cout << "something went wrong: " << __func__ << std::endl;
}

BigNum::BigNum(const std::vector<Byte> &b_vec)
{
	bn = BN_new();
	this->operator=(b_vec);
}

BigNum::~BigNum()
{
	if(has_to_be_freed)
	{
		BN_free(bn);
	}
}

std::vector<Byte> BigNum::get() const
{
	int size = BN_num_bytes(bn);
	char *c = new char[size];
	c = BN_bn2hex(bn);
	std::vector<Byte> ret_vec(c, c + size);

	delete[] c;
	return ret_vec;
}

void BigNum::operator=(const std::vector<Byte> &b_vec)
{
	char *c = new char[b_vec.size()+1];
	std::memcpy(c, b_vec.data(), b_vec.size());
	c[b_vec.size()] = '\0';

	unsigned long size = BN_hex2bn(&bn, c);
	if(size != b_vec.size())
		std::cout << "something went wrong: " << __func__ << std::endl;
	delete[] c;
}

std::ostream &operator<<(std::ostream &in, const BigNum &bn)
{
	for(const Byte b: bn.get())
	{
		in << b.get() << " ";
	}
	return in;
	
}

} //namespace SSH
