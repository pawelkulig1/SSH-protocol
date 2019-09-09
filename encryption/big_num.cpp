#include "big_num.h"
#include <cstring>
#include "encryption_common.h"
#include <iomanip>

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
	set = true;
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
	std::vector<Byte> ret_vec;
	for(int i=0;i<size*2;i+=2)
	{
		Byte temp(c[i] - 55, c[i+1] - 55);
		ret_vec.push_back(temp);
	}

	delete[] c;
	return ret_vec;
}

void BigNum::operator=(const std::vector<Byte> &b_vec)
{
	set = true;

	char *c = new char[(b_vec.size() * 2)+1];
	int counter = 0;
	for(int i=0;i<b_vec.size()*2;i+=2)
	{
		c[i] = b_vec[counter].high();
		c[i+1] = b_vec[counter++].low(); 
	}
	c[b_vec.size()*2] = '\0';

	unsigned long size = BN_hex2bn(&bn, "aabbcc");
	if(size != b_vec.size()*2)
		std::cout << "something went wrong: " << __func__ << std::endl;

	delete[] c;
	has_to_be_freed = false;	
}

bool BigNum::is_set() const
{
	return set;
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
