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
		//Byte temp(c[i], c[i+1]);
		ret_vec.push_back(temp);
		std::cout<<" getting: "<<std::hex<<std::setfill('0')<<static_cast<int>(c[i] - 55) << "" <<static_cast<int>(c[i+1] - 55);
	}
	std::cout<<std::endl;

	delete[] c;
	return ret_vec;
}

void BigNum::operator=(const std::vector<Byte> &b_vec)
{
	char *c = new char[(b_vec.size() * 2) + 1];
	int counter = 0;
	for(int i=0;i<b_vec.size()*2;i+=2)
	{
		c[i] = b_vec[counter].high() + 55;
		c[i+1] = b_vec[counter++].low() + 55; 
		std::cout<<" setting: "<<std::hex<<std::setfill('0')<<static_cast<int>(c[i] + 55) << "" <<static_cast<int>(c[i+1] + 55);
	}
	
	std::cout<<std::endl;
	//printf("%s\n", c);
	c[b_vec.size()*2] = '\0';

	unsigned long size = BN_hex2bn(&bn, c);
	if(size != b_vec.size()*2)
		std::cout << "something went wrong: " << __func__ << std::endl;

	delete[] c;
	has_to_be_freed = false;	
	set = true;
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

BIGNUM *BigNum::get0()
{
	has_to_be_freed = false;
	return bn;
}

BIGNUM *BigNum::get1()
{
	return bn;
}
} //namespace SSH
