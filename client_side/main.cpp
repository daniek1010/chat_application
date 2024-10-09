#include "client.hpp"

int main (){
	Client _client;
	_client._creatingClientSocketFd();
	if (_client.get_clientSocketFd()){
			std::cout << "socketFD passed" << std::endl;
		if (_client._creatingClientConnection() == 0){
			std::cout << "connection established" << std::endl;
		}
		else
			std::cout << "connection failed" << std::endl;
		while(1) {
			std::string input;
			std::getline(std::cin, input);
			_client._clientSendingMesssage(input);
		}
	}
	else
		std::cout << "sockedFd here failed" << _client.get_clientSocketFd() << std::endl;
}