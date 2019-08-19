#pragma once
#include "frame.h"
#include <vector>


class BinaryFrame: public Frame
{
	protected:
		typedef std::vector<uint8_t> byte;
		uint32_t packet_length; //length of packet in bytes without mac or packet_length
		uint8_t  padding_length; //length of random padding
		byte     payload; 
		byte     random_padding; //packet length must be multiple of 8 or cypher or cypher block size (bigger one)
		byte 	 mac;

		byte frame; //whole frame packed

		virtual void prepare_frame();
		virtual void construct_payload();
	public:
		virtual void setPayload(const std::vector<uint8_t> payload);
		virtual std::vector<uint8_t> getPayload()=0;
		virtual std::vector<uint8_t> getFrame() const;
		uint32_t getPacketLength() const {return packet_length;} //only for tests
		uint8_t getPaddingLength() const {return padding_length;} //only for tests
};
