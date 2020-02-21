#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int func(int a, int b)
{
	return a + b;
}

auto func2(int a, int b) -> int
{
	return a + b;
}

auto func3(int a, double b) -> decltype(a+b)
{
	return a + b;
}

template<class T1, class T2>
auto mul(const T1 &t1, const T2 &t2) -> decltype(t1*t2)
{
	return t1*t2;
}

int main(void)
{
	int a = 10;
	double b = 11.1;
	auto c = func3(10, 11.1);
	cout << "c = " << c << endl;

	auto i = 10;
	auto j = 11.2;
	auto k = mul(i, j);
	cout << "k  = " << k << endl;


	system("pause");
	return 0;
}
