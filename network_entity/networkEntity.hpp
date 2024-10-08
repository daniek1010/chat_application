#ifndef NETWORK_ENTITY_HPP
#define NETWORK_ENTITY_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class NetworkEntity{
	public:
		NetworkEntity (void){};
		virtual int _socket() = 0;
		virtual int _connect() = 0;
		virtual void _send(std::string message) = 0;
		virtual const std::string _recieve() = 0;
		virtual int getter_socket_fd(void) const = 0;
		virtual ~NetworkEntity(){};
	protected:
		int socketFD;
};

#endif