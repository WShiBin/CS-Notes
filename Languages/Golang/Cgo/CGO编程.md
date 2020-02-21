## Cgo

* 支持Go语言调用,C语言函数调用, 去继承,使用c几十年的资产 
* 用Go 语言导出C静态库/动态库接口给其它语言使用 



### 最简**CGO**程序 

```go
package main

import "C"

func main() {
	println("hello cgo")
}
```

go build 命令会在编译和链接阶段启动gcc编译器 



### 基于**C**标准库函数输出字符串 

```go
package main

//引入stdio.h头文件

//#include <stdio.h>
import "C"

func main() {
	// C.CString 将go的string转化成C的string
	// C.CString 没有释放
	C.puts(C.CString("Hello, World\n"))
}
```





### 使用自己的**C**函数 

```go
package main

// 自定义C函数

// #include <stdio.h>
// static void SayHello(const char* s) {
//     puts(s);
// }
import "C"

func main() {
	// 调用上面自定义的C函数
	C.SayHello(C.CString("Hello, World\n"))
}
```

