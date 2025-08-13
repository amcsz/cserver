#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
// https://pubs.opengroup.org/onlinepubs/009695399/basedefs/netinet/in.h.html
#include <netinet/in.h>

int main() {
	// create the socket
	int socket_fd;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	// specify the address for the server end
	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET; // AF_NET means IPv4
	server_addr.sin_port = htons(8000); // Connect to port 8000
	server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces on host machine, which lets other devices on the same network connect to it

	int connection_status = connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
	
	// check for error with connection
	if (connection_status == -1) {
		printf("There was an error in establishing a connection with the remote server!\n");
	}
	
	// try to receive data
	char response[256];
	recv(socket_fd, &response, sizeof(response), 0);

	printf("Received data from the server: %s\n", response);

	// close socket
	close(socket_fd);	
	return 0;
}
