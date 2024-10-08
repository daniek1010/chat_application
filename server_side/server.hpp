#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./network_entity/networkEntity.hpp"

class Client {
	public:
		Client (void){};
		int _socket();
		int _connect();
		void _send(std::string message);
		const std::string _recieve();
		int getter_socket_fd(void) const;
		~Client();
	private:
		int socketFD;
};

#endif