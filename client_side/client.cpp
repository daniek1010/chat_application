#include "client.hpp"

Client::Client() {
	std::cout << "client default constructor called " << std::endl;
}

int Client::_creatingClientSocketFd() {
	clinetSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (clinetSocketFD < 0 ){
		std::cout << "client creation faliled\n" << std::endl;
		return -1;
	}
	return (clinetSocketFD);
}

int Client::_creatingClientConnection(std::string buff_port, std::string client_name, std::string client_recieve) { 
	int connect_id;
	int port = std::atoi(buff_port.c_str());
	const char *ip = "127.0.0.1";
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ip, &address.sin_addr);
	connect_id = connect(clinetSocketFD, (const struct sockaddr *)&address, sizeof (address));
	if (connect_id < 0){
		std::cout << "client creation faliled" << connect_id << std::endl;
		return -1;
	}
	_clientSendingMesssage(client_name);
	_clientSendingMesssage(client_recieve);
	return 0;

}

void Client::_clientSendingMesssage(std::string message) {
	std::string newMsg = message + "\n";
    send(clinetSocketFD, newMsg.c_str(), newMsg.size(), 0);
}

int Client::get_clientSocketFd(void) const{
	return (clinetSocketFD);
}

void Client::_recieve(){
	char buffer[1024];
	while (true) {
		ssize_t bytes_received = recv(get_clientSocketFd(), buffer, sizeof(buffer) - 1, 0);
		if (bytes_received > 0) {
			buffer[bytes_received] = '\0';
			std::cout << buffer << std::endl;
		} else if (bytes_received == 0) {
			std::cout << "Server disconnected." << std::endl;
			break;
		} else {
			std::cerr << "Error receiving message." << std::endl;
			break;
		}
	}
}

Client::~Client(){
	std::cout << "client destructor here called" << std::endl;
}

