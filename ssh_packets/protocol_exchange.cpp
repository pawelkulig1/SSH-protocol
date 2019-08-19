#include "protocol_exchange.h"
#include "../host.h"

ProtocolExchange::ProtocolExchange()
{
	name = "ProtocolExchange";
}

ProtocolExchange::~ProtocolExchange()
{}

std::vector<uint8_t> ProtocolExchange::getPayload()
{
	comments = comments.size() > 0 ? "\x20" + comments : comments;
	
	payload = Host::payload_from_ascii(
			header + 
			"-" + 
			protocol_version + 
			"-" + 
			software_version + 
			comments + 
			"\x0d\x0a");

	return payload;
}

ProtocolExchange protocol_exchange;
