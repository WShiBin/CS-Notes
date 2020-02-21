#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// void fun

int main(int argc, char *argv[])
{
    unique_ptr<int> p(new int(100));
    // p.reset();
    // p.release();
    cout << *p << endl;

    unique_ptr<vector<int>> p2(new vector<int>());
    p2->push_back(1000);

    cout << "size = " << p2->size() << endl;
    // delete(p2) p2;

    std::unique_ptr<int> p1(new int(5));
    // std::unique_ptr<int> p2 = p1;            // 编译会出错
    std::unique_ptr<int> p3 = std::move(p1); // 转移所有权，现在那块内存归p3所有, p1成为无效的指针。

    p3.reset(); //释放内存。
    p1.reset(); //实际上什么都没做。
    return 0;
}