#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // string substr(int pos = 0, int n = npos) const;  //返回由pos开始的n个字符组成的字符串
    string str("ishibin@gmail.com");
    int pos = str.find("@");

    string userName = str.substr(0, pos);
    cout << "userName = " << userName << endl;

    return 0;
}