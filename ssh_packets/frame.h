#pragma once
#define DEFAULT_FRAME_NAME "NULL"
#include <vector>
#include <string>



class Frame
{
	protected:
		std::string name = DEFAULT_FRAME_NAME;
	public:
		Frame();
		Frame(std::string name);
		virtual ~Frame();
		virtual std::vector<uint8_t> getPayload()=0;
};
