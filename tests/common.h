#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#define ASSERT(NAME, x, y) \
	if(x != y) \
	{ \
		std::cout << std::left << std::setw(60) << \
			NAME << " FAILED in LINE: " << __LINE__  << " expected: " << std::endl; \
	} \
   	else \
	{ \
		std::cout << std::left << std::setw(60) << NAME << " PASSED"<<std::endl; \
	}


inline std::vector<uint8_t> empty_payload_generator(int size)
{
	std::vector<uint8_t> temp_vec;
	temp_vec.reserve(size);
	for (int i=0;i<size;i++){
		temp_vec.push_back(0x0);
	}
	return temp_vec;
}
