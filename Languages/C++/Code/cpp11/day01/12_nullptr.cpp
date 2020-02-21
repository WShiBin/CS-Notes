#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

void func(int a)
{
	cout << __LINE__ << endl;
}

void func(int* p)
{
	cout << __LINE__ << endl;
}

int main(void)
{
	int * p = NULL;
	int *p2 = 0;

	func(nullptr);

	//nullptr, 只能给指针赋值
	p = NULL;
	p2 = nullptr;
	if (p == p2)
	{
		cout << "equal\n";
	}

	//不能给一个普通整型变量赋值给nullptr
	//无法从“nullptr”转换为“int”
	int tmp = nullptr; //err


	system("pause");
	return 0;
}
