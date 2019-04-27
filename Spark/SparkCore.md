## RDD Overview



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



### RDD Actions