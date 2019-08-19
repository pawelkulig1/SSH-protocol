#pragma once

#include "binary_frame.h"

class KeyExchangeInit: public BinaryFrame 
{
	enum class ALGORITHMS {
		AES_128_CBC, // = std::string("aes128-cbc"),
		AES_192_CBC, // = std::string("aes192-cbc"),
		AES_256_CBC, // = std::string("aes256-cbc"),
		BLOWFISH    // = std::string("blowfish-cbc")
	};

};

