#include "SocketClient.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    std::shared_ptr<SocketClient> socketClient(new SocketClient("192.168.1.105", 9687));
    socketClient->connSync([&](int conn_fd, SocketClientState state, std::string msg) {
        // todo
        if (state == SocketClientState::CONNECTED)
        {
            cout << "connected " << endl;
            std::string msg{"hello"};
            int ret = write(conn_fd, msg.c_str(), msg.length());
            ret = write(conn_fd, msg.c_str(), msg.length());
            cout << "ret " << ret << endl;
        }
        else if (state == SocketClientState::CONNECT_FAILED)
        {
            cout << "connected failed" << endl;
        }
        else if (state == SocketClientState::DISCONNECTED)
        {
            cout << "disconnected " << endl;
        }
        else if (state == SocketClientState::RECEIVE_MSG)
        {
            cout << "receive msg " << endl;
            cout << "msg = " << msg << endl;
        }
    });

    return 0;
}