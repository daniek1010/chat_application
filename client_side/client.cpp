#include "client.hpp"


Client::Client() : NetworkEntity() {
	std::cout << "default constructor called " << std::endl;
}

int Client::_socket() {
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFD < 0 ){
		std::cout << "socket creation faliled\n" << std::endl;
		return -1;
	}
	return (socketFD);
}

int Client::_connect(){
	int connect_id;
	const char *ip = "142.250.189.174";
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(80);
	inet_pton(AF_INET, ip, &address.sin_addr);
	connect_id = connect(socketFD, (const struct sockaddr *)&address, sizeof (address));
	if (connect_id){
		std::cout << "socket creation faliled" << std::endl;
		return -1;
	}
	else
		std::cout << "socket creation successful" << std::endl;
	return 0;

}

void Client::_send(std::string message){
	send(socketFD, message.c_str(), sizeof(message), 0);
}

const std::string Client::_recieve(){
	std::string buffer(1024, '\0');
	std::cout << socketFD << std::endl;
	size_t bytes = recv(socketFD, &buffer[0], buffer.size(), 0);
	buffer.resize(bytes);
	return (buffer);
}


int Client::getter_socket_fd(void) const{
	return (socketFD);
}

Client::~Client(){
	std::cout << "destructor called" << std::endl;
}

