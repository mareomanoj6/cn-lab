#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 6767
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
	int server, client, clients[MAX_CLIENTS];
	int i, maxfd, n;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	fd_set readfds;

	server = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(server, (struct sockaddr *) &addr, len);
	listen(server, 5);

	for (i=0; i < MAX_CLIENTS; i++)
		clients[i] = 0;
	
	printf("Chat server is running on port %d...\n", PORT);

	while (1) {
		FD_ZERO(&readfds);
		FD_SET(server, &readfds);
		maxfd = server;

		for (i=0; i < MAX_CLIENTS; i++) {
			if (clients[i] > 0)
				FD_SET(clients[i], &readfds);
			if (clients[i] > maxfd)
				maxfd = clients[i];
		}

		select(maxfd+1, &readfds, NULL, NULL, NULL);

		if (FD_ISSET(server, &readfds)) {
			client = accept(server, (struct sockaddr *) &addr, &len);

			for (i=0; i < MAX_CLIENTS; i++) {
				if (clients[i] == 0) {
					clients[i] = client;
					break;
				}
			}

			if (i == MAX_CLIENTS)
				close(client);
			else
				printf("Client connected: socket %d\n", client);
		} 

		for (i=0; i < MAX_CLIENTS; i++) {
			client = clients[i];

			if (client > 0 && FD_ISSET(client, &readfds)) {
				n = recv(client, buffer, sizeof(buffer), 0);

				if (n <= 0) {
					printf("Client disconnected: socket %d\n", client);
					close(client);
					clients[i] = 0;
				} else {
					for (int j=0; j < MAX_CLIENTS; j++) {
						if (clients[j] > 0 && clients[j] != client) {
							send(clients[j], buffer, n, 0);
						}
					}
				}
			}
		}
	}

	close(server);
	return 0;
}