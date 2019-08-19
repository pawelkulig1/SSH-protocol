#pragma once
#include "frame.h"
#include "../host.h"

class ProtocolExchange: public Frame
{
	std::vector<uint8_t> payload = Host::payload_from_ascii("SSH-2.0-ClosedSSH_7.9\r\n");
	public:
		ProtocolExchange();
		~ProtocolExchange();
		std::vector<uint8_t> getPayload() override;

		std::string header = "SSH";
		std::string protocol_version = "2.0";
		std::string software_version = "ClosedSSH_1.0";
		std::string comments = "";
};

extern ProtocolExchange protocol_exchange;
