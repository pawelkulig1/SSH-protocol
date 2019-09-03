#include "frame_packer.h"
#include "host.h"
#include <system_error>

FramePacker::FramePacker() {}
void FramePacker::next(uint8_t byte)
{
	raw_payload.push_back(byte);
}

void FramePacker::next(std::vector<uint8_t> vec)
{
	raw_payload.insert(raw_payload.end(), vec.begin(), vec.end());
}

void FramePacker::next(std::string str, bool ascii)
{
	next(ascii ? Host::payload_from_ascii(str) : Host::payload_from_hex(str));
}

void FramePacker::size_next(uint8_t byte, size_t size_bytes)
{
	for (size_t i=0;i<size_bytes-1;i++)
	{
		raw_payload.push_back(0);
	}
	raw_payload.push_back(1);
}

void FramePacker::size_next(std::vector<uint8_t> vec, size_t size_bytes)
{
	if (size_bytes > 4)
		throw std::system_error(std::make_error_code(std::errc::invalid_argument), "size_bytes must be less than 5");
	
	uint32_t size = vec.size();
	uint8_t *ptr = reinterpret_cast<uint8_t *>(size);
		
	for (size_t i=0;i<(4 - size_bytes);i++)
	{
		raw_payload.push_back(ptr[4 - size_bytes + i]);
	}
}

void FramePacker::size_next(std::string str, size_t size_bytes, bool ascii)
{
	size_next(ascii ? Host::payload_from_ascii(str) : Host::payload_from_hex(str), size_bytes);
}

std::vector<uint8_t> FramePacker::get_payload() const
{
	return raw_payload;
}
