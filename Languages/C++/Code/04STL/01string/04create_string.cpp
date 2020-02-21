#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    // string();                  //创建一个空的字符串 例如: string str;
    // string(conststring & str); //使用一个string对象初始化另一个string对象
    // string(constchar * s);     //使用字符串s初始化
    // string(int n, char c);     //使用n个字符c初始化

    string s1;
    // ISO C++11 does not allow conversion from string literal to 'char *'
    // char *str = "hehe";
    const char *str = "hehe";
    string s2(str);
    string s3(s2);
    string s4(10, 'a');
    string s5 = "xixi";

    cout << "s4 = " << s4 << endl;
    cout << "s5 = " << s5 << endl;
    return 0;
}