#include "host.h"
#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>


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

Payload Host::payload_from_ascii(const std::string ascii_text)
{
	Payload data;
	data.reserve(ascii_text.size());
	for (const char letter: ascii_text)
		data.next(static_cast<uint8_t>(letter));
	return data;
}

Payload Host::payload_from_hex(const std::string hex_data)
{
	//std::vector<uint8_t> data;
	Payload data;
	data.reserve(hex_data.size() %2 == 0 ? hex_data.size()/2 : (hex_data.size() + 1) / 2);
	size_t size;
	uint8_t temp;
	for(int i=0;i<hex_data.size();i+=2)
	{
		temp = std::stoi(hex_data.substr(i, 1), &size, 16) << 4;
		temp |= std::stoi(hex_data.substr(i+1, 1), &size, 16);
		data.next(temp);
	}

	return data;
}

Payload Host::random_hex(int bytes)
{
	Payload ret;
	for (int i=0;i<bytes;i++)
	{
		ret.next(0x0A);
	}
	return ret;
}


std::string Host::vector_to_string(const std::vector<uint8_t> &vec)
{
	struct HexByte {
		uint8_t low : 4,
				high  : 4;
	};
	union {
		char u_c;
		HexByte u_hb;
	};

	std::string ret;
	for(const char c: vec)
	{
		u_c = c;
		ret.push_back(u_hb.high);
		ret.push_back(u_hb.low);
	}
	return ret;
}

uint8_t Host::byte2ascii(uint8_t byte)
{	
	//uint8_t ascii = 0;
	if(byte < 10)
	{
		return byte + 48;
	}
	if(byte < 16)
	{
		return byte + 55;
	}
	std::cout<<byte<<std::endl;
	throw(std::system_error(std::make_error_code(std::errc::argument_out_of_domain), __FUNCTION__));
}

uint8_t Host::ascii2byte(uint8_t ascii)
{
	//Byte byte = 0;
	if(ascii >= 48 && ascii <= 57)
	{
		return ascii - 48;
	}
	if(ascii >= 65 && ascii <= 70)
	{
		return ascii - 55;
	}
	std::cout<<ascii<<std::endl;
	throw(std::system_error(std::make_error_code(std::errc::argument_out_of_domain), __FUNCTION__));

}
