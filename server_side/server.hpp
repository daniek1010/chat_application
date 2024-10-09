#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>


class server {
	public:
		server (void){};
		int _creatingServerSocketFd();
		int _serverReservePortandIpBind();
		int _serverListens();
		int _serverAccpetIncoming();
		int _serverThread ();
		void _closeFd();
		epoll_event* initEpollEvant(int x, int socketFd);
		int run_server(void);
		int _createBindListen();
		void _send(const std::string &buff, int client_fd);
		const std::string _recieve(int clientSocketFd);
		void _receveAndSend(int sender, int epfd, std::vector <int> client_ArrayFd);
		int _getter_serverSocketFD(void) const;
		~server();
	private:
		int epoll_waitfd;
		int epfd;
		int serverSocketFD;
		int clientSocketFD;
		std::vector<int> client_ArrayFd;
		struct epoll_event* server_event;
		struct epoll_event* client_event;
		struct epoll_event server_event_gotten[100];
};
// int run_server(void);
#endif