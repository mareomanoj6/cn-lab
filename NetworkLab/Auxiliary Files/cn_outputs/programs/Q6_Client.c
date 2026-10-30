#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 6767

int main() {
	int sock;
	struct sockaddr_in server;
	char result[4096], sentence[1024];
	socklen_t len = sizeof(server);

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("Enter sentence: ");
	scanf(" %[^\n]", sentence);

	sendto(sock, sentence, strlen(sentence), 0, (struct sockaddr *) &server, len);
	int n = recvfrom(sock, result, sizeof(result)-1, 0, (struct sockaddr *) &server, &len);
	if (n <= 0) {
		close(sock);
		return 1;
	}

	result[n] = '\0';
	printf("Obtained translation: %s\n", result);

	close(sock);
	return 0;
}