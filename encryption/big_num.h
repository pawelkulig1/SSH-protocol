#pragma once
#include <openssl/bn.h>
#include <vector>
#include "../byte.h"
#include <ostream>
#include <iostream>
namespace SSH {
class BigNum
{
	BIGNUM *bn;
	bool set = false;

public:
	bool has_to_be_freed = true;

	BigNum();
	BigNum(const std::vector<Byte> &b_vec);
	~BigNum();
	
	std::vector<Byte> get() const;
	void operator=(const std::vector<Byte> &b_vec);
	void operator=(const std::string &hex_number);
	bool is_set() const;

	friend std::ostream &operator<<(std::ostream &in, const BigNum &bn);
};
}
