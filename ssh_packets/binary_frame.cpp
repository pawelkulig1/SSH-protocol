#include "binary_frame.h"
#include <iostream>

void BinaryFrame::prepare_frame()
{

	int padding_length = 8 - ((payload.size() + 4 + 1) % 8);
	padding_length = padding_length < 4 ? padding_length + 8 : padding_length;

	random_padding.clear();
	for(int i=0;i<padding_length;i++)
		random_padding.next(static_cast<Byte>(0x0)); //TODO

	packet_length = 1 + payload.size() + padding_length;
}

void BinaryFrame::construct_payload()
{
	//frame.erase(frame.begin(), frame.end());
	frame.clear();
	uint8_t *ptr = reinterpret_cast<uint8_t*>(&packet_length);
	frame.next(ptr[0]);
	frame.next(ptr[1]);
	frame.next(ptr[2]);
	frame.next(ptr[3]);
	frame.next(padding_size);
	frame.next(payload);
	frame.next(random_padding);
	frame.next(mac);
	//frame.insert(frame.end(), payload.begin(), payload.end());
	//frame.insert(frame.end(), random_padding.begin(), random_padding.end());
	//frame.insert(frame.end(), mac.begin(), mac.end());
}

void BinaryFrame::setPayload(const Payload &payload)
{
	this->payload = payload;
}

/*std::vector<uint8_t> BinaryFrame::getPayload() const
{
	return payload;
}*/

Payload BinaryFrame::getFrame()
{
	prepare_frame();
	BinaryFrame::construct_payload();
	return frame;
}
