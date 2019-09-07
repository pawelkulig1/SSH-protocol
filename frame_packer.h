#pragma once
#include <vector>
#include <stdint.h>
#include <string>

class FramePacker
{
	std::vector<uint8_t> raw_payload;
public:
	FramePacker();
	void next(uint8_t byte);
	void next(std::vector<uint8_t> vec);
	void next(std::string str, bool ascii=false);

	void size_next(uint8_t byte, size_t size_bytes=4);
	void size_next(std::vector<uint8_t> vec, size_t size_bytes=4);
	void size_next(std::string str, size_t size_bytes=4, bool ascii=false);

	std::vector<uint8_t> get_payload() const;
};
