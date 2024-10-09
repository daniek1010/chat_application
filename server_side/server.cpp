#include "server.hpp"

int server::_creatingServerSocketFd(){
	serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocketFD < 0 ){
		std::cout << "socket creation faliled\n" << std::endl;
		return (1);
	}
	return (0);
}

int server::_serverReservePortandIpBind(){
	std::string ip = "127.0.0.1";
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(4100);
	inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
	if (bind(serverSocketFD, (const struct sockaddr *)&address, sizeof(address)) < 0){
		return (std::cout << "binding faliled\n" << std::endl, 1);
	}
	return (0);

}

int server::_serverListens() {
	if (listen(serverSocketFD, SOMAXCONN) < 0) {
		std::cout << "lsiten faliled\n" << std::endl;
		return (1);
	}
	return (0);
}

int server::_serverAccpetIncoming(){
	int	clientSocketFD;
	socklen_t clientAddrLen;
	struct sockaddr_in clientAddr;
	clientAddrLen = sizeof(clientAddr);
	clientSocketFD = accept(serverSocketFD, (struct sockaddr *) &clientAddr, &clientAddrLen);
	if (clientSocketFD  < 0) {
		std::cout << "accept faliled\n" << std::endl;
		return (1);
	}
	return (clientSocketFD);
}

int server::run_server(void) {
	epfd = epoll_create1(0);
	if (_createBindListen() == 1)
		return (1);
	server_event = initEpollEvant(EPOLLIN, serverSocketFD);
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, serverSocketFD, server_event) == -1)
		return (1);
	while (1) {
		epoll_waitfd = epoll_wait(epfd, server_event_gotten, 100, -1);
		if (epoll_waitfd < 0)
			return (1);
		for (int i = 0; i < epoll_waitfd; i++) {
			if (server_event_gotten[i].data.fd == serverSocketFD) {
				clientSocketFD = _serverAccpetIncoming();
				if ( clientSocketFD == -1)
					return (1);
				client_ArrayFd.push_back(clientSocketFD);
				client_event = initEpollEvant(EPOLLIN, clientSocketFD);
				if (epoll_ctl(epfd, EPOLL_CTL_ADD, clientSocketFD, client_event) == -1)
					return (1);
			}
			else {
				_receveAndSend(server_event_gotten[i].data.fd, epfd, client_ArrayFd);
			}
		}
	}
	_closeFd();
}

int server::_createBindListen(){
	if (_creatingServerSocketFd() == 1)
		return (1);
	if (_serverReservePortandIpBind() == 1)
		return (1);
	if (_serverListens() == 1)
		return (1);
	return (0);
}


 epoll_event* server::initEpollEvant(int x, int socketFd) {
	epoll_event* events = new epoll_event;
	events->data.fd = socketFd;
	events->events = x;
	return events;

}

void server::_receveAndSend(int sender, int epfd, std::vector <int> client_ArrayFd) {
	server _server;
	int clientSendMsg;
	clientSendMsg = sender;
	std::string buff = _server._recieve(clientSendMsg);
	if (buff.empty()) {
		epoll_ctl(epfd, EPOLL_CTL_DEL, clientSendMsg, NULL);
		close(clientSendMsg);
    }
	else {
		for (int clientSocketFD : client_ArrayFd){
			if (clientSocketFD != clientSendMsg)
				_server._send(buff, clientSocketFD);

			}
	}
}

const std::string server::_recieve(int clientSocketFd){
	std::string buffer(1024, '\0');
	size_t bytes = recv(clientSocketFd, &buffer[0], buffer.size(), 0);
	if (bytes <= 0)
		return (0);
	buffer.resize(bytes);
	return (buffer);
}

int server::_getter_serverSocketFD(void) const {
	return (serverSocketFD);
}

void server::_send(const std::string &buff, int client_fd) {
    if (send(client_fd, buff.c_str(), buff.size(), 0) < 0) {
        std::cerr << "Failed to send message to client with fd: " << client_fd << std::endl;
    }
}

void server::_closeFd(){
	close (serverSocketFD);
	for (int i : client_ArrayFd)	
		close (i);
}

server::~server(){
	std::cout << "destructor called" << std::endl;
}