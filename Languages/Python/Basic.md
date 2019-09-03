

## Condition and Loop

```python
score = 80
if score > 90:
    print('A')
elif score > 70:
    print('B')
elif score >= 60:
    print('C')
else:
    print('D')

total = 0
i = 1
while i <= 100:
    total += i
    i += 1  # 没有++i或者--i
print(total)

'''
for循环只作用于容器！！！
没有这种写法：
  for (i = 0; i < 100; ++i):
      # TODO
上面这种循环只能用while实现
'''

i = 0
while i < 3:
    j = 0
    while j <= 3:
        if j == 2:
            j += 1
            continue  # 又去了while j <= 3
        print(i, j)
        j += 1
    i += 1
```



## Function

```python
# default args
def hello(who='world'):
    print('hello %s!' % (who))


hello()
hello('sea')


# f(x) = x * 5 + 100
# g(x) = x * 5; f(x) = x + 100
# => f(g(x)) = x * 5 + 100
def g(x):
    return x * 5


def f(gf, x):
    return gf(x) + 100


print(f(g, 100))
# lambda x: x * 5 等同于 g函数
print(f(lambda x: x * 5, 100))


def f(gf, x, y):
    return gf(x, y) + 100


print(f(lambda x, y: x * y, 100, 200))


def a(x):
    return x*5

def b(f, x):
    return f(x) + 100
#
# if __name__ == '__main__':
#     print("---------------------")
#     print(b(a, 100))
print(b(lambda x: x * 5, 100000))

```



## Type

### list

```python
# list就是数组


li = [1, 2, 3, 4, 5]
# 遍历
for i in li:
    # print(i)
    pass
# 用range模拟for (i = 0; i < x; ++i)
# range(x) => [0, x - 1]
# range(x, y) => [x, y - 1]
# range(x, y, z) => [x, x + z,..., < y]
for i in range(len(li)):
    # print(li[i])
    pass

for i in range(1, 10, 2):
    print(i)

print('----------------')
# 负数索引
print(li[-1])
print(li[-2])
print('----------------')

# 负数step的range => [x, x - z, ..., > z]
for i in range(3, -1, -1):
    print(i)

print('----------------')

# 添加元素
li = []
li.append(1)
li.append(2)
li.append('abc')
li.append(['d', 'e', 'f'])
print(li)

# 按元素添加数组
li = [1, 2]
li_2 = [3, 4, 5]
# 我们想要[1, 2, 3, 4, 5]
# li.append(li_2) => [1, 2, [3, 4, 5]]
li.extend(li_2)
print(li)

# 删除元素
li.pop()    # => [1, 2, 3, 4]
print(li)
li.pop(2)   # => [1, 2, 4]
print(li)

li = [5, 8, 7, 4, 2, 3]
li.sort()
print(li)
# lambda帮助排序
li = [[5, 2], [3, 8], [2, 11], [7, 6]]
# li.sort(key = lambda x: x[0]) # 参数名字
# 与lamda等价写法



def item_key(x):
    return x[0]


li.sort(key=item_key)
print(li)

```



### tuple

```python
# 只读数组
tp = (1, 2, 3)
try:
    tp[0] = 100
except Exception as e:
    print(e)

```



### set

```python
# 元素唯一
# list to set
s = set([1, 2, 2, 3, 3, 4, 5])
print(s)
# tuple to set
s = set((2, 3, 4, 5, 6, 2, 1, 9))
print(s)

```



### dict

```python
# key<->value对应的hash表
di = {'k1': 'v1', 'k2': 'v2'}
di['k3'] = 'v3'
di['k4'] = 'v4'

for k in di:
    print(di[k])

for k, v in di.items():
    print(k, v)

```



### slice

```python
# [1, 2, 3, 4, 5]
#  => [1, 2, 3]
#  => [3, 4]
li = [1, 2, 3, 4, 5]
li_0_2 =li[0:3] # 0 <= ? < 3
# 等价li[:3]
print(li_0_2)
# [start, end, step] => [start, start + step, ..., < end]
# start默认是0，end默认-1，step默认1
li_last_3 = li[-1:-4:-1]
print(li_last_3)

# 直接用切片反转数组
print(li[::-1])
print(li[-2::-1])

# 切片是复制
li_0_2[-1] = 100
print(li)

```



### list & string

```python
s = 'abcdefg'
try:
    str[0] = 'x'
except Exception as e:
    print(e)

# 修改字符串
li = list(s)
# print(li)
li[0] = 'x'
s = ''.join(li)
print(s)
s = '-'.join(li)
print(s)

# 切割
s = 'abc,def,ghi'
p1, p2, p3 = s.split(',')
print(p1, p2, p3)

# 下标访问和切片
s = 'abcdefg'
print(s[0], s[-1])
print(s[2:5])

```



String

* find
* index
* count
* 



## Object

```python
# 用type查看对象类型
print(type([1, 2, 3, 4]))
print(type('abcd'))
print(type({1: 2, 2: 3}))

# 用dir查看属性和方法
print(dir(list))


class Clazz(object):
    # self参考C++的this指针！
    def __init__(self, x, y):
        self.x = x
        self.y = y

    # 声明成员函数的时候，第一个参数一定是self，不要忘记！
    def display(self):
        print(self.x, self.y)


print(type(Clazz))
clz = Clazz(100, 200)
clz.display()  # => display(clz)


class Base:
    def run(self):
        print('Base::run')


class Tom(Base):
    def run(self):
        print('Tom::run')


t = Tom()
print(isinstance(t, Base))
t.run()

# ---------------
def run(runner):
    runner.run()

# R1重写了run, 实现了runner
class R1:
    def run(self):
        print('R1::run')

# R2重写了run, 实现了runner
class R2:
    def run(self):
        print('R2::run')


run(R1())
run(R2())

```



## File

```python
# handle在对文件操作的异常
with open('text.txt') as f:
  	print(dir(f))
    for line in f.readlines():
        print(line)

with open('text.txt', 'rb') as f:
    print(f.read())

s = 'abcdefg'
b = bytes(s)
print(b)

# 回去自己练习write函数写入

```



## Thread

```python
import threading

def thread_func(x):
    # 自己加sleep和其它复杂操作看效果
    print('%d\n' % (x * 100))

threads = []
for i in range(5):
    threads.append(threading.Thread(target = thread_func, args = (100, )))

for thread in threads:
    thread.start()

for thread in threads:
    thread.join()

```

