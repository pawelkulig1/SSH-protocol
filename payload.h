#pragma once
#include <vector>
#include <stdint.h>
#include <string>
#include "byte.h"

class Payload
{
	std::vector<Byte> raw_payload;
public:
	Payload();
	Payload(Byte byte);
	Payload(std::vector<Byte> byte_vec);
	Payload(const Payload &payload);
	Payload(std::string str, bool ascii=false);

	void operator=(const Payload &payload);

	void next(Byte byte);
	void next(std::vector<Byte> vec);
	void next(std::string str, bool ascii=false);
	void next(const Payload &payload);

	std::vector<Byte> 	get_payload_vec() const;
	std::string    	 	get_payload_str() const;
	void reserve(const unsigned int reservation);
	size_t size() const;
	void clear();
};
