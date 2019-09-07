#include "byte.h"

Byte::Byte()
{
	byte = 0;
}

Byte::Byte(uint8_t byte): byte(byte) {}

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

void Byte::set(const uint8_t high, const uint8_t low)
{
	byte = (high << 4) | (low & 0x0F);
}
