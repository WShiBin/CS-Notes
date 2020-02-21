#include <iostream>
#include <map>

using namespace std;
class MyCompare
{
public:
    // 方法后面加const, error: the specified comparator type does not provide a const call operator
    bool operator()(const int &a, const int &b) const
    {
        return a > b;
    }
};
// map 默认按key, 从小到大排序
int main(int argc, char *argv[])
{
    map<int, string, MyCompare> mapStu;
    mapStu.insert(pair<int, string>(3, "小张"));
    mapStu.insert(make_pair(-1, "校长"));
    mapStu.insert(map<int, string>::value_type(1, "小李"));
    mapStu[3] = "小刘";
    mapStu[5] = "小王";

    // for (auto &val : mapStu)
    // {
    //     cout << val.first << " " << val.second << endl;
    // }

    for (map<int, string, MyCompare>::iterator it = mapStu.begin(); it != mapStu.end(); ++it)
    {
        cout << (*it).first << " - " << (*it).second << endl;
    }
    return 0;
}