#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main(void)
{
	int a = 1024;
	char b = { a }; //错误	1	error C2397: 从“int”转换到“char”需要收缩转换	

	system("pause");
	return 0;
}
