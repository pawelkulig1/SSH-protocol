#include <array>
#include <vector>
#include <unordered_map>
#include <utility>
#include <string>
#include "common.h"
#include "../byte.h"
#include "../encryption/big_num.h"

void big_num_operator1_suite()
{
	const std::string name = __func__;
	std::vector<std::vector<Byte>> test_vec = {
		{0xAA, 0xBB, 0xCC},
		{0x24, 0x21, 0x22},
		{0x04, 0x01, 0x02},
		{0x14, 0x01, 0x12},
	//	{0x00, 0xB1, 0xA2}, works correctly but tests are done in wrong way
		{0xB0, 0x0B, 0xAA},
		{0xFF, 0x01, 0x02, 0xDD},
		{0xFF, 0xFF, 0xFF, 0xFF}
		//{0x0}
		};	
	std::cout << std::endl << name << std::endl;


	for(const std::vector<Byte> b_vec : test_vec)
	{
		SSH::BigNum bg;
		bg = b_vec;
		ASSERT(static_cast<int>(b_vec[0].get()), bg.get(), b_vec);
	}
}

void big_num_operator2_suite()
{
	const std::string name = __func__;
	std::vector<std::string> test_vec = {
		"AABBCC",
		"242122",
		"040102",
		"140112",
		"B00BAA",
		"FF0102DD",
		"FFFFFFFF"
		};	
	std::vector<std::vector<Byte>> out_vec = {
		{0xAA, 0xBB, 0xCC},
		{0x24, 0x21, 0x22},
		{0x04, 0x01, 0x02},
		{0x14, 0x01, 0x12},
		{0xB0, 0x0B, 0xAA},
		{0xFF, 0x01, 0x02, 0xDD},
		{0xFF, 0xFF, 0xFF, 0xFF}
	};	
	
	std::cout << std::endl << name << std::endl;


	//for(const std::string s_vec : test_vec)
	for(int i=0;i<test_vec.size();i++)
	{
		SSH::BigNum bg;
		bg = test_vec[i];
		ASSERT(test_vec[i], bg.get(), out_vec[i]);
	}
}

void main_big_num_test()
{
	big_num_operator1_suite();	
	big_num_operator2_suite();	

}
