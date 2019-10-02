#include "payload.h"
#include "host.h"
#include <system_error>

Payload::Payload() {}
Payload::Payload(Byte byte)
{
	next(byte);
}

Payload::Payload(std::vector<Byte> byte_vec)
{
	next(byte_vec);
}

Payload::Payload(const Payload &payload)
{
	raw_payload = payload.raw_payload;
}

Payload::Payload(std::string str, bool ascii)
{
	next(str, ascii);
}

void Payload::operator=(const Payload &payload)
{
	raw_payload = payload.raw_payload;	
}

void Payload::next(Byte byte)
{
	raw_payload.push_back(byte);
}

void Payload::next(std::vector<Byte> vec)
{
	raw_payload.insert(raw_payload.end(), vec.begin(), vec.end());
}

void Payload::next(std::string str, bool ascii)
{
	next(ascii ? Host::payload_from_ascii(str) : Host::payload_from_hex(str));
}

void Payload::next(const Payload &payload)
{
	next(payload.raw_payload);
}

std::vector<Byte> Payload::get_payload_vec() const
{
	return raw_payload;
}

void Payload::reserve(const unsigned int reservation)
{
	raw_payload.reserve(reservation);
}

size_t Payload::size() const
{
	return raw_payload.size();
}

void Payload::clear()
{
	raw_payload.erase(raw_payload.begin(), raw_payload.end());
}
