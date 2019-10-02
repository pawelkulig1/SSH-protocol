#include <array>
#include <vector>
#include <unordered_map>
#include <utility>
#include <string>
#include "common.h"

#include "../payload.h"


void pack_frames_vector_suite()
{
	typedef std::pair<std::vector<uint8_t>, std::vector<uint8_t>> test_pair;
	//typedef std::pair<uint8_t,              std::vector<uint8_t>> test_pair_2;
	//typedef std::pair<std::string,          std::vector<uint8_t>> test_pair_3;
	const std::string name = __func__;

	std::vector<test_pair> test_vec = {
		test_pair(empty_payload_generator(10), empty_payload_generator(10)),
		test_pair(empty_payload_generator(10), empty_payload_generator(20)),
		test_pair(empty_payload_generator(1),  empty_payload_generator(21)),
	};
	
	std::cout << std::endl << name << std::endl;

	Payload fp;
	for (const auto vec: test_vec)
	{
		fp.next(vec.first);
		ASSERT(vec.second.size(), fp.get_payload(), vec.second);
	}
}

void pack_frames_uint8_next_suite()
{
	//typedef std::pair<std::tuple<uint8_t, size_t>,             std::vector<uint8_t>> test_pair_2;
	////typedef std::pair<std::string,          std::vector<uint8_t>> test_pair_3;
	//const std::string name = __func__;

	//std::vector<test_pair> test_vec = {
	//	test_pair(std::make_tuple<uint8_t, size_t>() {}),
	//	test_pair(0, empty_payload_generator(12)),
	//};
	//
	//std::cout << std::endl << name << std::endl;

	//FramePacker fp;
	//for (const auto vec: test_vec)
	//{
	//	fp.next(vec.first);
	//	ASSERT(vec.second.size(), fp.get_payload(), vec.second);
	//}
}


void main_frame_packer_test()
{
	pack_frames_vector_suite();
}
