#pragma once
#include <openssl/err.h>

namespace SSH {
inline void handle_error()
{
	unsigned long err = ERR_get_error();
	char *buf = new char[512];
	ERR_error_string(err, buf);
	std::cout<<buf<<std::endl;
	delete[] buf;
}
} //namespace SSH
