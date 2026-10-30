#include <stdio.h>
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 6767 
#define BUFFER_SIZE 1024

int main() {
	int sock, n;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in server;
	fd_set readfds;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("connection failed");
		close(sock);
		return 1;
	}

	printf("Connected to chat. Type messages below\n");

	while (1) {
		FD_ZERO(&readfds);
		FD_SET(STDIN_FILENO, &readfds);
		FD_SET(sock, &readfds);

		select(sock+1, &readfds, NULL, NULL, NULL);

		if (FD_ISSET(STDIN_FILENO, &readfds)) {
			if (fgets(buffer, sizeof(buffer), stdin) == NULL)
				break; 
			
			if (send(sock, buffer, strlen(buffer)-1, 0) < 0)
				break;
		}

		if (FD_ISSET(sock, &readfds)) {
			n = recv(sock, buffer, sizeof(buffer)-1, 0);
			if (n <= 0) {
				printf("Disconnected from server\n");
				break;
			}

			buffer[n] = '\0';
			printf("%s\n", buffer);
		}
	}

	close(sock);
	return 0;
}