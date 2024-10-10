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
#include <optional>
#include <fcntl.h>


class server {
	public:
		server (void){};

		struct clientDetails {
			int clientfd;
			std::string clientName;
			std::string clientRecevingMsg;
		};
		clientDetails data;
		std::vector<clientDetails> clients_info;

		int _creatingServerSocketFd();
		int _serverReservePortandIpBind(std::string buff_port);
		int _serverListens();
		clientDetails _serverAcceptIncoming(); 
		// std::optional<clientDetails> _serverAccpetIncoming();
		// int _serverThread ();
		void _closeFd();
		epoll_event* initEpollEvant(int x, int socketFd);
		int run_server(std::string buff_port);
		int _createBindListen(std::string buff_port);
		void _send(const std::string &buff, int client_fd);
		const std::string _recieve(int clientSocketFd);
		void _receveAndSend(int sender, int epfd, std::vector <clientDetails> clients_info);
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