#include <array>
#include <vector>
#include <utility>
#include <string>
#include "common.h"
#include "../byte.h"

void get_high_suite()
{
	const std::string name = __func__;
	typedef std::pair<uint8_t, uint8_t> test_pair;
	std::vector<test_pair> test_vec = {
		test_pair(0xFF, 0x0F),
		test_pair(0xAB, 0x0A),
		test_pair(0x01, 0x0),
		test_pair(0x10, 0x1)
	}; 

	std::cout << std::endl << name << std::endl;
	for (const test_pair pair: test_vec)
	{
		Byte b(pair.first);
		ASSERT(static_cast<int>(pair.first), b.high(), pair.second);
	}
}

void get_low_suite()
{
	const std::string name = __func__;
	typedef std::pair<uint8_t, uint8_t> test_pair;
	std::vector<test_pair> test_vec = {
		test_pair(0xFF, 0x0F),
		test_pair(0xAB, 0xB),
		test_pair(0x01, 0x1),
		test_pair(0x10, 0x0)
	}; 

	std::cout << std::endl << name << std::endl;
	for (const test_pair pair: test_vec)
	{
		Byte b(pair.first);
		ASSERT(static_cast<int>(pair.first), b.low(), pair.second);
	}

}

void payload_set_high_low_suite()
{
	const std::string name = "payload_from_ascii_suite";
	typedef std::pair<std::pair<uint8_t, uint8_t>, uint8_t> test_pair;
	std::vector<test_pair> test_vec = {
		test_pair({std::make_pair<uint8_t, uint8_t>(0x0F, 0x0F), 0xFF}),
		test_pair({std::make_pair<uint8_t, uint8_t>(0x0A, 0x0B), 0xAB}),
		test_pair({std::make_pair<uint8_t, uint8_t>(0xCA, 0x0B), 0xAB}),
		test_pair({std::make_pair<uint8_t, uint8_t>(0xCA, 0xFB), 0xAB})
	};

	std::cout << std::endl << name << std::endl;
	for (const test_pair pair: test_vec)
	{
		Byte b;
		b.set(pair.first.first, pair.first.second);
		ASSERT(static_cast<int>(pair.first.first), b.get(), pair.second);
	}
}

void get_str_suite()
{
	const std::string name = __func__;
	std::cout << std::endl << name << std::endl;
	std::vector<Byte> test_vec = {
		Byte(0xFF),
		Byte(0xF0),
		Byte(0x0F),
		Byte(0xAB),
		Byte(0x77),
		Byte(0x00)
	};
	std::vector<std::string> out_vec = {
		"FF",
		"F0",
		"0F",
		"AB",
		"77",
		"00"
	};

	for (int i=0;i<test_vec.size();i++)
	{
		ASSERT(out_vec[i], test_vec[i].get_str(), out_vec[i]);
	}

}

void main_byte_test()
{
	std::cout << std::endl << "============================== " << __func__  << " ==============================" <<  std::endl;
	get_high_suite();
	get_low_suite();
	payload_set_high_low_suite();
	get_str_suite();
}
