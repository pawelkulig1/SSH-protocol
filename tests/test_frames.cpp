#include "../ssh_packets/key_exchange_init.h"

#include "common.h"
#include <string>
#include <vector>
#include <iostream>

void key_exchange_init_test_suite()
{
	const std::string name = "key_exchange_init_test_suite";
	std::cout << std::endl << name << std::endl;
	KeyExchangeInit keyExchange({EncryptionAlgorithm::AES_128_CBC,
								 EncryptionAlgorithm::AES_192_CBC, 	
    							 EncryptionAlgorithm::AES_256_CBC, 
 								 EncryptionAlgorithm::BLOWFISH_CBC});
}

void binary_frame_construct_payload_packet_length_suite()
{
	const std::string name = "binary_frame_construct_payload_packet_length_suite";
	typedef std::pair<std::vector<uint8_t>, int> test_pair;
	std::vector<test_pair> test_vec = {
		test_pair(empty_payload_generator(1069), 1076),
		test_pair(empty_payload_generator(1383), 1388)
	};

	std::cout << std::endl << name << std::endl;
	for (const test_pair pair: test_vec)
	{
		//BinaryFrame bf;
		//bf.setPayload(pair.first);
		//ASSERT(pair.second, bf.getPacketLength(), pair.second);
	}	
}	

void main_frames_test()
{
	key_exchange_init_test_suite();
	binary_frame_construct_payload_packet_length_suite();
}
