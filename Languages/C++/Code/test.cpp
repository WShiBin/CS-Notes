#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    // vector<string, __gun_cxx::__pool_alloc<string>> v;
    int num = std::atoi("44444");

    if (num == 0) {
        cout << "333333333333" << endl;
    } else {
        cout << "444444444444" << endl;
    }
    std::string str("hehe");
    cout << "len = " << strlen(str.c_str()) << endl;
    cout << "len = " << str.length() << endl;
    return 0;
}