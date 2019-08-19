#include "binary_frame.h"
#include <iostream>

void BinaryFrame::prepare_frame()
{

	int padding_length = 8 - ((payload.size() + 4 + 1) % 8);
	padding_length = padding_length < 4 ? padding_length + 8 : padding_length;

	random_padding.erase(random_padding.begin(), random_padding.end());
	for(int i=0;i<padding_length;i++)
		random_padding.push_back(0x0); //TODO

	packet_length = 1 + payload.size() + padding_length;
}

void BinaryFrame::construct_payload()
{
	frame.erase(frame.begin(), frame.end());
	uint8_t *ptr = reinterpret_cast<uint8_t*>(&packet_length);
	frame.push_back(ptr[0]);
	frame.push_back(ptr[1]);
	frame.push_back(ptr[2]);
	frame.push_back(ptr[3]);
	frame.push_back(padding_length);
	frame.insert(frame.end(), payload.begin(), payload.end());
	frame.insert(frame.end(), random_padding.begin(), random_padding.end());
	frame.insert(frame.end(), mac.begin(), mac.end());
}

void BinaryFrame::setPayload(const std::vector<uint8_t> payload)
{
	this->payload = payload;
	prepare_frame();
	construct_payload();
}

/*std::vector<uint8_t> BinaryFrame::getPayload() const
{
	return payload;
}*/

std::vector<uint8_t> BinaryFrame::getFrame() const
{
	return frame;
}
