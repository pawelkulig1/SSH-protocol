#include "frame.h"
#include <iostream>

Frame::Frame()
{}

Frame::Frame(std::string name): name(name){}

Frame::~Frame()
{}

Frame::Frame(std::string name, const Payload& payload): name(name), raw_payload(payload)
{
}

void Frame::operator=(const Payload& payload)
{
	raw_payload = payload;
}

void Frame::parse()
{
	packet_length 		= Host::byte2ascii(raw_payload.get<int>(0, 4));
	std::cout<<packet_length<<std::endl;
	padding_size 		= raw_payload.get<int>(4, 1);
	std::cout<<padding_size<<std::endl;
	opcode				= raw_payload.get<int>(5, 1); 
	std::cout<<opcode<<std::endl;
}



