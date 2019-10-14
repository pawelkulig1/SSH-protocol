#pragma once

#include "binary_frame.h"
#include "../encryption.h"
#include "../host.h"
#include "../payload.h"

class KeyExchangeInit: public BinaryFrame 
{
	//frame structure
	Payload 		cookie; //Payload(Host::random_hex(16));
	int 			kex_algorithms_len;
	std::string     kex_algorithms = "curve25519-sha256";

	int 			server_host_key_algorithms_len;
	std::string     server_host_key_algorithms = "ssh-rsa";

	int 			encryption_algorithms_client_to_server_len;
	std::string     encryption_algorithms_client_to_server = "aes128-cbc";

	int				encryption_algorithms_server_to_client_len;
    std::string     encryption_algorithms_server_to_client = "aes128-cbc";

	int				mac_algorithms_client_to_server_len;
    std::string     mac_algorithms_client_to_server = "hmac-sha1";

	int				mac_algorithms_server_to_client_len;
    std::string     mac_algorithms_server_to_client = "hmac-sha1";

	int				compression_algorithms_client_to_server_len;
    std::string     compression_algorithms_client_to_server = "none";

	int				compression_algorithms_server_to_client_len;
    std::string     compression_algorithms_server_to_client = "none";

	int				languages_client_to_server_len;
    std::string     languages_client_to_server = "";

	int				languages_server_to_client_len;
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
	virtual void parse();
	
};


extern KeyExchangeInit key_exchange_init;
