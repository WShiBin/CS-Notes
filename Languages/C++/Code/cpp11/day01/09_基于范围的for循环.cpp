#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

void func(int a[]) //形参中的数组不是数组，是指针变量，无法确定元素个数
{
	//基于范围的for, 这个范围要确定后，才能使用
	for (int & tmp: a) //err
	{
		cout << tmp << endl;
	}
}

int main(void)
{
	int a[] = { 1, 2, 3, 4, 5 };
	int n = sizeof(a) / sizeof(*a); //元素个数

	for (int i = 0; i < n; ++i)
	{
		int tmp = a[i];
		cout << tmp << ", ";
	}
	cout << endl;

	for (int tmp : a)
	{
		cout << tmp << ", ";
	}
	cout << endl;


	for (int i = 0; i < n; ++i)
	{
		int &tmp = a[i];
		tmp = 2 * tmp;
		cout << tmp << ", ";
	}
	cout << endl;

	for (int &tmp : a)
	{
		tmp = 2 * tmp;
		cout << tmp << ", ";
	}
	cout << endl;

	func(a); //调用函数



	system("pause");
	return 0;
}
