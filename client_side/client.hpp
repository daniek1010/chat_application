#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Client {
	public:
		Client (void);
		int _creatingClientSocketFd();
		int _creatingClientConnection();
		void _clientSendingMesssage(std::string message);
		const std::string _recieve();
		int get_clientSocketFd(void) const;
		~Client();
	private:
		int clinetSocketFD;
};

#endif