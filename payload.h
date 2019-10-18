#pragma once
#include <vector>
#include <stdint.h>
#include <string>
#include "byte.h"

class Payload
{
	std::vector<Byte> raw_payload;
	void next_zeros(const size_t bytes);
	static int get_counter;
public:
	Payload();
	Payload(const Byte byte);
	Payload(const Byte byte, const size_t bytes);
	Payload(const std::vector<Byte>& byte_vec);
	Payload(const std::vector<Byte>& byte_vec, const size_t bytes);
	Payload(const Payload &payload);
	Payload(const Payload &payload, const size_t bytes);
	Payload(const std::string& str, const size_t bytes=0, bool ascii=false);
	Payload(const uint8_t* c_str, const size_t size);
	Payload(const uint8_t* c_str, const size_t size, const size_t bytes);
	Payload(const std::vector<Byte>::const_iterator beg, const std::vector<Byte>::const_iterator end);
	
	void operator=(const Payload &payload);
	Byte at(const int index) const;
	std::vector<Byte>::const_iterator begin() const;
	std::vector<Byte>::const_iterator end() const;

	void next(Byte byte);
	void next(const Byte byte, const size_t bytes);
	void next(const std::vector<Byte>& vec);
	void next(const std::vector<Byte>& vec, const size_t bytes);
	void next(const std::string& str, const size_t bytes=0, const bool ascii=false);
	void next(const Payload &payload);
	void next(const Payload &payload, const size_t bytes);
	void next(const uint8_t* c_str, size_t size);
	void next(const uint8_t* c_str, const size_t size, const size_t bytes);
	void next(const uint32_t data, const size_t bytes=4);

	Payload remove(const long unsigned int beg, const long unsigned int size) const;
	Payload get(const long unsigned int beg, const long unsigned int size) const;
	Payload get(const long unsigned int size) const;

	template <typename T>
	T get(const long unsigned int beg, const long unsigned int size) const;

	template <typename T>
	T get(const long unsigned int size) const;

	std::vector<Byte> 	get_vec() const;
	std::string    	 	get_str() const;
	void 				print() const;
	void reserve(const unsigned int reservation);
	size_t size() const;
	void clear();
};
