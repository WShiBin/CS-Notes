#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8889

int main(int argc, char *argv[])

{
    struct sockaddr_in cli_addr;
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)
    {
        perror("socket err\n");
        exit(EXIT_FAILURE);
    }

    bzero(&cli_addr, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // inet_pton(AF_INET, "127.0.0.1", &cli_addr.sin_addr.s_addr);
    cli_addr.sin_port = htons(PORT);

    if (connect(sock_fd, (struct sockaddr *)&cli_addr, (socklen_t)sizeof(cli_addr)) == -1)
    {
        perror("connect err\n");
        exit(EXIT_FAILURE);
    }

    char buf[1024] = "hello from client";

    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        write(sock_fd, buf, strlen(buf));
    }

    close(sock_fd);

    return 0;
}