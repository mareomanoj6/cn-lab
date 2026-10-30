#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 6767

char *slang[] = {"tbh", "ig", "tbf", "atm", "irl", "lol","asap", "omg", "ttyl", "idk", "nvm"};
char *normal[] = {"to be honest", "I guess", "to be fair","at the moment", "in real life", "laughing out loud","as soon as possible", "oh my god", "talk to you later","I don't know", "never mind"};

void translate(char *sentence, char *result) {
    char word[100];
    int i = 0, j, k;
    result[0] = '\0';
    while (sentence[i] != '\0') {
        if (!isalpha((unsigned char)sentence[i])) {
            int len = strlen(result);
            result[len] = sentence[i++];
            result[len + 1] = '\0';
            continue;
        }
        j = 0;
        while (isalpha((unsigned char)sentence[i]) && j < 99)
            word[j++] = sentence[i++];
        word[j] = '\0';

        int found = 0;
        for (k = 0; k < 11; k++)
            if (strcasecmp(word, slang[k]) == 0) {
                strcat(result, normal[k]);
                found = 1;
                break;
            }
        if (!found)
            strcat(result, word);
    }
}

int main() {
	int sock;
	char sentence[1024], result[4096];
	struct sockaddr_in server, client;
	socklen_t len = sizeof(client);

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;

	bind(sock, (struct sockaddr *) &server, sizeof(server));

	printf("Waiting for client...\n");

	int n = recvfrom(sock, sentence, sizeof(sentence)-1, 0, (struct sockaddr *) &client, &len);

	if (n <= 0) {
		close(sock);
		return 1;
	}

	sentence[n] = '\0';

	printf("Received sentence: %s\nTranslating...\n", sentence);
	translate(sentence, result);

	sendto(sock, result, strlen(result), 0, (struct sockaddr *) &client, len);

	close(sock);
	return 0;
}