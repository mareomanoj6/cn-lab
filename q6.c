#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8001
#define BUFSZ 1024

char *abbr[] = { "tbh", "ig", "tbf", "atm", "irl",
                 "lol", "asap", "omg", "ttyl", "idk", "nvm" };
char *formal[] = { "to be honest", "I guess", "to be fair", "at the moment",
                   "in real life", "laugh out loud", "as soon as possible",
                   "oh my God", "talk to you later", "I don't know", "never mind" };
#define NABBR 11

void translate(char *in, char *out) {
    char *tok = strtok(in, " \t\n");
    out[0] = 0;

    while (tok != NULL) {
        int l = strlen(tok);
        while (l > 0 && !isalpha((unsigned char)tok[l - 1])) tok[--l] = 0;
        int s = 0;
        while (tok[s] && !isalpha((unsigned char)tok[s])) s++;

        char w[128];
        strcpy(w, tok + s);
        for (int i = 0; w[i]; i++) w[i] = tolower((unsigned char)w[i]);

        char *repl = w;
        for (int i = 0; i < NABBR; i++)
            if (strcmp(w, abbr[i]) == 0) repl = formal[i];

        strcat(out, repl);
        strcat(out, " ");
        tok = strtok(NULL, " \t\n");
    }

    int l = strlen(out);
    if (l > 0) out[l - 1] = 0;
}

void server(void) {
    int sfd;
    struct sockaddr_in saddr, caddr;
    char sentence[BUFSZ], resp[BUFSZ];

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd < 0) { perror("socket"); exit(1); }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(PORT);

    if (bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) { perror("bind"); exit(1); }
    printf("Server waiting on UDP port %d...\n", PORT);

    while (1) {
        socklen_t clen = sizeof(caddr);
        int n = recvfrom(sfd, sentence, sizeof(sentence) - 1, 0,
                         (struct sockaddr *)&caddr, &clen);
        sentence[n] = 0;
        printf("Received : %s\n", sentence);

        translate(sentence, resp);
        printf("Replied  : %s\n", resp);

        sendto(sfd, resp, strlen(resp) + 1, 0,
               (struct sockaddr *)&caddr, sizeof(caddr));
    }
}

void client(void) {
    int sfd;
    struct sockaddr_in saddr;
    char sentence[BUFSZ], resp[BUFSZ];

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd < 0) { perror("socket"); exit(1); }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr);

    printf("Enter sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = 0;

    sendto(sfd, sentence, strlen(sentence), 0,
           (struct sockaddr *)&saddr, sizeof(saddr));

    socklen_t slen = sizeof(saddr);
    int n = recvfrom(sfd, resp, sizeof(resp) - 1, 0,
                     (struct sockaddr *)&saddr, &slen);
    resp[n] = 0;
    printf("Translation: %s\n", resp);
    close(sfd);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "client") == 0)
        client();
    else
        server();
    return 0;
}