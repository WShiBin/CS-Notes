#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class A
{
public:
	A(int i) : a(i) //参数列表初始化
	{
		//a =  i;
	}

	int a;
};

class B
{
public:
	int data{ 1 };
	int data2 = 1;
	A tmp{ 10 };

	string name{ "mike" };
};

int main(void)
{
	B obj;
	cout << obj.data << endl;
	cout << obj.data2 << endl;
	cout << obj.tmp.a << endl;
	cout << obj.name << endl;

	system("pause");
	return 0;
}
