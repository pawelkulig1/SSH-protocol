#include "key_exchange_init.h"
#include "../host.h"
#include <iostream>


KeyExchangeInit::KeyExchangeInit()
{}

KeyExchangeInit::KeyExchangeInit(std::vector<EncryptionAlgorithm> algorithms)
{
	set_requested_algorithms(algorithms);
}

void KeyExchangeInit::construct_payload()
{
	std::string payload_temp = "";
		
	payload = Host::payload_from_ascii(payload_temp);
}

void KeyExchangeInit::set_requested_algorithms(std::vector<EncryptionAlgorithm> requested_algorithms)
{
	this->requested_algorithms = requested_algorithms;
	construct_payload();
}

std::vector<EncryptionAlgorithm> KeyExchangeInit::get_requested_algorithms() const
{
	return requested_algorithms;
}

std::vector<uint8_t> KeyExchangeInit::getPayload()
{
	return payload;
}

KeyExchangeInit key_exchange_init({EncryptionAlgorithm::AES_128_CBC, 
									EncryptionAlgorithm::AES_192_CBC, 
									EncryptionAlgorithm::AES_256_CBC, 
									EncryptionAlgorithm::BLOWFISH_CBC});
