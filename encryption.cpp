#include "encryption.h"
#include <iostream>

#define ENCRYPTION_ALGORITHM(ENUM_NAME, NAME) \
	std::make_tuple<EncryptionAlgorithm, std::string>(EncryptionAlgorithm::ENUM_NAME, NAME) 

const std::unordered_map<EncryptionAlgorithm, std::string> Encryption::algorithm_to_name = {
	ENCRYPTION_ALGORITHM(AES_128_CBC,  "aes128-cbc"),
	ENCRYPTION_ALGORITHM(AES_192_CBC,  "aes192-cbc"),
	ENCRYPTION_ALGORITHM(AES_256_CBC,  "aes256-cbc"),
	ENCRYPTION_ALGORITHM(BLOWFISH_CBC, "blowfish-cbc")
};

void Encryption::set_encryption_method(std::unique_ptr<Encryption> encr_ptr)
{	
	this->encr_ptr = std::move(encr_ptr);
}

EncryptionAlgorithm Encryption::get_current_encryption_method() const
{
	return current_encryption_method; 
}

std::string Encryption::get_algorithm_string(EncryptionAlgorithm algorithm)
{
	return algorithm_to_name.find(algorithm)->second;
}

