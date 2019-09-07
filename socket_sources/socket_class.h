#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <memory>
#include <vector>
#include <string>
#include <cstring>
#include <arpa/inet.h>

class SocketClass
{
    int sock;
    int conn;
	int domain;
	int connection_type;
	int protocol;
	std::string ip = "0.0.0.0";
	int port = 5005; //ssh port
	constexpr static int buffer_size = 4096;

	const sockaddr_in make_socket_struct();

public:
    SocketClass();
	SocketClass(std::string destination_ip);
	SocketClass(std::string destination_ip, int port);
	void connect();
	ssize_t send(const std::vector<uint8_t> data);
	std::vector<uint8_t> recv();
};
