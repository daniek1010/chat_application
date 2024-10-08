#include "./client_side/client.hpp"

int main (){
	Client _client;
	_client._socket();
	if (_client.getter_socket_fd()){
			std::cout << "socketFD passed" << std::endl;
		if (_client._connect() == 0){
			std::cout << "connection established" << std::endl;
		}
		else
			std::cout << "connection failed" << std::endl;
	}
	else
		std::cout << "sockedFd failed" << _client.getter_socket_fd() << std::endl;
}