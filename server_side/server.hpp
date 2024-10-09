#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../network_entity/networkEntity.hpp"

class server {
	public:
		server (void){};
		void _socket();
		void _bind();
		int _listen();
		int _accpet();
		// int _connect();
		// int _closeFd();

		// void _send(std::string message);
		const std::string _recieve(int clientSocketFd);
		int getter_socket_fd(void) const;
		~server();
	private:
		int serverSocketFD;
};

#endif