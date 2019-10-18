#include "key_exchange_init.h"
#include "../host.h"
#include <iostream>
#include <errno.h>
#include <cstring>


KeyExchangeInit::KeyExchangeInit()
{
	cookie = Host::random_hex(16);
}

KeyExchangeInit::KeyExchangeInit(std::vector<EncryptionAlgorithm> algorithms)
{
	cookie = Host::random_hex(16);
	set_requested_algorithms(algorithms);
}

void KeyExchangeInit::construct_payload()
{
	kex_algorithms_len = kex_algorithms.size();
	encryption_algorithms_client_to_server_len = encryption_algorithms_client_to_server.size();
	encryption_algorithms_server_to_client_len = encryption_algorithms_server_to_client.size();
	mac_algorithms_client_to_server_len = mac_algorithms_client_to_server.size();
	mac_algorithms_server_to_client_len = mac_algorithms_server_to_client.size();
	languages_client_to_server_len = languages_client_to_server.size();
	languages_server_to_client_len = languages_server_to_client.size();


	payload.next(SSH_OPCODES::SSH_MSG_KEXINIT, 1);
	payload.next(cookie, 16);

	payload.next(kex_algorithms_len, 4);
	payload.next(kex_algorithms, kex_algorithms_len);

	payload.next(server_host_key_algorithms_len, 4);
	payload.next(server_host_key_algorithms, server_host_key_algorithms_len);

	payload.next(encryption_algorithms_client_to_server_len, 4);
	payload.next(encryption_algorithms_client_to_server, encryption_algorithms_client_to_server_len);

	payload.next(encryption_algorithms_server_to_client_len, 4);
	payload.next(encryption_algorithms_server_to_client, encryption_algorithms_server_to_client_len);

	payload.next(mac_algorithms_client_to_server_len, 4);
	payload.next(mac_algorithms_client_to_server, mac_algorithms_client_to_server_len);

	payload.next(mac_algorithms_server_to_client_len, 4);
	payload.next(mac_algorithms_server_to_client, mac_algorithms_server_to_client_len);

	payload.next(compression_algorithms_client_to_server_len, 4);
	payload.next(compression_algorithms_client_to_server, compression_algorithms_client_to_server_len);

	payload.next(compression_algorithms_server_to_client_len, 4);
	payload.next(compression_algorithms_server_to_client, compression_algorithms_server_to_client_len);

	payload.next(languages_client_to_server_len, 4);
	payload.next(languages_client_to_server, languages_client_to_server_len);

	payload.next(languages_server_to_client_len, 4);
	payload.next(languages_server_to_client, languages_server_to_client_len);

	payload.next(first_kex_packet_follows, 1);

	payload.next(reserved, 4);
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

Payload KeyExchangeInit::getPayload()
{
	return payload;
}

KeyExchangeInit key_exchange_init({EncryptionAlgorithm::AES_128_CBC, 
									EncryptionAlgorithm::AES_192_CBC, 
									EncryptionAlgorithm::AES_256_CBC, 
									EncryptionAlgorithm::BLOWFISH_CBC});

void KeyExchangeInit::parse()
{
	if(raw_payload.size() == 0)
		throw(std::system_error(std::make_error_code(std::errc::no_message), std::strerror(errno)));
	
	Frame::parse();
	if(opcode != SSH_OPCODES::SSH_MSG_KEXINIT)
	{
		throw(std::system_error(std::make_error_code(std::errc::operation_not_permitted), std::strerror(errno)));
	}

	
	cookie 							= raw_payload.get	   	(16);
	kex_algorithms_len 				= raw_payload.get<int> 	(4);
	kex_algorithms 					= raw_payload.get	   	(kex_algorithms_len).get_str();
	
	server_host_key_algorithms_len 	= raw_payload.get<int> 	(4);
	server_host_key_algorithms		= raw_payload.get		(server_host_key_algorithms_len).get_str();
	
	encryption_algorithms_client_to_server_len = raw_payload.get<int>(4);
   	encryption_algorithms_client_to_server = raw_payload.get(encryption_algorithms_client_to_server_len).get_str();
	
	encryption_algorithms_server_to_client_len = raw_payload.get<int>(4);
	encryption_algorithms_server_to_client = raw_payload.get(encryption_algorithms_server_to_client_len).get_str();


	mac_algorithms_client_to_server_len = raw_payload.get<int>(4);
   	mac_algorithms_client_to_server = raw_payload.get(mac_algorithms_client_to_server_len).get_str();

	mac_algorithms_server_to_client_len = raw_payload.get<int>(4);
	mac_algorithms_server_to_client = raw_payload.get(mac_algorithms_server_to_client_len).get_str();

	languages_client_to_server_len = raw_payload.get<int>(4);
   	languages_client_to_server = raw_payload.get(languages_client_to_server_len).get_str();

	languages_server_to_client_len = raw_payload.get<int>(4);
	languages_server_to_client = raw_payload.get(languages_server_to_client_len).get_str();

	first_kex_packet_follows = raw_payload.get<int>(1);
	reserved = raw_payload.get<int>(1);
}
