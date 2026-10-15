#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8002
#define MAXCLIENTS 100

int clients[MAXCLIENTS];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void broadcast(char *msg, int sender) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < MAXCLIENTS; i++)
        if (clients[i] >= 0 && clients[i] != sender)
            write(clients[i], msg, strlen(msg));
    pthread_mutex_unlock(&lock);
}

void *handle(void *arg) {
    int fd = *(int *)arg;
    free(arg);
    char msg[1024], out[1100];
    ssize_t n;

    while ((n = read(fd, msg, sizeof(msg) - 1)) > 0) {
        msg[n] = 0;
        snprintf(out, sizeof(out), "Client %d: %s", fd, msg);
        broadcast(out, fd);
    }

    close(fd);
    pthread_mutex_lock(&lock);
    for (int i = 0; i < MAXCLIENTS; i++)
        if (clients[i] == fd) clients[i] = -1;
    pthread_mutex_unlock(&lock);
    return NULL;
}

void server(void) {
    int lfd, cfd;
    struct sockaddr_in saddr, caddr;
    socklen_t clen = sizeof(caddr);
    signal(SIGPIPE, SIG_IGN);

    for (int i = 0; i < MAXCLIENTS; i++) clients[i] = -1;

    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd < 0) { perror("socket"); exit(1); }

    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(PORT);

    if (bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) { perror("bind"); exit(1); }
    if (listen(lfd, 8) < 0) { perror("listen"); exit(1); }
    printf("Chat server on port %d...\n", PORT);

    while (1) {
        cfd = accept(lfd, (struct sockaddr *)&caddr, &clen);
        if (cfd < 0) { perror("accept"); continue; }

        pthread_mutex_lock(&lock);
        int slot = 0;
        while (slot < MAXCLIENTS && clients[slot] >= 0) slot++;
        if (slot < MAXCLIENTS) clients[slot] = cfd;
        pthread_mutex_unlock(&lock);

        if (slot >= MAXCLIENTS) { close(cfd); continue; }

        int *fdp = malloc(sizeof(int));
        *fdp = cfd;
        pthread_t t;
        pthread_create(&t, NULL, handle, fdp);
    }
}

void *receive_messages(void *arg) {
    int fd = *(int *)arg;
    char buf[1100];
    ssize_t n;

    while ((n = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = 0;
        printf("%s", buf);
        fflush(stdout);
    }
    close(fd);
    return NULL;
}

void client(void) {
    int fd;
    struct sockaddr_in saddr;
    char line[1024];
    signal(SIGPIPE, SIG_IGN);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); exit(1); }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr);

    if (connect(fd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        perror("connect");
        exit(1);
    }
    printf("Connected. Type a message (Ctrl+D to quit):\n");

    int *fdp = malloc(sizeof(int));
    *fdp = fd;
    pthread_t t;
    pthread_create(&t, NULL, receive_messages, fdp);

    while (fgets(line, sizeof(line), stdin))
        write(fd, line, strlen(line));

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "client") == 0)
        client();
    else
        server();
    return 0;
}