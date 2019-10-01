#include "big_num.h"
#include <cstring>
#include "encryption_common.h"
#include <iomanip>
#include "../host.h"

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
	//std::cout<<"get(), size: " << size << std::endl;
	char *c = new char[size*2];
	c = BN_bn2hex(bn);
	printf("%s\n", c);
	std::vector<Byte> ret_vec;
	for(int i=0;i<size*2;i+=2)
	{
		Byte temp(Host::ascii2byte(c[i]), Host::ascii2byte(c[i+1]));
		//Byte temp(c[i], c[i+1]);
		ret_vec.push_back(temp);
		//std::cout<<" getting: "<<std::hex<<std::setfill('0')<<static_cast<int>(Host::ascii2byte(c[i])) << "" <<static_cast<int>(Host::ascii2byte(c[i+1]));
	}
	//std::cout<<std::endl;

	delete[] c;
	return ret_vec;
}

void BigNum::operator=(const std::vector<Byte> &b_vec)
{
	char *c = new char[(b_vec.size() * 2) + 1];
	int counter = 0;
	for(int i=0;i<b_vec.size()*2;i+=2)
	{
		c[i] = Host::byte2ascii(b_vec[counter].high());
		c[i+1] = Host::byte2ascii(b_vec[counter++].low());
		//std::cout<<" setting: "<<std::hex<<std::setfill('0')<<static_cast<int>(c[i]) << "" <<static_cast<int>(c[i+1]);
	}
	
	//std::cout<<std::endl;
	//printf("%s\n", c);
	c[b_vec.size()*2] = '\0';

	unsigned long size = BN_hex2bn(&bn, c);
	//std::cout<<"operator= vec, size: " << size << std::endl;
	if(size != b_vec.size()*2)
		std::cout << "something went wrong: " << __func__ << std::endl;

	delete[] c;
	has_to_be_freed = false;	
	set = true;
}

void BigNum::operator=(const std::string &hex_number)
{
	unsigned long size = BN_hex2bn(&bn, hex_number.c_str());
	if(size != hex_number.size())
		std::cout << "something went wrong: " << __func__ << "std::string " << size << std::endl;
	has_to_be_freed = false;	
	set = true;
}

void BigNum::operator=(const BigNum &bn2)
{
	bn = BN_dup(bn2.bn);
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
		in << b.get_str() << " ";
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

BIGNUM **BigNum::get0_ptr()
{
	has_to_be_freed = false;
	return &bn;
}

} //namespace SSH
