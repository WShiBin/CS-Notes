#ifndef ALEXA_CLIENT_SDK_SAMPLEAPP_INCLUDE_SAMPLEAPP_SOCKETCLIENT_H_
#define ALEXA_CLIENT_SDK_SAMPLEAPP_INCLUDE_SAMPLEAPP_SOCKETCLIENT_H_

#include <arpa/inet.h>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#define BUF_SIZE 1024

using namespace std;

enum class SocketClientState
{
    CONNECTED,
    CONNECT_FAILED,
    DISCONNECTED,
    RECEIVE_MSG,
};

class SocketClient
{
public:
    SocketClient(const char *ip, int port);
    void connAsync(function<void(int, SocketClientState, std::string)> callback);
    void connSync(function<void(int, SocketClientState, std::string)> callback);
    ~SocketClient() = default;

private:
    bool isRunning = false;
    struct sockaddr_in server_addr;
    char buf[BUF_SIZE];
    int sockfd;
    int read_len;

    socklen_t server_addr_len = sizeof(server_addr);
};

#endif // ALEXA_CLIENT_SDK_SAMPLEAPP_INCLUDE_SAMPLEAPP_SOCKETCLIENT_H_