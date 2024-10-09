#include "client.hpp"

// int main (){
// 	Client _client;
// 	_client._creatingClientSocketFd();
// 	if (_client.get_clientSocketFd()){
// 			std::cout << "client socketFD passed" << std::endl;
// 		if (_client._creatingClientConnection() == 0){
// 			std::cout << "client connection established" << std::endl;
// 		}
// 		else
// 			std::cout << "client connection failed" << std::endl;
// 		while(1) {
// 			std::string input;
// 			std::getline(std::cin, input);
// 			_client._clientSendingMesssage(input);
// 		}
// 	}
// 	else
// 		std::cout << "client sockedFd here failed" << _client.get_clientSocketFd() << std::endl;
// }

#include <thread>

// Inside your main function:
int main() {
    Client _client;
    _client._creatingClientSocketFd();
    
    if (_client.get_clientSocketFd()) {
        std::cout << "client socketFD passed" << std::endl;
        if (_client._creatingClientConnection() == 0) {
            std::cout << "client connection established" << std::endl;

            // Create a thread for receiving messages
            std::thread receiveThread(&Client::_recieve, &_client);
            receiveThread.detach(); // Detach the thread to run independently

            while (1) {
                std::string input;
                std::getline(std::cin, input);
                _client._clientSendingMesssage(input);
            }
        } else {
            std::cout << "client connection failed" << std::endl;
        }
    } else {
        std::cout << "client socketFd here failed" << _client.get_clientSocketFd() << std::endl;
    }
}
