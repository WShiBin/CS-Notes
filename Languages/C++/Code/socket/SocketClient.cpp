#include "SocketClient.h"

SocketClient::SocketClient(const char *ip, int port)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr.s_addr) == -1)
    {
        perror("inet_pton err\n");
        exit(EXIT_FAILURE);
    }
    // server_addr.sin_addr.s_addr = htonl(ip);
    server_addr.sin_port = htons(port);

    server_addr_len = sizeof(server_addr);
}
void SocketClient::connAsync(function<void(int, SocketClientState, std::string)> callback)
{
    std::thread t([&]() { connSync(callback); });
    t.detach();
}
void SocketClient::connSync(function<void(int, SocketClientState, std::string)> callback)
{
    if (isRunning)
    {
        return;
    }
    isRunning = true;
    int ret = connect(sockfd, (struct sockaddr *)&server_addr, server_addr_len);
    if (ret != -1)
    {
        callback(sockfd, SocketClientState::CONNECTED, "connected");
    }
    else
    {
        callback(sockfd, SocketClientState::CONNECT_FAILED, "connected failed");
    }

    while (1)
    {
        read_len = read(sockfd, buf, BUF_SIZE);

        if (read_len > 0)
        {
            callback(sockfd, SocketClientState::RECEIVE_MSG, std::string{buf});
            bzero(buf, sizeof(buf));
        }
        else if (read_len == 0)
        {
            callback(sockfd, SocketClientState::DISCONNECTED, "discont");
        }
    }
}