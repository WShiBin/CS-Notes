#include <iostream>

using namespace std;

class AbstractCalculator
{
public:
    int num_a;
    int num_b;
    virtual int getResult()
    {
        return 0;
    }
};

class AddCalculator : public AbstractCalculator
{
public:
    int getResult()
    {
        return num_a + num_b;
    }
};

// 这里的多态用引用
// void getResult(AbstractCalculator &calculator)
void getResult(AbstractCalculator &calculator)
{
    int ret = calculator.getResult();
    cout << "ret = " << ret << endl;
}

int main(int argc, char *argv[])
{
    // 这里的多态用指针
    AbstractCalculator *calculator = new AddCalculator();
    calculator->num_a = 100;
    calculator->num_b = 100;
    int ret = calculator->getResult();
    cout << "ret = " << ret << endl;

    cout << " --------------- " << endl;
    getResult(*calculator);
    return 0;
}