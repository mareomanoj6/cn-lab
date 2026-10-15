#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#define PORT 8003

void server(void) {
    int sfd;
    struct sockaddr_in saddr, caddr;
    char req[32];

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd < 0) { perror("socket"); exit(1); }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(PORT);

    if (bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) { perror("bind"); exit(1); }
    printf("Time server on UDP port %d...\n", PORT);

    while (1) {
        socklen_t clen = sizeof(caddr);
        recvfrom(sfd, req, sizeof(req), 0, (struct sockaddr *)&caddr, &clen);

        if (fork() == 0) {
            time_t now = time(NULL);
            char *s = ctime(&now);
            s[strcspn(s, "\n")] = 0;
            sendto(sfd, s, strlen(s) + 1, 0,
                   (struct sockaddr *)&caddr, sizeof(caddr));
            exit(0);
        }
    }
}

void client(void) {
    int sfd;
    struct sockaddr_in saddr;
    char resp[128];

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd < 0) { perror("socket"); exit(1); }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr);

    sendto(sfd, "TIME", 4, 0, (struct sockaddr *)&saddr, sizeof(saddr));

    socklen_t slen = sizeof(saddr);
    int n = recvfrom(sfd, resp, sizeof(resp) - 1, 0,
                     (struct sockaddr *)&saddr, &slen);
    resp[n] = 0;
    printf("Server time: %s\n", resp);
    close(sfd);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "client") == 0)
        client();
    else
        server();
    return 0;
}