## OverView

### Spark Streaming是什么

Spark Streaming is an extension of the core Spark API that enables scalable, high-throughput, fault-tolerant **stream processing of live data streams**. Data can be ingested from many sources like **Kafka**, **Flume**, **Kinesis**, or **TCP sockets**, and can be processed using complex algorithms expressed with high-level functions like `map`, `reduce`, `join` and `window`.  Finally, processed data can be pushed out to filesystems, databases, and live dashboards. In fact, you can apply Spark’s [machine learning](http://spark.apache.org/docs/2.1.1/ml-guide.html) and [graph processing](http://spark.apache.org/docs/2.1.1/graphx-programming-guide.html) algorithms on data streams.

![Spark Streaming](Spark_Streaming.assets/streaming-arch.png)



## 入门

### WordCount案例

> 使用netcat工具向9999端口不断的发送数据，通过SparkStreaming读取端口数据并统计不同单词出现的次数

```xml
<dependency>
    <groupId>org.apache.spark</groupId>
    <artifactId>spark-streaming_2.11</artifactId>
    <version>2.1.1</version>
</dependency>
```

```scala
object WordCount {
    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf()
            .setMaster("local[*]")
            .setAppName("WordCount")

        val streamingContext: StreamingContext = new StreamingContext(conf, Seconds(5))

        val inputDStream: ReceiverInputDStream[String] = streamingContext.socketTextStream("hadoop102", 10000)

        val dstream: DStream[(String, Int)] = inputDStream.flatMap(_.split("\\W+"))
            .map((_, 1))
            .reduceByKey(_ + _)

        dstream.print()
        //inputDStream.start()

        streamingContext.start()
        streamingContext.awaitTermination()
    }
}
```

```shell
> nc -lk 9999
```

### WordCount解析

Discretized Stream是Spark Streaming的基础抽象，代表持续性的数据流和经过各种Spark原语操作后的结果数据流。在内部实现上，DStream是一系列连续的RDD来表示。每个RDD含有一段时间间隔内的数据



## DStream创建

### RDD队列

> 循环创建几个RDD，将RDD放入队列。通过SparkStream创建Dstream，计算WordCount

```scala
object QueueDemo {
    def main(args: Array[String]): Unit = {
        val conf: SparkConf = new SparkConf()
            .setAppName("")
            .setMaster("local[*]")
        val sCtx = new StreamingContext(conf, Seconds(5))
        val queue: mutable.Queue[RDD[Int]] = mutable.Queue[RDD[Int]]()
        val dStream: InputDStream[Int] = sCtx.queueStream(queue, true)

        dStream.reduce(_ + _).print()
        //dStream.print
        sCtx.start()

        for (i <- 1 to 3) {
            //while (true) {
            queue += sCtx.sparkContext.parallelize(1 to 100)
            Thread.sleep(2000)
        }

        sCtx.awaitTermination()
    }
}
```

### 自定义数据源 receiver

> 自定义数据源，实现监控某个端口号，获取该端口号内容

编写方式参考streamingContext.socketTextStream中的SocketReceiver.scala

CustomerReceiver.scala

```scala
class CustomerReceiver(host: String, port: Int) extends Receiver[String](StorageLevel.MEMORY_ONLY) {

    //最初启动的时候，调用该方法，作用为：读数据并将数据发送给Spark
    override def onStart(): Unit = {
        new Thread("Socket Receiver") {
            override def run() {
                receive()
            }
        }.start()
    }

    //读数据并将数据发送给Spark
    def receive(): Unit = {

        //创建一个Socket
        var socket: Socket = new Socket(host, port)

        //定义一个变量，用来接收端口传过来的数据
        var input: String = null

        //创建一个BufferedReader用于读取端口传来的数据
        val reader = new BufferedReader(new InputStreamReader(socket.getInputStream, StandardCharsets.UTF_8))

        //读取数据
        input = reader.readLine()

        //当receiver没有关闭并且输入数据不为空，则循环发送数据给Spark
        while (!isStopped() && input != null) {
            store(input)
            input = reader.readLine()
        }

        //跳出循环则关闭资源
        reader.close()
        socket.close()

        //重启任务
        restart("restart")
    }

    override def onStop(): Unit = {}
}
```

CustomerReceiverDemo.scala

```scala
object CustomerReceiverDemo {
    def main(args: Array[String]): Unit = {

        //1.初始化Spark配置信息
        val sparkConf = new SparkConf().setMaster("local[*]")
            .setAppName("StreamWordCount")

        //2.初始化SparkStreamingContext
        val ssc = new StreamingContext(sparkConf, Seconds(5))

        //3.创建自定义receiver的Streaming
        val lineStream = ssc.receiverStream(new CustomerReceiver("hadoop102", 9999))

        //4.将每一行数据做切分，形成一个个单词
        val wordStream = lineStream.flatMap(_.split("\t"))

        //5.将单词映射成元组（word,1）
        val wordAndOneStream = wordStream.map((_, 1))

        //6.将相同的单词次数做统计
        val wordAndCountStream = wordAndOneStream.reduceByKey(_ + _)

        //7.打印
        wordAndCountStream.print()

        //8.启动SparkStreamingContext
        ssc.start()
        ssc.awaitTermination()
    }
}
```

### Kafka数据源

## 转换

## 输出