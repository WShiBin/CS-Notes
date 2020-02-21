#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    ofstream ofs;
    // static const openmode app    = 0x01; 追加
    // static const openmode ate    = 0x02; 初始位置:文件尾部
    // static const openmode binary = 0x04; 二进制
    // static const openmode in     = 0x08; 读
    // static const openmode out    = 0x10; 写
    // static const openmode trunc  = 0x20; 清空
    // 多个之前用|   ios_base::app | ios_base::out
    ofs.open("hello.txt", ios_base::app);
    ofs << "hahah";
    ofs.close();
    return 0;
}