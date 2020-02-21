#include <iostream>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    // map<T1, T2> mapTT;             //map默认构造函数:
    // map(const map &mp);            //拷贝构造函数
    // map &operator=(const map &mp); //重载等号操作符
    // map.insert(...);               //往容器插入元素，返回pair<iterator,bool>
    map<int, string> mapStu;
    mapStu.insert(pair<int, string>(3, "小张"));
    mapStu.insert(make_pair(-1, "校长"));
    mapStu.insert(map<int, string>::value_type(1, "小李"));
    mapStu[3] = "小刘";
    mapStu[5] = "小王";

    for (auto &val : mapStu)
    {
        cout << val.first << " " << val.second << endl;
    }

    // swap(mp);                      //交换两个集合容器
    // size();                        //返回容器中元素的数目
    // empty();                       //判断容器是否为空
    cout << "size = " << mapStu.size() << endl;
    cout << "is empty ? " << mapStu.empty() << endl;

    // clear();                       //删除所有元素
    // erase(pos);                    //删除pos迭代器所指的元素，返回下一个元素的迭代器。
    // erase(beg, end);               //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
    // erase(keyElem);                //删除容器中key为keyElem的对组。
    // find(key);                     //查找键key是否存在,若存在，返回该键的元素的迭代器；/若不存在，返回map.end();
    // count(keyElem);                //返回容器中key为keyElem的对组个数。对map来说，要么是0，要么是1。对multimap来说，值可能大于1。
    mapStu.erase(mapStu.begin());
    mapStu.erase(mapStu.begin(), --mapStu.end());
    mapStu.erase(-1);
    // mapStu.clear();
    cout << (*mapStu.find(5)).second << endl;

    // lower_bound(keyElem);          //返回第一个key>=keyElem元素的迭代器。
    // upper_bound(keyElem);          //返回第一个key>keyElem元素的迭代器。
    // equal_range(keyElem);          //返回容器中key与keyElem相等的上下限的两个迭代器。

    return 0;
}