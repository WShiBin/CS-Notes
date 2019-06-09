## RDD Overview

RDD（Resilient Distributed Dataset）叫做弹性分布式**数据集**，是Spark中最基本的数据抽象。代码中是一个抽象类，它代表一个弹性的、不可变、可分区、里面的元素可并行计算的**集合**



### RDD特点

* 弹性
* 分区
* 只读
* 依赖
* Cache
* Checkpoint



## RDD 编程模型

create —> transformation —> action

### RDD创建

- 从集合中创建 RDD
- 从外部存储创建 RDD
- 从其他 RDD 转换得到新的 RDD。

```scala
object RDDCreate {

  def main(args: Array[String]): Unit = {
    val conf: SparkConf = new SparkConf()
      .setAppName("RddCreate")
      .setMaster("local[*]")
    val sc = new SparkContext(conf)

    // 创建 RDD, 同时也可以设置分区数
    val rdd1: RDD[Int] = sc.makeRDD(Array(1, 2, 3, 4, 5, 5, 6))
    val rdd2: RDD[Int] = sc.parallelize(Array(1, 2, 3, 4, 5, 6, 7))

    // 可以是本地文件系统,远程文件系统,如hdfs://..., s3n://...,SequenceFiles, hadoop inputformat
    // 可以是目录,也可以是文件或压缩文件,
    val rdd3: RDD[String] = sc.textFile("file path")
  }
}
```



### RDD Transformations

1. Value 类型
   * map
   * mapPartitions
   * mapPartitionsWithIndex
   * flatMap
   * glom
   * groupBy
   * filter
   * sample
   * distinct
   * coalesce
   * repartition
   * sortBy
   * pipe
2. 双 Value 类型
   * union
   * subtract
   * intersection
   * cartesian
   * zip
3. Key-Value 类型
   * partitionBy
   * reduceByKey
   * groupByKey
   * reduceByKey
   * aggregateByKey
   * foldByKey
   * combineByKey
   * sortByKey
   * mapValues
   * join
   * cogroup

```scala
// 都是调用combineByKeyWithClassTag
// 三个角度:零值-区内-区间

// 没有零值,区内函数和区间函数一样
reduceByKey(func: (V, V) => V)
    combineByKeyWithClassTag[V]((v: V) => v, func, func, partitioner)

// zeroValue,区内和区间相同
foldByKey(zeroValue: V)(func: (V, V) => V):
    combineByKeyWithClassTag[V]((v: V) => cleanedFunc(createZero(), v), cleanedFunc, cleanedFunc, partitioner)

// zeroValue:每个分区取一个零值
// seqOp:区内,
// combOp:分区间
aggregateByKey[U: ClassTag](zeroValue: U)(seqOp: (U, V) => U, combOp: (U, U) => U):
    combineByKeyWithClassTag[U]((v: V) => cleanedSeqOp(createZero(), v), cleanedSeqOp, combOp, partitioner)

// createCombiner:来自分区的第一个value
// mergeValue:区内
// mergeCombiners:区间
combineByKey[C](createCombiner: V => C, mergeValue: (C, V) => C, mergeCombiners: (C, C) => C)
    combineByKeyWithClassTag(createCombiner, mergeValue, mergeCombiners, partitioner, mapSideCombine, serializer)(null)
```



### RDD Actions

* reduce
* collect
* count
* first
* take
* takeOrdered
* aggregate
* fold
* saveAsTextFile
* saveAsSequenceFile
* countByKey
* foreach



### RDD中的函数传递

传递一个方法

传递一个属性



### RDD依赖关系

#### Lineage

#### 窄依赖

#### 宽依赖

#### DAG

#### 任务划分

* Application
* Job
* Stage
* Task

![image-20190427212358365](SparkCore.assets/image-20190427212358365.png)

> Application->Job->Stage->Task每一层都是1对n的关系

### RDD缓存

RDD通过persist方法或cache方法可以将前面的计算结果缓存，默认情况下 persist() 会把数据以序列化的形式缓存在 JVM 的堆空间中

但是并不是这两个方法被调用时立即缓存，而是触发后面的action时，该RDD将会被缓存在计算节点的内存中，并供后面重用

```scala
object CacheDemo {
    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf().setAppName("").setMaster("local[*]")
        val sc = new SparkContext(conf)

        val rdd1: RDD[String] = sc.parallelize(Array("shibin"))
        val rdd2: RDD[String] = rdd1.map(_ + System.currentTimeMillis()) //不缓存会被重新计算
        		// 注释或不注释,数据不同
        		.cache()

        for (elem <- 1.to(10)) {
          	// action(collect)动作才会触发cache 缓存,提供下一次使用
            println(rdd2.collect().mkString)
        }

        sc.stop()
    }
}
```



