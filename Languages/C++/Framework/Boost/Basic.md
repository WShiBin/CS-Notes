Boost

准标准库

https://www.boost.org/

https://www.boost.org/doc/libs/1_71_0/more/getting_started/unix-variants.html#link-your-program-to-a-boost-library

# 01.总论

项目目录

* boost: 90%的源代码	
  * align: 内存对齐
  * archive:
  * asio: 异步并发
  * assign: 赋值初始化
  * atomic: 原子操作库
  * bimap
  * bind
  * chrono: 时间处理
  * ...
  * xpression
* doc: 文档
* libs: 所有组件的测试/示例/编译代码和说明文档
* more: 库作者相关文档
* status: 可用于测试boost库各个组件
* tools: b2,quickbook等自带工具



### 使用方式

声明和实现在一起, .hpp文件

* 直接include使用
* 必须编译成静态库和动态库才能使用:chrono, data_time, program_options, test, thread等

### Install 安装

```shell
./bootstrap.sh  		# config
sudo ./b2 install		# install
sudo ./b2 --buildtype=comlete install		# install 完整编译,安装所有调试版,发行版的静态库和动态库
./b2 --help 				# help
```

默认编译Release版本

头文件:/usr/local/include

库文件:/usr/local/lib

### 验证是否安装成功

```cpp
#include <boost/config.hpp>
#include <boost/version.hpp>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << BOOST_VERSION << endl;
    cout << BOOST_LIB_VERSION << endl;
    cout << BOOST_PLATFORM << endl;
    cout << BOOST_COMPILER << endl;
    cout << BOOST_STDLIB << endl;
    return 0;
}
```

## 1.2.构建工具

用的自己的构建工具b2(boost build v2)

构建脚本

* jamfile/Jamfile
* jamroot: 放在根目录下,用于管理项目树,定义整个项目的构建配置



# 02.时间和日期

> timer,date_time和chrono

### 2.1.timer

两个版本:timer(v1:c/c++标准库函数)和cpu_timer(v2:chrono库,使用操作系统API,精度更高)

这里讲timer

三个小组件:tiemr,progress_timer,progress_display