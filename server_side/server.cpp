#include "server.hpp"

void server::_creatingServerSocketFd(){
	serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocketFD < 0 ){
		std::cout << "socket creation faliled\n" << std::endl;
		return ;
	}
	std::cout << "socket creation success\n" << std::endl;
}

int server::_serverReservePortandIpBind(){
	std::string ip = "127.0.0.1";
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(4242);
	inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
	if (bind(serverSocketFD, (const struct sockaddr *)&address, sizeof(address)) < 0){
		return (std::cout << "binding faliled\n" << std::endl, 1);
	}
	return (0);

}

int server::_serverListens(){
	if (listen(serverSocketFD, SOMAXCONN) < 0){
		std::cout << "lsiten faliled\n" << std::endl;
		return (-1);
	}
	std::cout << "connection listening on port 4242 " << std::endl;
	return (0);
}

int server::_serverAccpetIncoming(){
	socklen_t clientAddrLen;
	struct sockaddr_in clientAddr;
	clientAddrLen = sizeof(clientAddr);
	int clientSocketFd = accept(serverSocketFD, (struct sockaddr *) &clientAddr, &clientAddrLen);
	if (clientSocketFd  < 0){
		std::cout << "accept faliled\n" << std::endl;
	}
	std::cout << "connection established " << std::endl;
	return clientSocketFd ;	

}


// int server::_closeFd(){

// }

const std::string server::_recieve(int clientSocketFd){
	std::string buffer(1024, '\0');
	size_t bytes = recv(clientSocketFd, &buffer[0], buffer.size(), 0);
	buffer.resize(bytes);
	return (buffer);
}


int server::getter_socket_fd(void) const{
	return (serverSocketFD);
}

server::~server(){
	std::cout << "destructor called" << std::endl;
}

// int server::_connect(){
// 	int connect_id;
// 	const char *ip = "142.250.189.174";
// 	struct sockaddr_in address;
// 	address.sin_family = AF_INET;
// 	address.sin_port = htons(80);
// 	inet_pton(AF_INET, ip, &address.sin_addr);
// 	connect_id = connect(serverSocketFD, (const struct sockaddr *)&address, sizeof (address));
// 	if (connect_id){
// 		std::cout << "socket creation faliled" << std::endl;
// 		return -1;
// 	}
// 	else
// 		std::cout << "socket creation successful" << std::endl;
// 	return 0;

// }

// void server::_send(std::string message){
// 	send(serverSocketFD, message.c_str(), sizeof(message), 0);
// }
