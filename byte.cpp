#include "byte.h"
#include "host.h"

Byte::Byte()
{
	byte = 0;
}

Byte::Byte(const uint8_t byte): byte(byte) {}

Byte::Byte(const uint8_t high, const uint8_t low)
{
	set(high, low);
}

uint8_t Byte::low() const
{
	return (byte & 0x0F);
}

uint8_t Byte::high() const
{
	return (byte>>4);
}

uint8_t Byte::get() const
{
	return byte;
}

std::string Byte::get_str() const
{
	return std::string(1, Host::byte2ascii(high())) + std::string(1, Host::byte2ascii(low()));
}

void Byte::set(const uint8_t high, const uint8_t low)
{
	byte = (high << 4) | (low & 0x0F);
}

bool Byte::operator==(const Byte &other) const
{
	return byte == other.byte;
}
