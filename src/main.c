#include "response.h"
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

#define MY_SOCK_ADDR "127.0.0.1"
#define MY_SOCK_PORT 5555

/* Macro that gets plugged in during pre-processing. The while (0)
 makes it so that the function can be called followed by a semi-colon.
 */
#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)


int main() {
	// Socket setup
	struct protoent *tcpProtoEnt = getprotobyname("tcp");
	struct sockaddr_in my_addr;
	const int TCP_PROTO_NUM = tcpProtoEnt -> p_proto;

	// -- 1. Create socket
	int SOCK_FD = socket(AF_INET, SOCK_STREAM, TCP_PROTO_NUM);

	if (SOCK_FD == -1) {
		handle_error("socket");
	}

	// Bind setup
	uint32_t byte_addr;
	uint16_t byte_port;

	// Converts address string to bytes in network byte order (big-endian)
	inet_pton(AF_INET, MY_SOCK_ADDR, &byte_addr);

	// Converts port to bytes in network byte order (big-endian)
	byte_port = htons(MY_SOCK_PORT);

	// Initialize addr object
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = byte_addr;
	my_addr.sin_port = byte_port;

	// Set socket option to allow bound addresses to be re-used. This
	// was added to allow the program to be closed, then re-run immediately.
	// Without this option, the program may error out because the address 
	// will show as being already in use.
	int reuse = 1;
	if (setsockopt(SOCK_FD, SOL_SOCKET, SO_REUSEADDR, (void *)&reuse, sizeof(reuse)) < 0) {
		handle_error("socket-option");
	}

	// --  2. Bind socket
	if (bind(SOCK_FD, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1) {
		handle_error("bind");
	}

	// -- 3. Receive client connection
	// This program wills start a web server process. Listen on the socket and enqueue up to n connections awaiting connection.
	listen(SOCK_FD, 5);
	
	while (1) {
		printf("Listening on port %d...\n", MY_SOCK_PORT);

		// Accept the next connection in the queue and create a new socket and FD representing that connection.
		int newSock = accept(SOCK_FD,NULL, NULL);

		if (newSock == -1) {
			handle_error("accept");
		}

		printf("Connection established, FD: %d\n\n", newSock);

		char buffer[1000];

		ssize_t bytesReturned = read(newSock, &buffer, sizeof(buffer));

		if (bytesReturned == -1) {
			handle_error("read");
		}
		// null terminator so that left-over bytes in the buffer won't be printed
		buffer[bytesReturned] = '\0';

		printf("Request, raw content:\n\n%s", buffer);

		char header[] = 
			"HTTP/1.0 200\r\n"
			"Content-Type: text/html\r\n";

		char *template = "templates/index.html";

		// Reads HTML file 
		char *responseBody = readFile(template);

		if (responseBody == NULL) {
			handle_error("read file");
		}

		// the header and body needs to be separated by an empty line as per section 4.1 of the HTTP 1.0 spec
		char *response = strcat(header, "\r\n"); 

		response = strcat(header, responseBody);

		// -- 5. Write the response
		ssize_t bytesSent = write(newSock, response, strlen(response));

		if (bytesReturned == -1) {
			handle_error("write");
		}

		int closeAttempt = close(newSock);

		if (closeAttempt == -1) {
			handle_error("close");
		}

		// malloc() was used to move template string from a separate method.
		free(responseBody);
	}

	return 0;
}

