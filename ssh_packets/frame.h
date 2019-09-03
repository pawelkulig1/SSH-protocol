#pragma once
#define DEFAULT_FRAME_NAME "NULL"
#include <vector>
#include <string>

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
	public:
		Frame();
		Frame(std::string name);
		virtual ~Frame();
		virtual std::vector<uint8_t> getPayload()=0; // only payload
		virtual std::vector<uint8_t> getFrame()=0;   // whole frame
};
