#include "socket_class.h"
#include "../host.h"
#include <iostream>
#include <errno.h>


const sockaddr_in SocketClass::make_socket_struct()
{
    sockaddr_in sa;
    sa.sin_family = PF_INET;
    sa.sin_port = htons(port);
    in_addr i_a;
    i_a.s_addr = Host::get_ip_address(ip);
    sa.sin_addr = i_a; 
	return sa;
}

SocketClass::SocketClass(): SocketClass("127.0.0.1", 32768)
{
}

SocketClass::SocketClass(std::string destination_ip): SocketClass(destination_ip, 5005)
{
}

SocketClass::SocketClass(std::string destination_ip, int port): ip(destination_ip), port(port)
{
    sock = socket(PF_INET, SOCK_STREAM, 0);
	std::cout<<"socket created" << std::endl;
}

void SocketClass::connect()
{
	sockaddr_in sa = make_socket_struct();
    conn = ::connect(sock, reinterpret_cast<sockaddr *>(&sa), sizeof(sa));
	if(conn) throw(std::system_error(
				std::make_error_code(std::errc::connection_refused), 
				strerror(errno)
				));
}

ssize_t SocketClass::send(std::vector<uint8_t> data)
{
	uint8_t *buff = new uint8_t[data.size()]; 
	std::memcpy(buff, data.data(), data.size());
	ssize_t status = ::send(sock, buff, data.size(), MSG_DONTROUTE);
	if(status == -1)
	{
		throw(std::system_error(std::make_error_code(std::errc::not_connected), strerror(errno)));
	}
	delete[] buff;
	buff = nullptr;
	return status;
}

ssize_t SocketClass::send(const Payload &payload)
{
	uint8_t *buff = new uint8_t[payload.size()];
	for(long unsigned int i=0;i<payload.size();i++)
	{
		buff[i] = payload.at(i).get();
	}
	ssize_t status = ::send(sock, buff, payload.size(), MSG_DONTROUTE);
	if(status == -1)
	{
		throw(std::system_error(std::make_error_code(std::errc::not_connected), strerror(errno)));
	}
	delete[] buff;
	buff = nullptr;
	return status;
	//return send(payload.get_vec());	
}

Payload SocketClass::recv()
{
	void *buffer = new uint8_t[buffer_size];
	ssize_t size = ::recv(sock, buffer, buffer_size, 0);
	uint8_t *buff_ptr = reinterpret_cast<uint8_t*>(buffer);
	Payload p = Payload(buff_ptr, size);
	//std::vector<uint8_t> ret_vec(buff_ptr, buff_ptr + size);

	delete[] buff_ptr;
	buff_ptr = nullptr;
	buffer = nullptr;
	return p;
}
