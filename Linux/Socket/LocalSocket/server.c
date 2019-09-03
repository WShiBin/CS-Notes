#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // socket
    struct sockaddr_un ser_addr, cli_addr;
    int cfd, sfd;

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    // bind
    bzero(&ser_addr, sizeof(ser_addr));
    ser_addr.sun_family = AF_UNIX;
    strcpy(ser_addr.sun_path, "ser.socket");

    // int opt = 1;
    // if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    // {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }

    unlink("ser.socket");
    bind(sfd, (struct sockaddr *)&ser_addr, (socklen_t)sizeof(ser_addr));

    // listen
    listen(sfd, 1024);
    // accept
    while (1)
    {
        socklen_t cli_addr_len;
        int cfd = accept(sfd, (struct sockaddr *)&cli_addr, &cli_addr_len);
        char buf[1024] = {0};
        int len = 0;
        while ((len = read(cfd, buf, sizeof(buf))) > 0)
        {

            // int len = read(cfd, buf, sizeof(buf));
            if (len == 0)
            {
                printf("disconnect \n");
            }
            else if (len > 0)
            {
                printf("buf = %s\n", buf);
                write(cfd, "hehe\n", sizeof("hehe\n"));
            }
            else
            {
                perror("read err");
            }
            bzero(buf, sizeof(buf));
        }
    }
    // close
    return 0;
}