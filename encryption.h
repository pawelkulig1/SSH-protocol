#pragma once
#include <string>
#include <unordered_map>
#include <memory>

enum class EncryptionAlgorithm
{
	AES_128_CBC, // = std::string("aes128-cbc"),
	AES_192_CBC, // = std::string("aes192-cbc"),
	AES_256_CBC, // = std::string("aes256-cbc"),
	BLOWFISH_CBC    // = std::string("blowfish-cbc")
};

class Encryption
{
	std::unique_ptr<Encryption> encr_ptr;
	EncryptionAlgorithm current_encryption_method;
	//const static std::unordered_map<EncryptionAlgorithm, std::string> algorithm_to_name;

public:
	void set_encryption_method(std::unique_ptr<Encryption> encr_ptr);
	EncryptionAlgorithm get_current_encryption_method() const;
	static std::string get_algorithm_string(EncryptionAlgorithm algorithm);
};
