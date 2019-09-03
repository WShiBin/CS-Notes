#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define CLI_PATH "cli.socket"
#define SER_PATH "ser.socket"

int main(int argc, char *argv[])
{
    struct sockaddr_un seraddr, cliaddr;
    int cfd;
    int len;
    char buf[1024];
    cfd = socket(AF_UNIX, SOCK_STREAM, 0);

    // cli addr
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sun_family = AF_UNIX;
    strcpy(cliaddr.sun_path, CLI_PATH);

    // sun_path在结构体sockaddr_un中的偏移
    len = offsetof(struct sockaddr_un, sun_path) + strlen(cliaddr.sun_path);

    unlink(cliaddr.sun_path);
    bind(cfd, (struct sockaddr *)&cliaddr, len);

    // ser addr
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sun_family = AF_UNIX;
    strcpy(seraddr.sun_path, SER_PATH);

    len = offsetof(struct sockaddr_un, sun_path) + strlen(seraddr.sun_path);
    int ret = connect(cfd, (struct sockaddr *)&seraddr, (socklen_t)len);

    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        write(cfd, buf, sizeof(buf));
        // len = 0 disconnect
        // len > 0 有content
        // len < 0 error
        len = read(cfd, buf, sizeof(buf));

        buf[len] = 0;
        write(STDOUT_FILENO, buf, sizeof(len + 1));
        bzero(buf, sizeof(buf));
    }
    close(cfd);

    return 0;
}