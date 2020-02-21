#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
using namespace std;


int main(void)
{
	//static_assert(常量表达式条件, "提示的字符串")
	static_assert(sizeof(void *) == 4, "64位系统不支持");
	cout << "hello C++\n";

	system("pause");
	return 0;
}


int main01(void)
{
	bool flag = false;

	//运行时，检查条件，如果条件为真，往下执行，如果条件为假，中断，提示错误
	//assert(flag == true); //条件为假， 中断
	assert(flag == false);//条件为真，往下执行

	cout << "hello C++\n";


	system("pause");
	return 0;
}
