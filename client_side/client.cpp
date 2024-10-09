#include "client.hpp"

Client::Client() {
	std::cout << "default constructor called " << std::endl;
}

int Client::_creatingClientSocketFd() {
	clinetSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (clinetSocketFD < 0 ){
		std::cout << "socket creation faliled\n" << std::endl;
		return -1;
	}
	return (clinetSocketFD);
}

int Client::_creatingClientConnection() { 
	int connect_id;
	const char *ip = "127.0.0.1";
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(4242);
	inet_pton(AF_INET, ip, &address.sin_addr);
	connect_id = connect(clinetSocketFD, (const struct sockaddr *)&address, sizeof (address));
	if (connect_id < 0){
		std::cout << "socket creation faliled" << connect_id << std::endl;
		return -1;
	}
	else
		std::cout << "socket creation successful" << std::endl;
	return 0;

}

void Client::_clientSendingMesssage(std::string message) {
    send(clinetSocketFD, message.c_str(), message.size(), 0);
}

int Client::get_clientSocketFd(void) const{
	return (clinetSocketFD);
}

const std::string Client::_recieve(){
	std::string buffer(1024, '\0');
	std::cout << clinetSocketFD << std::endl;
	size_t bytes = recv(clinetSocketFD, &buffer[0], buffer.size(), 0);
	buffer.resize(bytes);
	return (buffer);
}

Client::~Client(){
	std::cout << "destructor called" << std::endl;
}

