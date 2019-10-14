#pragma once
#define DEFAULT_FRAME_NAME "NULL"
#include <vector>
#include <string>
#include "../payload.h"

enum SSH_OPCODES
{
	SSH_MSG_DISCONNECT            = 1,
	SSH_MSG_IGNORE                = 2,
	SSH_MSG_UNIMPLEMENTED         = 3,
	SSH_MSG_DEBUG                 = 4,
	SSH_MSG_SERVICE_REQUEST       = 5,
	SSH_MSG_SERVICE_ACCEPT        = 6,
	SSH_MSG_KEXINIT               = 20,
	SSH_MSG_NEWKEYS               = 21	
};


class Frame
{
	protected:
		std::string name = DEFAULT_FRAME_NAME;
		Payload raw_payload;
	public:
		uint32_t packet_length;
		uint32_t padding_size; //should be 8_t but it is not working now
		uint32_t opcode;
		
		Frame();
		Frame(std::string name);
		Frame(std::string name, const Payload& payload);
		void operator=(const Payload& payload);

		virtual ~Frame();
		virtual Payload getPayload()=0; // only payload
		virtual Payload getFrame()=0; // whole frame
		virtual void parse();
};
