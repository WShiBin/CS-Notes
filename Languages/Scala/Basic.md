## Overview

> Scala combines object-oriented and functional programming in one concise, high-level language. Scala's **static types** help avoid bugs in complex applications, and its JVM and JavaScript runtimes let you build high-performance systems with easy access to huge ecosystems of libraries.	

[https://www.scala-lang.org](https://www.scala-lang.org/)

Scala 是一门以 java 虚拟机（JVM）为运行环境并将**面向对象**和**函数式编程**的最佳特性结合在一起 的**静态类型**编程语言

## 安装Install(Mac)

```shell
> brew install java 	# java > 1.8
> brew install scala
> brew info scala
> echo $SCALA_HOME
/usr/local/Cellar/scala/2.12.8
> scala
Welcome to Scala 2.12.8 (Java HotSpot(TM) 64-Bit Server VM, Java 1.8.0_191).
Type in expressions for evaluation. Or try :help.

scala> val a = 100
a: Int = 100

scala>
```



## Idea配置

* install plugin:settings>plugin>search scala
* Add framework support:项目右键
* add scala folder under main, apple scala to sources
* 关联源码

> Homebrew没有下载源码,下载相同版本源码https://github.com/scala/scala/archive/v2.12.8.tar.gz,放到相应位置/usr/local/Cellar/scala/2.12.8/**src**



## HelloWord

```scala
object Hello {

  def main(args: Array[String]): Unit = {
    System.out.println("hello world")
    println("Hello World")
  }
}
```

反编译

```java
public final class Hello{
  public static void main(String[] paramArrayOfString){
    Hello..MODULE$.main(paramArrayOfString);
  }
}

public final class Hello${
  public static  MODULE$;
  
  static{
    new ();
  }
  
  public void main(String[] args){
    System.out.println("hello world");
    Predef..MODULE$.println("hehe");
    int a = 100;
    Predef..MODULE$.println(BoxesRunTime.boxToInteger(a));
  }
  
  private Hello$(){
    MODULE$ = this;
  }
}
```



## Scala代码 执行流程

![image-20190415182235978](Basic.assets/image-20190415182235978.png)

## 打印Print

```scala
object PrintDemo {

  def main(args: Array[String]): Unit = {
    //使用+ 
    var name: String = "tom"
    var sal: Double = 1.2
    println("hello" + sal + name)

    //使用格式化的方式 printf 
    printf("name=%s sal=%f\n", name, sal) 
    
    //使用$引用的方式，输出变量，类似 php 
    println(s"第三种方式 name=$name sal = ${sal + 1}")
  }
}
```

## 变量Variable

语法:var|val 变量名 [: 变量类型] = 变量值

```scala
var a : Int = 1
```

> var 修饰的变量可改变， val 修饰的 变量不可改(**加final**)
>
> 因为 val 没有线程安全问题，因此效率高，scala 的设计者推荐我们 val



## 数据类型

* Scala 与 Java 有着相同的数据类型，在 Scala 中数据类型都是对象
* Scala 数据类型分为两大类 AnyVal(值类型) 和 AnyRef(引用类型)

![image-20190415185111716](Basic.assets/image-20190415185111716.png)

1. 在 scala 中有一个根类型 Any ,他是所有类的父类.
2. scala 中一切皆为对象，分为两大类 AnyVal(值类型)， AnyRef(引用类型)， 他们都是 Any 子类.
3. Null 类型是 scala 的特别类型，它只有一个值 null, 他是 bottom calss ,是 所有 AnyRef 类型的子
4. Nothing 类型也是 bottom class ,他是所有类的子类，在开发中通常可以将 Nothing 类型的值返回 给任意变量或者函数， 这里抛出异常使用很多.



### Unit 类型、Null 类型和 Nothing 类型

Unit 相当于 void, Null 的值是 null, Nothing可以作为没有正常返回值的方法的返回类型,一般用于异常

```scala
class NothingDemo {
  def main(args: Array[String]): Unit = {
    println(sayHello)
  }
  
  def sayHello: Nothing = {
    throw new Exception("抛出异常")
  }
}
```

### 类型转换

```scala
object TypeConvertDemo {
  def main(args: Array[String]): Unit = {
    var str : String = "100"
    println(str.toInt)
    println(str.toDouble)
    println(str.toFloat)
    println(str.toLong)
  }
}
```



## scala 的关键字(39个)

> package, import, class, object, trait, extends, with, type, forSome 
>
> private, protected, abstract, sealed, final, implicit, lazy, override 
>
> try, catch, finally, throw 
>
> if, else, match, case, do, while, for, return, yield 
>
> def, val, var 
>
> this, super 
>
> new 
>
> true, false, null



## 运算符

1. 算术运算符
2. 赋值运算符
3. 比较运算符(关系运算符)
4. 逻辑运算符
5. 位运算符

### 算术运算符

+, - , * , / , %

> Scala 中没有++、--操作符，需要通过+=、-=来实现同样的效果

### 赋值运算符

=,+=,-=,*=,/=,%=先算术运算,后赋值

<<=.>>=先位移运算,后赋值

&=,|=,^=先逻辑运算,后赋值

### 关系运算符(比较运算符)

==,!=,>,>=,<,<=

### 逻辑运算符

&&,||,!

### 位运算符

&,|,^,~,<<,>>,>>>



## 流程控制

1. 顺序控制
2. 分支控制
3. 循环控制

### if,while,do…while(同Java)

### for 

```scala
object ForDemo {
  def main(args: Array[String]): Unit = {
    // 1,2,3,4...100
    for(c <- 1 to 100) {
      println(c)
    }
    
    // 1,4,7,10...100  (1+3x)
    for(c <- 1.to(100, 3)) {
      println(c)
    }
    
    // 同上
    for (i <- Range(1, 100, 3)) {
      println(i)
    }

    // 1 ~ 99
    for (c <- 1 until 100) {
      println(c)
    }

    // 99,98,97.96...1
    for (c <- 1 until 100 reverse) {
      println(c)
    }

    // 循环守卫
    for (c <- 1 until 100 if c % 3 == 0) {
      println(c)
    }

    // 循环返回值:Vector集合
    var arr = for (i <- 1 to 10) yield i * i
    println(arr)
  }
}
```

{}替换()

```scala
object ForDemo1 {
  def main(args: Array[String]): Unit = {
    for (i <- 1 to 3; j = i * 2) {
      println(" i= " + i + " j= " + j)
    }

    //可以写成
    for {i <- 1 to 3
         j = i * 2} {
      println(" i= " + i + " j= " + j)
    }
  }
}
```

#### 99乘法表-for 实现

``` scala
object ChengfabiaoDemo {
  def main(args: Array[String]): Unit = {
    for (row <- 1 to 9; col <- 1 to row) {
      print(s"$row * $col = ${row * col}\t")
      if (row == col) println()
    }
  }
  
  def foo(): Unit = {
    1 to 9 foreach (row => {
      1 to row foreach (col => printf(s"$row * $col = ${row * col}\t"))
      println()
    })
  }
}
```

### Break

> scala 中没有 break, 用 Breaks,本质上使用 try-catch,threw exception

````scala
import scala.util.control.Breaks

object BreakDemo {
  def main(args: Array[String]): Unit = {
    Breaks.tryBreakable(
      
      for (i <- 1.to(10)) {
        if (i == 5) {
          Breaks.break()
        }
      }
      
    )
    
  }
}
````

### Continue

> Scala 中没有 Continue, 用循环守卫实现



## 函数式编程

在 Scala 当中，函数是一等公民，像变量一样，既可以作为函数的参数使用，也可以将函数赋值给一个 变量.

### 函数式编程基础

#### 函数定义/声明

函数语法

```
def 函数名 ([参数名: 参数类型], ...)[[: 返回值类型] =] { 
	语句...
	return 返回值 
}
```

#### 参数的省略

#### 参数默认值

```scala
object FunDemo3 {

  def main(args: Array[String]): Unit = {
    println(preAndPost("ishibin"))
    println(preAndPost("ishibin", post = ".cn"))
  }

  def preAndPost(content: String, pre: String = "www.", post: String = ".com") = {
    pre + content + post
  }
}
```



#### 命名参数

#### 可变参数

```scala
class FunDemo3 {

  def main(args: Array[String]): Unit = {
    val arr: Range.Inclusive = 1.to(10)
    val sum= add(arr: _*)
    println(sum)
  }

  def add(a: Int*) = {
    var sum = 0
    for (elem <- a) {
      sum += elem
    }
    sum
  }
}
```



#### 递归//难点 [最短路径，邮差问题，迷宫问题, 回溯]

```scala
object FuntionDemo2 {

  def main(args: Array[String]): Unit = {
    println(fbn(10))
  }

  def fbn(n: Int): Int = {
    if (n == 1 || n == 2) {
      1
    } else {
      fbn(n - 1) + fbn(n - 2)
    }
  }
}
```



过程
惰性函数和异常



### 函数式编程高级

值函数(函数字面量)
高阶函数
闭包
应用函数
柯里化函数，
抽象控制...



Def,lazy,val 区别

````scala
object DefLazyValDemo {
  def main(args: Array[String]): Unit = {
    println(a)
    println(b)
    println(c)

    println("--------------")

    println(a)
    println(b)
    println(c)
  }

  def a = {
    println("aaa")
  }

  lazy val b = {
    println("bbb")
  }

  val c = {
    println("ccc")
  }
}
````



## 异常Try catch

```scala
object TryCatchDemo {

  def main(args: Array[String]): Unit = {
    try {
      new FileInputStream("")
    } catch {
      case e: FileNotFoundException => println(e)
      case e: NullPointerException => println(e)
      case _ => println("big exception")
    } finally {
      println("always print")
    }
  }
}
```



## 面向对象

## 语法

```scala
// var name 私有成员, 有 get/set
// val age 私有成员final, 有 get
// sex 如果class中不使用sex,则 sex 不会成为成员变量;有使用则为私有final成员
class User(var name: String, val age: Int, sex: String) {
  println("abc")

  def foo() = {
    println(name)
    println(sex) // 不使用 sex 则不会成为 field
  }
}
```

反编译 User.class

```shell
> javap -private User
```

```java
public class com.ishibin.User {
  private java.lang.String name;
  private final int age;
  private final java.lang.String sex;
  public java.lang.String name();
  public void name_$eq(java.lang.String);
  public int age();
  public void foo();
  public com.ishibin.User(java.lang.String, int, java.lang.String);
}
```

### @BeanProperty

为属性生成 get/set

```scala
class Person(@BeanProperty var name: String, @BeanProperty var age: Int) {
  @BeanProperty var gender: String = _
}
```

### 主构造/辅助构造

- 主构造器和 Java 有很大不同. 主构造器位于类名之后.
- 辅构造器和 Java 类似. 只是在 Scala 中辅构造器的名字统一用`this`来表示.
- 主构造器只能有一个, 辅构造器可以有多个.
- 在创建对象的时候, 和 Java 一样也是通过传入的参数来选择构造器.
- 调用主构造器的时候, 会执行类中的所有语句(当然不包括类中定义的方法.)

```scala
class Person() { // 主构造器如果没有参数可以省略圆括号
  var name: String = _
  var age: Int = _
  println("ok")

  // 辅构造器
  def this(name: String) {
    // 构造器第一行必须要能调用到主构造器
    this()
    this.name = name

  }

  // 辅构造器
  def this(name: String, age: Int) {
    this(name)
    this.age = age
  }

  def sayHello(): Unit = {
    println("hello: " + this.name)
  }
}
```

> 如果不想让外界通过主构造器创建对象, 可以把主构造器私有: 在类名和圆括号中间添加一个关键字`private`,辅构造器仍然可以调用私有的主构造器. 私有之后只是不能在外界调用而已.

### 构造器的形参

#### 1. 普通形参(未添加任何修饰的形参)

未添加任何修饰的构造函数的形参, 在能访问到的范围内就是一个普通的局部变量

- 主构造函数的形参在整个类的内部都是当做局部变量使用
- 辅构造函数的形参只在当前构造函数内有效

#### 2. 给形参添加`var`修饰

给形参添加`val`修饰, 那么这个时候的形参就是类的属性. 在类的内部可有直接`属性名`访问, 也可以`this.属性名`访问

在类的外部也可以访问.

#### 3. 给形参添加`val`修饰

给形参添加`val`修饰, 这个时候的形参就是一个只读的属性.

#### 4. 再添加`@BeanProperty`

再添加`@BeanProperty`, 就会给属性添加相应的`setter`和`getter`方法.(如果是`val`的则只有`getter`方法)



## 导包

```scala
package com.ishibin

// all
import java.util._
// 只导HashMap,TreeMap
import java.util.{HashMap, TreeMap}
// 给HashMap取别名
import java.util.{HashMap => HM, TreeMap}
// 屏蔽 HashMap
import java.util.{HashMap => _, TreeMap}
// 先取别名,然后全部导入
import java.util.{HashMap => HM, _}

object ImportDemo {

  def main(args: Array[String]): Unit = {
    // 临时导包
    import java.util.HashMap
    val map1 = new HashMap[String,String]()
 
    // 全类名, 不用导包
    val map2 = new java.util.HashMap[String, String]()
  }
}
```



## 隐式转换,隐式值,隐式类

### 隐式转换

> 隐式转换与函数名称无关，只与函数签名（函数参数类 型和返回值类型）有关

```scala
object Demo02 {
  def main(args: Array[String]): Unit = {
    implicit def  doubleToInt(d: Double):Int = {
      d.toInt
    }

    val num: Int = 3.5
    println("num =" + num)
  }
}
```

反编译字节码, 调用 douToInt 函数返回 int 值

```scala
package com.ishibin.implicitdemo;
import scala.Predef.;

public final class Demo02${
  public static  MODULE$;
  
  private static final int doubleToInt$1(double d){
    return (int)d;
  }
  
  public void main(String[] args){
    int num = doubleToInt$1(3.5D);
    Predef..MODULE$.println(5 + "num =" + num);
  }
  
  private Demo02$(){
    MODULE$ = this;
  }
  
  static{
    new ();
  }
}
```

拓展原有类功能

```scala
object Demo03 {
  def main(args: Array[String]): Unit = {
    implicit def hehe(mySQL: MySQL) = {
      new DB()
    }

    val mysql = new MySQL
    mysql.insert()
    mysql.delete() // 编译器工作 分析 addDelete$1(mySQL).delete()
    mysql.update()
  }
}

class MySQL {
  def insert(): Unit = {
    println("insert")
  }
}

class DB {

  def delete(): Unit = {
    println("delete")
  }

  def update(): Unit = {
    println("update")
  }
}
```

### 隐式值

> 隐式值也叫隐式变量，将某个形参变量标记为 implicit， 所以编译器会在方法省略隐式参数的情况 下去搜索作用域内的隐式值作为缺省参数

```scala
object Demo04 {
  def main(args: Array[String]): Unit = {
    implicit var str: String = "hello world"

    def fun(implicit str: String) = {
      println(str)  // hello world
    }

    fun
    //fun() //error
  }
}
```

Note:优先级 传值 > 隐式值 > 默认值

```scala
object Demo05 {
  //传值 > 隐式值 > 默认值
  def main(args: Array[String]): Unit = {
    implicit var str: String = "hello world"

    def fun(implicit str: String = "hello default") = {
      println(str) // hello world
    }

    fun("hello scala") //hello scala
    fun(str = "hello spark") //hello spark
    fun //hello world
    fun() //hello default
  }
}
```

### 隐式类