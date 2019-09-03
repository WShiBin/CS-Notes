Cgo

静态库和动态库

* 直接使用源码
* 连接静态库
* 连接动态库



gcc编译命令

```
预处理：gcc -E hello.c -o hello.i
编  译：gcc -S hello.i -o hello.s
汇  编：gcc -c hello.s -o hello.o
链  接：gcc    hello.o -o hello_elf
```





```
 go build -buildmode=c-archive -o dest.a filename.go   
 go build -buildmode=c-shared -o number.so   
```





![]()