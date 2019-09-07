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
	void handle_error();

public:
	bool has_to_be_freed = true;

	BigNum();
	BigNum(const std::vector<Byte> &b_vec);
	~BigNum();
	
	std::vector<Byte> get() const;

	void operator=(const std::vector<Byte> &b_vec);

	friend std::ostream &operator<<(std::ostream &in, const BigNum &bn);
};
}
