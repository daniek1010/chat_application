#include "server.hpp"

int main (){
	server _server;
	_server._creatingServerSocketFd();
	if (_server._serverReservePortandIpBind() == 1)
		return 0;
	_server._serverListens();
	int clientSocketFd = _server._serverAccpetIncoming();
	while (1){
		std::string buff = _server._recieve(clientSocketFd);
		std::cout << buff << std::endl;
		buff.clear();
	}


	// _client._socket();
	// if (_client.getter_socket_fd()){
	// 		std::cout << "socketFD passed" << std::endl;
	// 	if (_client._connect() == 0){
	// 		std::cout << "connection established" << std::endl;
	// 	}
	// 	else
	// 		std::cout << "connection failed" << std::endl;
	// }
	// else
	// 	std::cout << "sockedFd failed" << _client.getter_socket_fd() << std::endl;
}