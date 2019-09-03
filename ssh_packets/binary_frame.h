#pragma once
#include "frame.h"
#include <vector>

typedef std::vector<uint8_t> byte_vec;
typedef uint8_t byte;

class BinaryFrame: public Frame
{
	protected:
		uint32_t packet_length; //length of packet in bytes without mac or packet_length
		uint8_t  padding_length; //length of random padding
		byte_vec     payload; 
		byte_vec     random_padding; //packet length must be multiple of 8 or cypher or cypher block size (bigger one)
		byte_vec 	 mac;

		byte_vec frame; //whole frame packed

		virtual void prepare_frame();
		virtual void construct_payload();
	public:
		virtual void setPayload(const std::vector<uint8_t> payload);
		virtual std::vector<uint8_t> getPayload() override =0;
		virtual std::vector<uint8_t> getFrame() override;
		uint32_t getPacketLength() const {return packet_length;} //only for tests
		uint8_t getPaddingLength() const {return padding_length;} //only for tests
};
