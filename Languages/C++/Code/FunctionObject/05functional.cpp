#include <functional>
#include <iostream>

using namespace std;
void print_num(int i) {
    std::cout << i << '\n';
}

int main(int argc, char* argv[]) {
    std::plus<int> p;
    int ret = p(10, 20);
    cout << "ret = " << ret << endl;

    std::minus<int> m;
    ret = m(20, 10);
    cout << "ret = " << ret << endl;

    std::multiplies<int> mu;
    int ret = mu(10, 20);
    cout << "ret = " << ret << endl;

    std::divides<int> d;
    ret = d(20, 10);
    cout << "ret = " << ret << endl;

    std::invoke(print_num(), -9);

    return 0;
}