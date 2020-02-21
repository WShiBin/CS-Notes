

- 条件编译Conditional inclusion
- 文本替换Replacing text macros
- 包含头文件Source file inclusion



## 条件编译Conditional inclusion

**Syntax**

```c++
#if expression
#ifdef identifier
#ifndef identifier
#elif expression
#else
#endif
```

**Example**

```c++
#define ABCD 2
#include <stdio.h>
 
int main(void)
{
 
#ifdef ABCD
    printf("1: yes\n");
#else
    printf("1: no\n");
#endif
 
#ifndef ABCD
    printf("2: no1\n");
#elif ABCD == 2
    printf("2: yes\n");
#else
    printf("2: no2\n");
#endif
 
#if !defined(DCBA) && (ABCD < 2*4-3)
    printf("3: yes\n");
#endif
}
```



## 文本替换Replacing text macros

**Syntax**

```c++
#define identifier replacement-list(optional)
#define identifier( parameters ) replacement-list(optional)
#define identifier( parameters, ... ) replacement-list(optional)    (since C++11)
#define identifier( ... ) replacement-list(optional)    (since C++11)
#undef identifier
```

**'# and ## operators'**

- '#'会将变量加双引号

```c++
#define showlist(...) puts(#__VA_ARGS__)
showlist();            // expands to puts("")
showlist(1, "x", int); // expands to puts("1, \"x\", int")
```

- '##'后面的内容会用变量值替换掉

```c++
#include <iostream>

// Make function factory and use it
#define FUNCTION(name, a) \
    int fun_##name() { return a; }

// 定义三个函数
FUNCTION(abcd, 12)
FUNCTION(fff, 2)
FUNCTION(qqq, 23)

#undef FUNCTION
#define FUNCTION 34
#define OUTPUT(a) std::cout << "output: " #a << '\n'

// Using a macro in the definition of a later macro
#define WORD "Hello "
#define OUTER(...) WORD #__VA_ARGS__

int main()
{
  	// 调用用宏文本替换定义的几个方法
    std::cout << "abcd: " << fun_abcd() << '\n';
    std::cout << "fff: " << fun_fff() << '\n';
    std::cout << "qqq: " << fun_qqq() << '\n';

  	// Note:没有加引号
    std::cout << FUNCTION << '\n';
    OUTPUT(million); //note the lack of quotes
    OUTPUT(second);  //note the lack of quotes
    OUTPUT(10);      //note the lack of quotes

  	// WORD是字符串的WORD,不是宏的WORD
    std::cout << OUTER(World) << '\n';
    std::cout << OUTER(WORD World) << '\n';
}
```



## 源文件包含Source file inclusion

**Syntax**

```c++
#include <filename>	(1)	
#include "filename"	(2)	
__has_include ( " filename " )	(3)	(since C++17)
__has_include ( < filename > )	(3)	(since C++17)
```

**Note**

```
#ifndef FOO_H_INCLUDED /* any name uniquely mapped to file name */
#define FOO_H_INCLUDED
// contents of the file are here
#endif
```

**Example**

```c++
#if __has_include(<optional>)
#  include <optional>
#  define have_optional 1
#elif __has_include(<experimental/optional>)
#  include <experimental/optional>
#  define have_optional 1
#  define experimental_optional 1
#else
#  define have_optional 0
#endif
 
#include <iostream>
 
int main()
{
    if (have_optional)
        std::cout << "<optional> is present.\n";
 
    int x = 42;
#if have_optional == 1
    std::optional<int> i = x;
#else
    int* i = &x;
#endif
    std::cout << "i = " << *i << '\n';
}
```

