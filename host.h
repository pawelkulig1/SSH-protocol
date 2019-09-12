#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

struct Host
{
	static uint32_t 			get_ip_address(std::string);
	static std::vector<uint8_t> payload_from_ascii(const std::string ascii_text);
	static std::vector<uint8_t> payload_from_hex(const std::string hex_data);
	static std::vector<uint8_t> random_hex(int bytes);
	static std::string 			vector_to_string(const std::vector<uint8_t> &vec);
	template <typename T> static void print(const std::vector<T> vec)
	{
		int c = 0;
		for(const T t: vec)
		{
			if(c % 8 == 0) std::cout << "  ";
			std::cout<< std::hex << std::setfill('0') << static_cast<int>(t.get()) << " ";
			if(c % 16 == 0) std::cout << std::endl;
		}
	}
};
