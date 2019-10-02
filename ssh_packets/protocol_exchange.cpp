#include "protocol_exchange.h"
#include "../host.h"
#include "../encryption.h"

ProtocolExchange::ProtocolExchange()
{
	name = "ProtocolExchange";
}

Payload ProtocolExchange::getPayload()
{
	comments = comments.size() > 0 ? "\x20" + comments : comments;
	
	payload.clear();
	payload.next(header, true);
	payload.next("-", true);
	payload.next(protocol_version, true);
	payload.next("-", true);
	payload.next(software_version, true);
	payload.next(comments, true);
	payload.next("\x0d\x0a", true);

	return payload;
}

Payload ProtocolExchange::getFrame()
{
	getPayload();
	return payload;
}

ProtocolExchange protocol_exchange;
								   
								   
								   
