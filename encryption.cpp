#include "encryption.h"
#include <iostream>
#include <tuple>

const std::unordered_map<EncryptionAlgorithm, std::string> Encryption::algorithm_to_name({
		{EncryptionAlgorithm::AES_128_CBC,  "aes128-cbc"},
		{EncryptionAlgorithm::AES_192_CBC,   "aes192-cbc"},
		{EncryptionAlgorithm::AES_256_CBC,   "aes256-cbc"},
		{EncryptionAlgorithm::BLOWFISH_CBC,  "blowfish-cbc"}
});

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

