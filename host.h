#pragma once

#include <string>
#include <vector>

struct Host
{
	static uint32_t 			get_ip_address(std::string);
	static std::vector<uint8_t> payload_from_ascii(const std::string ascii_text);
	static std::vector<uint8_t> payload_from_hex(const std::string hex_data);
	static std::vector<uint8_t> random_hex(int bytes);
	static std::string 			vector_to_string(const std::vector<uint8_t> &vec);
};
