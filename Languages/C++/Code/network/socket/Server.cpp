#include "Server.h"
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
#define BUFFER_SIZE 1024

void *heart_handler(void *arg);

Server::Server(int port)
{
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(port);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0)
    {
        cout << "Create Socket Failed!";
        exit(1);
    }
    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
}

Server::~Server()
{
    for (int fd = 0; fd <= max_fd; ++fd)
    {
        if (FD_ISSET(fd, &master_set))
        {
            close(fd);
        }
    }
}

void Server::Bind()
{
    if (-1 == (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))))
    {
        cout << "Server Bind Failed!";
        exit(1);
    }
    cout << "Bind Successfully.\n";
}

void Server::Listen(int queue_len)
{
    if (-1 == listen(listen_fd, queue_len))
    {
        cout << "Server Listen Failed!";
        exit(1);
    }
    cout << "Listen Successfully.\n";
}

void Server::Accept()
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int new_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (new_fd < 0)
    {
        cout << "Server Accept Failed!";
        exit(1);
    }

    string ip(inet_ntoa(client_addr.sin_addr));
    cout << ip << "new connection was accept.\n";
    mmap.insert(make_pair(new_fd, make_pair(ip, 0)));

    FD_SET(new_fd, &master_set);
    if (new_fd > max_fd)
    {
        max_fd = new_fd;
    }
}

void Server::Recv(int nums)
{
    PACKET_HEAD *head = new PACKET_HEAD;
    for (int fd = 0; fd <= max_fd; ++fd)
    {
        if (FD_ISSET(fd, &working_set))
        {
            bool close_conn = false;
            //PACKET_HEAD head;

            //head.buf = (char*)malloc(128);
            recv(fd, head, sizeof(PACKET_HEAD), 0);

            if (head->type == HEART)
            {
                mmap[fd].second = 0;
                cout << "Received heart-beat from client.\n";
                send(fd, head, sizeof(PACKET_HEAD), 0);
                //cout << sizeof(head) << "sizeof(head).\n";
            }
            else
            {
                mmap[fd].second = 0;
                //处理非心跳包数据
                cout << "Received " << head->buf << " from client.\n";
                send(fd, head, sizeof(PACKET_HEAD), 0);
                memset(head->buf, 0, sizeof(head->buf));
            }

            if (close_conn)
            {
                close(fd);
                FD_CLR(fd, &master_set);
                if (fd == max_fd)
                {
                    while (FD_ISSET(max_fd, &master_set) == false)
                        --max_fd;
                }
            }
        }
    }
    delete head;
}

void Server::Run()
{
    pthread_t id;
    int ret = pthread_create(&id, NULL, heart_handler, (void *)this);
    if (ret != 0)
    {
        cout << "Can not create heart-beat checking thread.\n";
    }

    max_fd = listen_fd;
    FD_ZERO(&master_set);
    FD_SET(listen_fd, &master_set);

    while (1)
    {
        FD_ZERO(&working_set);
        memcpy(&working_set, &master_set, sizeof(master_set));

        timeout.tv_sec = 30;
        timeout.tv_usec = 0;
        int nums = select(max_fd + 1, &working_set, NULL, NULL, &timeout);
        if (nums < 0)
        {
            cout << "select() error!";
            exit(1);
        }

        if (nums == 0)
        {
            cout << "select() is timeout!";
            continue;
        }

        if (FD_ISSET(listen_fd, &working_set))
            Accept();
        else
            Recv(nums);
    }
}

void *heart_handler(void *arg)
{
    cout << "The heartbeat checking thread started.\n";
    Server *s = (Server *)arg;
    while (1)
    {
        map<int, pair<string, int>>::iterator it = s->mmap.begin();
        for (; it != s->mmap.end();)
        {
            if (it->second.second == 5)
            {
                cout << "The client" << it->second.first << "has be offline.\n";
                int fd = it->first;
                close(fd);
                FD_CLR(fd, &s->master_set);
                if (fd == s->max_fd)
                {
                    while (FD_ISSET(s->max_fd, &s->master_set) == false)
                        s->max_fd--;
                }
                s->mmap.erase(it++);
            }
            else if (it->second.second < 5 && it->second.second >= 0)
            {
                it->second.second += 1;
                ++it;
            }
            else
            {
                ++it;
            }
        }
        sleep(3);
    }
}

int main()
{
    Server server(8000);
    server.Bind();
    server.Listen();

    server.Run();
    return 0;
}