**cache 调用无参的 persist**

> 缓存有可能丢失，或者存储存储于内存的数据由于内存不足而被删除，RDD的缓存容错机制保证了即使缓存丢失也能保证计算的正确执行。通过基于RDD的一系列转换，丢失的数据会被重算，由于RDD的各个Partition是相对独立的，因此只需要计算丢失的部分即可，并不需要重算全部Partition。

![image-20190427205713538](SparkCore.assets/image-20190427205713538.png)

![image-20190427205345793](SparkCore.assets/image-20190427205345793.png)



### RDD Checkpoint

Spark中对于数据的保存除了持久化操作之外，还提供了一种检查点的机制，检查点（**本质是通过将RDD写入Disk做检查点**）是为了通过lineage做容错的辅助，lineage过长会造成容错成本过高，这样就不如在中间阶段做检查点容错，如果之后有节点出现问题而丢失分区，从做检查点的RDD开始重做Lineage，就会减少开销。检查点通过将数据写入到HDFS文件系统实现了RDD的检查点功能。

为当前RDD设置检查点。该函数将会创建一个二进制的文件，并存储到checkpoint目录中，该目录是用[Spark](https://www.iteblog.com/archives/tag/spark/)Context.setCheckpointDir()设置的。**在checkpoint的过程中，该RDD的所有依赖于父RDD中的信息将全部被移除**。对RDD进行checkpoint操作并不会马上被执行，必须执行Action操作才能触发。

```scala
object CheckPointDemo {
    def main(args: Array[String]): Unit = {
        // 防止可能出现的权限问题
        System.setProperty("HADOOP_USER_NAME", "ben")

        val conf: SparkConf = new SparkConf() .setAppName("") .setMaster("local[*]")
        val sc = new SparkContext(conf)
        sc.setCheckpointDir("hdfs://hadoop102:9000/checkpoint")

        val rdd: RDD[String] = sc.parallelize(Array("atguigu"))
        val chRdd: RDD[String] = rdd.map(_ + System.currentTimeMillis)

      	// 先缓存
        chRdd.cache()
        chRdd.checkpoint()

        for (elem <- 1 to 10) {
            println(chRdd.collect().mkString)
        }

        sc.stop()
    }
}
```



## 键值对RDD数据分区

* HashPartitioner(Default)

* RangePartitioner

> 只有Key-Value类型的RDD才有分区,非Key-Value类型的RDD分区的值是None

### 获取分区

RDD的partitioner 属性来获取 RDD 的分区方式。它会返回一个 scala.Option 对象， 通过get方法获取其中的值pairs.partitioner

### Hash分区

HashPartitioner分区的原理：对于给定的key，计算其hashCode，并除以分区的个数取余，如果余数小于0，则用余数+分区的个数（否则加0），最后返回的值就是这个key所属的分区ID

```scala
object HashDemo {
    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf()
            .setAppName("")
            .setMaster("local[*]")
        val sc = new SparkContext(conf)
        val rdd: RDD[(Int, Int)] = sc.parallelize(List((1, 3), (1, 2), (2, 4), (2, 3), (3, 6), (3, 8)), 8)
        val partitioner: Option[Partitioner] = rdd.partitioner
        val rdd2: RDD[(Int, Int)] = rdd.partitionBy(new HashPartitioner(4))
        rdd2.mapPartitionsWithIndex((index, it) => {
            println(index)
            it
        }).collect()
        println("----------------")

        // 是什么分区器
        println(rdd2.partitioner)
        // 有多小个分区
        println(rdd2.partitioner.get.numPartitions)
    }
}
```



HashPartitioner源码

```scala
	// HashPartitioner
	def getPartition(key: Any): Int = key match {
    case null => 0
    case _ => Utils.nonNegativeMod(key.hashCode, numPartitions)
  }

  // utils.scala
  def nonNegativeMod(x: Int, mod: Int): Int = {
    val rawMod = x % mod
    rawMod + (if (rawMod < 0) mod else 0)
  }
```



### Range 分区

HashPartitioner分区弊端：可能导致每个分区中**数据量的不均匀**，极端情况下会导致某些分区拥有RDD的全部数据

RangePartitioner作用：将一定范围内的数映射到某一个分区内，尽量保证每个分区中数据量的均匀，而且分区与分区之间是有序的，一个分区中的元素肯定都是比另一个分区内的元素小或者大，但是分区内的元素是不能保证顺序的。简单的说就是将一定范围内的数映射到某一个分区内。实现过程为：

第一步：先从整个RDD中抽取出样本数据，将样本数据排序，计算出每个分区的最大key值，形成一个Array[KEY]类型的数组变量rangeBounds；

第二步：判断key在rangeBounds中所处的范围，给出该key值在下一个RDD中的分区id下标；该分区器要求RDD中的KEY类型必须是可以排序的



### 自定义分区

* 继承Partitioner
* 重写numPartitions,getPartition
* partitionBy,join,groupByKey 传入自定义 Partitioner

```scala
object CustomerDemo {

    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf()
            .setAppName("")
            .setMaster("local[*]")
        val sc = new SparkContext(conf)
        val rdd: RDD[(Int, Int)] = sc.parallelize(List((1, 3), (1, 2), (2, 4), (2, 3), (3, 6), (3, 8)), 8)
        val rdd2: RDD[(Int, Int)] = rdd.partitionBy(new CustomerPartitioner(4))
        rdd2.mapPartitionsWithIndex((index, it) => {
            println(index, it.toList)
            it
        }).collect()

        println(rdd2.partitioner)
        sc.stop()
    }
}

// 继承Partitioner
class CustomerPartitioner(numParts: Int) extends Partitioner {

    //覆盖分区数
    override def numPartitions: Int = numParts

    //覆盖分区号获取函数
    override def getPartition(key: Any): Int = {
        val ckey: String = key.toString
        ckey.substring(ckey.length - 1).toInt % numParts
    }
}
```



## 数据读取与保存

* 件格式分为：Text文件、Json文件、Csv文件、Sequence文件以及Object文件
* 文件系统分为：本地文件系统、HDFS、HBASE以及数据库



### Text

```scala
object TextDemo {
    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf()
            .setAppName("")
            .setMaster("local[*]")
        val sc = new SparkContext(conf)
        val hdfsRdd: RDD[String] = sc.textFile("hdfs://hadoop102:9000/user/ben/zookeeper.out")
        hdfsRdd.saveAsTextFile("file:///Users/Ben/Desktop/fruitOut")
        sc.stop()
    }
}
```



### Json

person.json(/opt/module/spark-2.1.1-local/examples/src/main/resources/people.json)

![image-20190427200616093](SparkCore.assets/image-20190427200616093.png)

```scala
object JsonDemo {
    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf()
            .setAppName("")
            .setMaster("local[*]")
        val sc = new SparkContext(conf)
        val jsonRdd: RDD[String] = sc.textFile("file:///Users/Ben/Desktop/people.json")
        val result: RDD[Option[Any]] = jsonRdd.map(JSON.parseFull)
        println(result.collect().foreach(item => println(item.get)))
        sc.stop()
    }
}
```

output:

```
Map(name -> Michael)
Map(name -> Andy, age -> 30.0)
Map(name -> Justin, age -> 19.0)
```



### SequenceFile

> 一个分区一个文件
>
> SequenceFile文件只针对PairRDD

```scala
object SequenceFileDemo {
    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf()
        		.setAppName("")
        		.setMaster("local[*]")
        val sc = new SparkContext(conf)

        val rdd: RDD[(Int, Int)] = sc.parallelize(Array((1,2),(3,4),(5,6)))
        val rdd2: RDD[(Int, Int)] = rdd.partitionBy(new HashPartitioner(1))
        rdd2.saveAsSequenceFile("file:///Users/Ben/Desktop/seqFile")
        sc.stop()
    }
}
```



### HDFS



### HBase



### MySQL

```scala
object JDBCDemo {

    private val driver = "com.mysql.jdbc.Driver"
    private val url = "jdbc:mysql://hadoop102:3306/rdd"
    private val userName = "root"
    private val passWd = "shibin"

    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf().setAppName("").setMaster("local[*]")
        val sc = new SparkContext(conf)

        // get data
        getData(sc)

        // insert data
        sc.parallelize(List("Female", "Male", "Female")).foreachPartition(insertData)
        sc.stop()
    }

    def getData(sc: SparkContext) = {
        val jdbcRDD = new JdbcRDD(
            sc,
            () => {
                Class.forName(driver)
                DriverManager.getConnection(url, userName, passWd)
            },
            "select * from user where ? <= id and id <= ?",
            1,
            20,
            2,
            result => result.getString(2)
        )
        jdbcRDD.collect().foreach(println)
    }

    def insertData(iterator: Iterator[String]): Unit = {
        Class.forName(driver).newInstance()
        val conn = java.sql.DriverManager.getConnection(url, userName, passWd)
        iterator.foreach(data => {
            val ps = conn.prepareStatement("insert into rddtable(name) values (?)")
            ps.setString(1, data)
            ps.executeUpdate()
        })
    }
}
```



## RDD编程进阶

### 累加器

```scala
object AccDemo {
    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf()
            .setAppName("")
            .setMaster("local[*]")
        val sc = new SparkContext(conf)
        var a = 1
        sc.parallelize(Array(1, 2, 3, 4, 5))
            .foreach(x => {
                Thread.sleep(200)
                a += 1 // 这个会去在不同的 executor 上去执行
                println(a)
            })
        println("----------------------")
        println(a) // 1 这个 a 是 driver 上的 a
        sc.stop()
    }
}
```

> App -> job -> stage -> task 执行



#### 系统累加器

LongAccumulator

```scala
object AccDemo {
    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf()
            .setAppName("")
            .setMaster("local[*]")
        val sc = new SparkContext(conf)
        val rdd: RDD[Int] = sc.parallelize(Array(1, 2, 3, 4, 5, 6, 7))
        val longAccumulator = new LongAccumulator()
				// 注册
        sc.register(longAccumulator)

        rdd.foreach(x => {
            longAccumulator.add(x)
        })

        println(longAccumulator.value)
        sc.stop()
    }
}
```



#### 自定义累加器

步骤:

* 继承AccumulatorV2
* 泛型第一个参数:输入类型,累加传入的类型
* 泛型第二个参数:value 值类型,传出的类型
* 重写方法

**自定义求和累加器**

```scala
class IntAccumulator extends AccumulatorV2[Int, Int] {
    private var sum: Int = 0

    override def isZero: Boolean = sum == 0

    override def copy(): AccumulatorV2[Int, Int] = {
        val newAcc = new IntAccumulator
        //newAcc._count = this._count
        newAcc.sum = this.sum
        newAcc
    }

    override def reset(): Unit = {
        this.sum = 0
    }

    override def add(v: Int): Unit = sum += v

    override def merge(other: AccumulatorV2[Int, Int]): Unit = {
        other match {
            case a: IntAccumulator => this.sum += a.sum
            case _ =>
        }
    }

    override def value: Int = sum
}
```



**自定义求平均数累加器**

```scala
class MapAccumulator extends AccumulatorV2[Int, Map[String, Double]] {

    private var map = Map[String, Double]()

    override def isZero: Boolean = map.isEmpty

    override def copy(): AccumulatorV2[Int, Map[String, Double]] = {
        val acc = new MapAccumulator
        acc.map ++= this.map
        acc
    }

    override def reset(): Unit = Map[String, Double]()

    override def add(v: Int): Unit = {
        map += "sum" -> (map.getOrElse("sum", 0d) + v)
    }

    override def merge(other: AccumulatorV2[Int, Map[String, Double]]): Unit = other match {
        case o: MapAccumulator =>
            map += "sum" -> (map.getOrElse("sum", 0) + o.map.getOrElse("sum", 0d))
            map += "count" -> (map.getOrElse("count", 0d) + o.map.getOrElse("count", 0d))
        case _ =>
    }

    override def value: Map[String, Double] = {
        map += "avg" -> map.getOrElse("sum", 0d) / map.getOrElse("count", 1d)
        map
    }
}
```



**自定义:字符串放到集合,数字累加**

```scala
	val rdd: RDD[Any] = sc.parallelize(Array("a", 2, "b", 4, "c", 6, 7))
```

```scala
class StringIntAccumulator extends AccumulatorV2[Any, (List[String], Int)] {

    private var list = List[String]()
    private var sum = 0

    override def isZero: Boolean = list.isEmpty && sum == 0

    override def copy(): AccumulatorV2[Any, (List[String], Int)] = {
        val other = new StringIntAccumulator
        other.list = this.list
        other.sum = this.sum
        other
    }

    //override def copy(): AccumulatorV2[List[String], Int] = {
    //}

    override def reset(): Unit = {
        list = List[String]()
        sum = 0
    }

    override def add(v: Any): Unit = v match {
        case s: String => list :+= s
        case i: Int => sum += i
        case _ =>
    }

    override def merge(other: AccumulatorV2[Any, (List[String], Int)]): Unit = other match {
        case acc: StringIntAccumulator =>
            list ++= acc.list
            sum += acc.sum
        case _ =>
    }

    override def value: (List[String], Int) = (list, sum)
}
```



### 广播变量（调优策略）

一个 spark app 执行时,会将一个变量序列化, 传输到每一个 task 中, 这样比较消耗资源, 因为多个 task 可能在一个 executor 上, task 是线程, 在同一个 executor (进程上)资源是共享的, 优化

```scala
object BroadCastDemo {
    def main(args: Array[String]): Unit = {
        val arr = Array(10, 20)
        val conf = new SparkConf().setAppName("Practice").setMaster("local[2]")
        val sc = new SparkContext(conf)
        val rdd1 = sc.parallelize(Array(30, 50, 70, 60, 10, 20))
        val broadArr: Broadcast[Array[Int]] = sc.broadcast(arr)
        rdd1.foreach(x => {
            // 使用广播变量
            val arr: Array[Int] = broadArr.value
        })
        sc.stop()
    }
}
```

