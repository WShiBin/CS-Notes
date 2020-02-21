#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    ifstream ifs;
    ifs.open("hello.txt");
    if (!ifs.is_open())
    {
        cout << "open file feild" << endl;
        exit(1);
    }

    char buf[1024] = {0};
    // 第一种读方式
    // while (ifs >> buf)
    // {
    //     cout << buf << endl;
    // }

    // 第二种读方式
    // while (ifs.getline(buf, sizeof(buf)))
    // {
    //     cout << buf << endl;
    // }

    // 第三种读方式
    string str_buf;
    while (getline(ifs, str_buf))
    {
        cout << str_buf << endl;
    }

    // ifs.read
    ifs.close();

    return 0;
}