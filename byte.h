#pragma once
#include <stdint.h>
#include "host.h"

class Byte
{
	uint8_t byte;
public:
	Byte();
	Byte(const uint8_t byte);
	Byte(const uint8_t high, const uint8_t low);
	uint8_t low() const;
	uint8_t high() const;
	uint8_t get() const;
	std::string	get_str() const;
	void set(const uint8_t high, const uint8_t low);

	bool operator==(const Byte &other) const;
};
