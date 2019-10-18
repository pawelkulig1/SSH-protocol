#include "frame.h"
#include "../host.h"
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
	packet_length 		= raw_payload.get<int>(4);//Host::byte2ascii(raw_payload.get<int>(0, 4));
	padding_size 		= raw_payload.get<int>(1);
	opcode				= raw_payload.get<int>(1); 
}



