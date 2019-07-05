spark位置
spark对比mapreduce

Spark SQL 和 HIVE
Spark 和 Storm
    实时 vs 准实时
    Storm:一条一条处理,吞吐量小, 实时
    Spark:一批一批处理,吞吐量大, 准实时

Spark 应用场景
    Spark vs MR 图
    Spark SQL vs HIVE 图
    Spark Streaming vs Storm

## 隐式转换
当类型不匹配,调用方法不存在,类型不匹配,
- 隐式函数
- 隐式类
    拓展其功能
- 隐式值
    默认值

wordcount 图
Spark调度 图

Spark core
Spark计算
    分布式:
    内存:内存放不下了放硬盘
    迭代式计算:和MR

broadcast: 只读,每个worker节点一份,减少driver到worker节点的网络传输次数
accumulator

RDD
    抽象
    弹性
    容错
源码
性能优化
Spark SQL
Spark Streaming


master资源调度算法
stage划分算法
task分配算法