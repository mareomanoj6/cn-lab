#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>

#define PORT 8004

void read_line(int fd, char *buf, int max) {
    int i = 0;
    char c;
    while (i < max - 1 && read(fd, &c, 1) == 1) {
        if (c == '\n') break;
        buf[i++] = c;
    }
    buf[i] = 0;
}

void server(void) {
    int lfd, cfd;
    struct sockaddr_in saddr, caddr;
    socklen_t clen = sizeof(caddr);
    signal(SIGPIPE, SIG_IGN);

    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd < 0) { perror("socket"); exit(1); }

    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(PORT);

    if (bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) { perror("bind"); exit(1); }
    if (listen(lfd, 5) < 0) { perror("listen"); exit(1); }
    printf("File server on port %d...\n", PORT);

    while (1) {
        cfd = accept(lfd, (struct sockaddr *)&caddr, &clen);
        if (cfd < 0) { perror("accept"); continue; }

        if (fork() == 0) {
            close(lfd);
            char fname[256], buf[1024];
            int n = read(cfd, fname, sizeof(fname) - 1);
            fname[n] = 0;

            char head[256];
            snprintf(head, sizeof(head), "PID: %d\n", (int)getpid());
            write(cfd, head, strlen(head));

            FILE *fp = fopen(fname, "r");
            if (fp == NULL) {
                write(cfd, "ERROR: file not found\n", 23);
            } else {
                write(cfd, "FOUND\n", 6);
                while (fgets(buf, sizeof(buf), fp))
                    write(cfd, buf, strlen(buf));
                fclose(fp);
            }
            printf("Served '%s' by child PID %d\n", fname, (int)getpid());
            close(cfd);
            exit(0);
        }
        close(cfd);
    }
}

void client(void) {
    int fd;
    struct sockaddr_in saddr;
    char fname[256], line[1024];

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

    printf("Enter filename: ");
    fgets(fname, sizeof(fname), stdin);
    fname[strcspn(fname, "\n")] = 0;

    write(fd, fname, strlen(fname));

    read_line(fd, line, sizeof(line));
    printf("%s\n", line);

    read_line(fd, line, sizeof(line));
    if (strcmp(line, "FOUND") == 0) {
        char buf[1024];
        int k;
        while ((k = read(fd, buf, sizeof(buf))) > 0)
            fwrite(buf, 1, k, stdout);
    } else {
        printf("%s\n", line);
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "client") == 0)
        client();
    else
        server();
    return 0;
}