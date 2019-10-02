#pragma once

#include "binary_frame.h"
#include "../encryption.h"
#include "../host.h"
#include "../payload.h"

class KeyExchangeInit: public BinaryFrame 
{
	//frame structure
	byte            opcode = SSH_OPCODES::SSH_MSG_KEXINIT;
	Payload 		cookie; //Payload(Host::random_hex(16));
	std::string     kex_algorithms = "curve25519-sha256";
	std::string     server_host_key_algorithms = "ecdsa-sha2-nistp256";
	std::string     encryption_algorithms_client_to_server = "aes256-ctr";
    std::string     encryption_algorithms_server_to_client = "aes256-ctr";
    std::string     mac_algorithms_client_to_server = "hmac-sha2-512";
    std::string     mac_algorithms_server_to_client = "hmac-sha2-256";
    std::string     compression_algorithms_client_to_server = "none";
    std::string     compression_algorithms_server_to_client = "none";
    std::string     languages_client_to_server = "";
    std::string     languages_server_to_client = "";
    byte            first_kex_packet_follows = 0;
    uint32_t        reserved = 0; //(reserved for future extension)


	std::vector<EncryptionAlgorithm> requested_algorithms;
	public:
	KeyExchangeInit();
	KeyExchangeInit(std::vector<EncryptionAlgorithm> algoritms);
	
	void construct_payload() override;
	void set_requested_algorithms(std::vector<EncryptionAlgorithm> requested_algorithms);
	std::vector<EncryptionAlgorithm> get_requested_algorithms() const;
	Payload getPayload() override;
	
};


extern KeyExchangeInit key_exchange_init;
