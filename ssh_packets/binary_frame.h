#pragma once
#include "frame.h"
#include <vector>

typedef uint8_t byte;

class BinaryFrame: public Frame
{
	protected:
		//uint32_t 	packet_length; //length of packet in bytes without mac or packet_length
		//uint8_t  	padding_length; //length of random padding
		Payload     payload; 
		Payload     random_padding; //packet length must be multiple of 8 or cypher or cypher block size (bigger one)
		Payload 	mac;

		Payload 	frame; //whole frame packed

		virtual void prepare_frame();
		virtual void construct_payload();
	public:
		virtual void setPayload(const Payload& payload);
		virtual Payload getPayload() override =0;
		virtual Payload getFrame() override;
		uint32_t getPacketLength() const {return packet_length;} //only for tests
		uint8_t getPaddingLength() const {return padding_size;} //only for tests
};
