#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <pthread.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;

enum Type
{
    HEART,
    OTHER
};

struct PACKET_HEAD
{
    Type type;
    int length;
    char buf[128];
};

class Server
{
private:
    struct sockaddr_in server_addr;
    socklen_t server_addr_len;
    int listen_fd;
    int max_fd;
    fd_set master_set;
    fd_set working_set;
    struct timeval timeout;
    map<int, pair<string, int>> mmap;

public:
    Server(int port);
    ~Server();
    void Bind();
    void Listen(int queue_len = 20);
    void Accept();
    void Run();
    void Recv(int nums);
    friend void *heart_handler(void *arg);
};