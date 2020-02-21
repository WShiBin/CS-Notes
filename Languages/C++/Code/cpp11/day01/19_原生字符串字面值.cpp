#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	cout << R"(hello, \n world)" << endl;
	string str = R"(helo \4 \r 
	abc, mike
	hello\n)";
	cout << endl;
	cout << str << endl;

	system("pause");
	return 0;
}
