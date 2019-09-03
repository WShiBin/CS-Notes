#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXLINE 80
#define SERV_PORT 8888
// #define SERV_PORT 6668

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr;
    char buf[MAXLINE];
    int sockfd, n;
    char *str;
    if (argc != 2)
    {
        fputs("usage: ./client message\n", stderr);
        exit(1);
    }
    str = argv[1];
    printf("str = %s\n", str);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // inet_pton(AF_INET, "127.0,0,1", &server_addr.sin_addr);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(SERV_PORT);
    // serveraddr.sin_addr =

    socklen_t server_addr_len = sizeof(server_addr);
    int conn_ret = connect(sockfd, (struct sockaddr *)&server_addr, server_addr_len);
    printf("conn_ret = %d\n", conn_ret);
    if (conn_ret == 0)
    {
        /* code */
        printf("connected ...\n");
    }
    else
    {
        printf("Oh dear, something went wrong with read()! %s\n", strerror(conn_ret));
        printf("connect faild\n");
        exit(1);
    }

    ssize_t write_len = write(sockfd, str, strlen(str));
    printf("write_len = %zd\n", write_len);

    n = read(sockfd, buf, MAXLINE);
    if  (n == 0)
    {
        printf("disconnected ...\n");
    }
    else if (n > 0)
    {
        printf("读到了content: %s\n", buf);
    }
    else
    {
        printf("err\n");
    }

    close(sockfd);

    return 0;
}
