// #include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_EVENTS 10
#define PORT 8889

int main(int argc, char *argv[])
{

    struct epoll_event ev, events[MAX_EVENTS];
    int listen_sock, conn_sock, nfds, epollfd;
    struct sockaddr_in serv_addr, cli_addr;

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    /* Code to set up listening socket, 'listen_sock',
              (socket(), bind(), listen()) omitted */
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == -1)
    {
        perror("socket err\n");
        exit(EXIT_FAILURE);
    }

    if (bind(listen_sock, (struct sockaddr *)&serv_addr, (socklen_t)sizeof(serv_addr)) == -1)
    {
        perror("bind err\n");
        exit(EXIT_FAILURE);
    }

    if (listen(listen_sock, 1024) == -1)
    {
        perror("listen err\n");
        exit(EXIT_FAILURE);
    }

    epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1)
    {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        int n = 0;
        for (n = 0; n < nfds; ++n)
        {
            if (!(events[n].events & EPOLLIN))
                continue;
            if (events[n].data.fd == listen_sock)
            {
                // new connect
                socklen_t cli_addr_len = sizeof(cli_addr);
                conn_sock = accept(listen_sock, (struct sockaddr *)&cli_addr, &cli_addr_len);
                if (conn_sock == -1)
                {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                // setnonblocking(conn_sock);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_sock;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1)
                {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                // receive msg
                int conn_fd = events[n].data.fd;
                char buf[1024] = {0};
                int len = read(conn_fd, buf, sizeof(buf));
                if (len == 0)
                {
                    printf("disconnect \n");
                    //
                    if (epoll_ctl(epollfd, EPOLL_CTL_DEL, conn_fd, NULL) == -1)
                    {
                        perror("epoll del err\n");
                        exit(EXIT_FAILURE);
                    }
                    close(conn_fd);
                }
                else if (len > 0)
                {
                    printf("buf = %s\n", buf);
                }
                else
                {
                    printf("err\n");
                }

                // do_use_fd(events[n].data.fd);
            }
        }
    }
    close(listen_sock);
    close(epollfd);
    return 0;
}