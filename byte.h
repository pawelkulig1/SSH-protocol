#pragma once
#include <stdint.h>

class Byte
{
	uint8_t byte;
public:
	Byte();
	Byte(uint8_t byte);
	uint8_t low() const;
	uint8_t high() const;
	uint8_t get() const;
	void set(const uint8_t high, const uint8_t low);
};
