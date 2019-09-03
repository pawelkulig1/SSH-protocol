#include "host.h"
#include <iostream>
#include <string>
#include <vector>


uint32_t Host::get_ip_address(std::string ip)
{
	int poz = 0; 
	int prev_poz = 0;
	uint8_t octets[4] = {0};
	for(int i=0;i<4;i++)
	{
		poz = ip.find(".", prev_poz);
		poz = poz == -1 ? ip.length() : poz;
		std::string temp = ip.substr(prev_poz, poz - prev_poz);
		prev_poz = poz + 1;
		octets[i] = static_cast<uint8_t>(std::stoi(temp));
	}	
	return htonl(*(reinterpret_cast<uint32_t*>(octets))); //endianes
}

std::vector<uint8_t> Host::payload_from_ascii(const std::string ascii_text)
{
	std::vector<uint8_t> data;
	data.reserve(ascii_text.size());
	for (const char letter: ascii_text)
		data.push_back(static_cast<uint8_t>(letter));
	return data;
}

std::vector<uint8_t> Host::payload_from_hex(const std::string hex_data)
{
	std::vector<uint8_t> data;
	data.reserve(hex_data.size() %2 == 0 ? hex_data.size()/2 : (hex_data.size() + 1) / 2);
	size_t size;
	uint8_t temp;
	for(int i=0;i<hex_data.size();i+=2)
	{
		temp = std::stoi(hex_data.substr(i, 1), &size, 16) << 4;
		temp |= std::stoi(hex_data.substr(i+1, 1), &size, 16);
		data.push_back(temp);
	}

	return data;
}

std::vector<uint8_t> Host::random_hex(int bytes)
{
	std::vector<uint8_t> ret;
	for (int i=0;i<bytes;i++)
	{
		ret.push_back(0x0A);
	}
	return ret;
}
