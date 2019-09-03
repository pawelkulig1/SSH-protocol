#include <array>
#include <vector>
#include <unordered_map>
#include <utility>
#include <string>
#include "common.h"
#include "../encryption.h"

void get_current_algorithm_suite()
{
	const std::string name = "get_current_algorithm_suite";
	
	std::cout << std::endl << name << std::endl;
	ASSERT("aes128-cbc", Encryption::get_algorithm_string(EncryptionAlgorithm::AES_128_CBC), "aes128-cbc");
}


void main_encryption_test()
{
	get_current_algorithm_suite();

}
