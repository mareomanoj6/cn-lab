#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_N 50

void server(void) {
    int lfd, cfd;
    struct sockaddr_in saddr, caddr;
    socklen_t clen = sizeof(caddr);
    int N, m[MAX_N * MAX_N];

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
    printf("Server waiting on port %d...\n", PORT);

    while (1) {
        cfd = accept(lfd, (struct sockaddr *)&caddr, &clen);
        if (cfd < 0) { perror("accept"); continue; }
        printf("Client connected.\n");

        read(cfd, &N, sizeof(int));
        if (N < 1 || N > MAX_N) {
            const char *e = "Invalid order";
            write(cfd, e, strlen(e) + 1);
            close(cfd);
            continue;
        }
        read(cfd, m, sizeof(int) * N * N);

        int upper = 1, lower = 1;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (m[i * N + j] != 0) {
                    if (i > j) upper = 0;
                    if (i < j) lower = 0;
                }

        char type[50];
        if (upper && lower)      strcpy(type, "Diagonal");
        else if (upper)          strcpy(type, "Upper Triangular");
        else if (lower)          strcpy(type, "Lower Triangular");
        else                     strcpy(type, "Not triangular or diagonal");

        printf("Matrix is %s\n", type);
        write(cfd, type, strlen(type) + 1);
        close(cfd);
    }
}

void client(void) {
    int cfd, N, m[MAX_N * MAX_N];
    struct sockaddr_in saddr;
    char type[50];

    srand(time(NULL));

    printf("Enter order N: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            m[i * N + j] = rand() % 50 + 1;

    printf("Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%4d", m[i * N + j]);
        printf("\n");
    }

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd < 0) { perror("socket"); exit(1); }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr);

    if (connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        perror("connect");
        exit(1);
    }

    write(cfd, &N, sizeof(int));
    write(cfd, m, sizeof(int) * N * N);

    read(cfd, type, sizeof(type));
    printf("\nMatrix type: %s\n", type);
    close(cfd);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "client") == 0)
        client();
    else
        server();
    return 0;
}