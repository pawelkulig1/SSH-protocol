#pragma once

#include <iostream>
#include <iomanip>
//#define ASSERT(x, y) (x+y)
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


#define ASSERT_VECTOR(NAME, x, y) \

