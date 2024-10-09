#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class server {
	public:
		server (void){};
		void _creatingServerSocketFd();
		int _serverReservePortandIpBind();
		int _serverListens();
		int _serverAccpetIncoming();
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