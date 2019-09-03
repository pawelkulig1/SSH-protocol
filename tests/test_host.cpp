#include <array>
#include <vector>
#include <utility>
#include <string>
#include "common.h"
#include "../host.h"

void get_ip_address_suite()
{
	const std::string name = "get_ip_address_suite";
	typedef std::pair<std::string, uint32_t> ip_pair;
	std::vector<ip_pair> test_vec = {
		ip_pair("192.168.0.23", 0xC0A80017),
		ip_pair("0.0.0.0", 0x0),
		ip_pair("127.0.0.1", 0x7F000001),
		ip_pair("255.255.255.255", 0xFFFFFFFF),
		ip_pair("1.1.1.1", 0x01010101)
	}; 

	std::cout<< name << std::endl;
	for (const ip_pair pair: test_vec)  
		ASSERT(pair.first, Host::get_ip_address(pair.first), pair.second);
}

void payload_from_ascii_suite()
{
	const std::string name = "payload_from_ascii_suite";
	typedef std::pair<std::string, std::vector<uint8_t>> test_pair;
	std::vector<test_pair> test_vec = {
		test_pair("SSH", {0x53, 0x53, 0x48}),
		test_pair("-2.0", {0x2d, 0x32, 0x2e, 0x30}),
		test_pair("OpenSSH_7.9", {0x4f, 0x70, 0x65, 0x6e, 0x53, 0x53, 0x48, 0x5f, 0x37, 0x2e, 0x39}),
		test_pair("ala ma kota", {97, 108, 97, 32, 109, 97, 32, 107, 111, 116, 97})
	};

	std::cout << std::endl << name << std::endl;
	for (const test_pair pair: test_vec)
		ASSERT(pair.first, Host::payload_from_ascii(pair.first), pair.second);
}

void payload_from_hex_suite()
{
	const std::string name = "payload_from_hex_suite";
	typedef std::pair<std::string, std::vector<uint8_t>> test_pair;
	std::vector<test_pair> test_vec = {
		test_pair("535348", {0x53, 0x53, 0x48}),
		test_pair("2d322e30", {0x2d, 0x32, 0x2e, 0x30}),
		test_pair("4f70656e5353485f372e39", {0x4f, 0x70, 0x65, 0x6e, 0x53, 0x53, 0x48, 0x5f, 0x37, 0x2e, 0x39})
	};

	std::cout << std::endl << name << std::endl;
	for (const test_pair pair: test_vec)
		ASSERT(pair.first, Host::payload_from_hex(pair.first), pair.second);

}


void main_host_test()
{
	typedef void (*suite_ptr)();
	std::array<suite_ptr, 3> suite = {
		&get_ip_address_suite,
		&payload_from_ascii_suite,
		&payload_from_hex_suite
	};
	for (suite_ptr s: suite)
	{
		s();
	}
}
