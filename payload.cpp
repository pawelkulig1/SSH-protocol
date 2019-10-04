#include "payload.h"
#include "host.h"
#include <system_error>

Payload::Payload() {}
Payload::Payload(const Byte byte)
{
	next(byte);
}

Payload::Payload(const Byte byte, const size_t bytes)
{
	next(byte, bytes);
}

Payload::Payload(const std::vector<Byte>& byte_vec)
{
	next(byte_vec);
}

Payload::Payload(const std::vector<Byte>& byte_vec, const size_t bytes)
{
	next(byte_vec, bytes);
}

Payload::Payload(const Payload& payload)
{
	raw_payload = payload.raw_payload;
}

Payload::Payload(const Payload& payload, const size_t bytes)
{
	raw_payload = payload.raw_payload;
}

Payload::Payload(const std::string& str, const bool ascii)
{
	next(str, ascii);
}

Payload::Payload(const std::string& str, const size_t bytes, const bool ascii)
{
	next(str, ascii, bytes);
}

Payload::Payload(const uint8_t *c_str, size_t size)
{
	next(c_str, size);
}

Payload::Payload(const uint8_t *c_str, const size_t bytes, const size_t size)
{
	next(c_str, size, bytes);
}

Payload::Payload(const std::vector<Byte>::const_iterator beg, const std::vector<Byte>::const_iterator end)
{
	raw_payload.insert(raw_payload.begin(), beg, end);
}

void Payload::operator=(const Payload& payload)
{
	raw_payload = payload.raw_payload;	
}

Byte Payload::at(int index) const
{
	return raw_payload[index];
}

std::vector<Byte>::const_iterator Payload::begin() const
{
	return raw_payload.begin();
}

std::vector<Byte>::const_iterator Payload::end() const
{
	return raw_payload.end();
}

void Payload::next_zeros(const size_t bytes)
{
	for(int i=0;i<bytes;i++)
	{
		raw_payload.push_back(0x0);
	}
}

void Payload::next(const uint32_t data, const size_t bytes)
{
	next_zeros(bytes - 4);
	raw_payload.insert(raw_payload.end(), &data, &data + 4);
}

void Payload::next(const Byte byte)
{
	raw_payload.push_back(byte);
}

void Payload::next(const Byte byte, const size_t bytes)
{
	size_t data_size = 1;
	next_zeros(bytes - data_size);
	raw_payload.push_back(byte);
}

void Payload::next(const std::vector<Byte>& vec)
{
	raw_payload.insert(raw_payload.end(), vec.begin(), vec.end());
}

void Payload::next(const std::vector<Byte>& vec, const size_t bytes)
{
	next_zeros(bytes - vec.size());	
	raw_payload.insert(raw_payload.end(), vec.begin(), vec.end());
}

void Payload::next(const std::string& str, bool ascii)
{
	next(ascii ? Host::payload_from_ascii(str) : Host::payload_from_hex(str));
}

void Payload::next(const std::string& str, const size_t bytes, bool ascii)
{
	next_zeros(bytes - str.size());
	next(ascii ? Host::payload_from_ascii(str) : Host::payload_from_hex(str));
}

void Payload::next(const Payload& payload)
{
	next(payload.raw_payload);
}

void Payload::next(const Payload& payload, const size_t bytes)
{
	next_zeros(bytes - payload.size());
	next(payload.raw_payload);
}

void Payload::next(const uint8_t *c_str, const size_t size)
{
	raw_payload.insert(raw_payload.end(), c_str, c_str + size);	
}

void Payload::next(const uint8_t *c_str, const size_t size, const size_t bytes)
{
	next_zeros(bytes - size);
	raw_payload.insert(raw_payload.end(), c_str, c_str + size);	
}

Payload Payload::get(int beg, int size) const
{
	return Payload(raw_payload.begin() + beg, raw_payload.begin() + beg + size);
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
