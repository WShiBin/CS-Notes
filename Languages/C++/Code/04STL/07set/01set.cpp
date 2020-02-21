#include <iostream>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
    // set<T> st;                     //set默认构造函数：
    // mulitset<T> mst;               //multiset默认构造函数:
    // set(const set &st);            //拷贝构造函数
    // set &operator=(const set &st); //重载等号操作符
    set<int> s;
    set<int> s2(s);
    set<int> s3 = s;

    // swap(st);                      //交换两个集合容器
    // size();                        //返回容器中元素的数目
    // empty();                       //判断容器是否为空
    s.swap(s2);
    cout << "size = " << s.size() << endl;
    cout << "is empty ? " << s.empty() << endl;

    // insert(elem);                  //在容器中插入元素。
    // clear();                       //清除所有元素
    // erase(pos);                    //删除pos迭代器所指的元素，返回下一个元素的迭代器。
    // erase(beg, end);               //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
    // erase(elem);                   //删除容器中值为elem的元素。
    s.insert(10);
    s.insert(10);
    s.insert(20);
    s.insert(30);
    for (auto &val : s)
        cout << val << " ";
    cout << endl;

    // find(key);                     //查找键key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
    // count(key);                    //查找键key的元素个数
    set<int>::iterator f = s.find(10);
    cout << "find " << *f << endl;
    cout << "count = " << s.count(10) << endl;

    // lower_bound(keyElem);          //返回第一个key>=keyElem元素的迭代器。
    // upper_bound(keyElem);          //返回第一个key>keyElem元素的迭代器。
    // equal_range(keyElem);          //返回容器中key与keyElem相等的上下限的两个迭代器。
    s.lower_bound(10);
    return 0;
}