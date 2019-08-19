#include "../ssh_packets/frame.h"
#include "../ssh_packets/frame.cpp"
#include "../ssh_packets/binary_frame.h"
#include "../ssh_packets/binary_frame.cpp"

#include "common.h"
#include <string>
#include <vector>

std::vector<uint8_t> empty_payload_generator(int size)
{
	std::vector<uint8_t> temp_vec;
	temp_vec.reserve(size);
	for (int i=0;i<size;i++){
		temp_vec.push_back(0x0);
	}
	return temp_vec;
}


void binary_frame_construct_payload_packet_length_suite()
{
	const std::string name = "binary_frame_construct_payload_packet_length_suite";
	typedef std::pair<std::vector<uint8_t>, int> test_pair;
	std::vector<test_pair> test_vec = {
		test_pair(empty_payload_generator(1069), 1076),
		test_pair(empty_payload_generator(1383), 1388)
	};

	std::cout<< name << std::endl;
	for (const test_pair pair: test_vec)
	{
		//BinaryFrame bf;
		//bf.setPayload(pair.first);
		//ASSERT(pair.second, bf.getPacketLength(), pair.second);
	}	
}	

void main_frames_test()
{
	binary_frame_construct_payload_packet_length_suite();
}
