#include "server.hpp"

int main (int ac, char **argv){
	if (ac != 2)
		return 0;
	server _server;
	_server.run_server(argv[1]);


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