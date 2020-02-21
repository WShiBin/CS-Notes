#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <typeinfo> //typeid
#include <vector>
using namespace std;

int main(void)
{
	int i;
	decltype(i) j = 0;
	cout << typeid(j).name() << endl;

	float a;
	double b;
	decltype(a + b) c;
	cout << typeid(c).name() << endl;

	vector<int> tmp;
	decltype(tmp.begin()) k;
	for (k = tmp.begin(); k != tmp.end(); ++k)
	{
		//……
	}

	enum {Ok, Error}flag; //匿名类型的枚举变量
	decltype(flag) flag2;


	system("pause");
	return 0;
}
