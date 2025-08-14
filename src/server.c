#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
	FILE *html_data;
	html_data = fopen("src/www/index.html", "r");

	if (html_data == NULL) {
		printf("Error opening file.\n");
		return 1;
	}

	char buf[1024];
	char http_headers[2048] = "HTTP/1.1 200 OK\r\n\n";

	while (fgets(buf, sizeof(buf), html_data) != NULL) {
		strcat(http_headers, buf);
	}

	fclose(html_data); 

	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8000);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind to port	
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	// listen for connections	
	listen(server_socket, 10); // 2nd arg is max backlog 

	int client_socket;

	while (1) {
		client_socket = accept(server_socket, NULL, NULL);
		
		char buffer[1024] = {0};
		read(client_socket, buffer, 1024);
		printf("Received: %s\n", buffer);

	
		send(client_socket, http_headers, sizeof(http_headers), 0);
		close(client_socket);
	}
	
	close(server_socket);
	return 0;
}
