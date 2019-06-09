

## configuration

* hadoop-env.sh
* mapred-env.sh
* yarn-env.sh
* slaves
* core-site.xml
* hdfs-site.xml
* mapred-site.xml
* yarn-site.xml



|      | 服务器hadoop102  | 服务器hadoop103            | 服务器hadoop104           |
| ---- | ---------------- | -------------------------- | ------------------------- |
| HDFS | NameNodeDataNode | DataNode                   | DataNodeSecondaryNameNode |
| Yarn | NodeManager      | ResourcemanagerNodeManager | NodeManager               |



hadoop-env.sh/mapred-env.sh/yarn-env.sh

```shell
export JAVA_HOME=/opt/module/jdk1.8.0_144
```

slaves

```
hadoop102
hadoop103
hadoop104
```

core-site.xml

```xml
<configuration>
  <!-- 指定HDFS中NameNode的地址 -->
  <property>
    <name>fs.defaultFS</name>
    <value>hdfs://hadoop102:9000</value>
  </property>
  <!-- 指定Hadoop运行时产生文件的存储目录 -->
  <property>
    <name>hadoop.tmp.dir</name>
    <value>/opt/module/hadoop-2.7.2/data/tmp</value>
  </property>
  <!-- 增加配置支持LZO压缩 -->
  <property>
    <name>io.compression.codecs</name>
    <value>
    org.apache.hadoop.io.compress.GzipCodec,
    org.apache.hadoop.io.compress.DefaultCodec,
    org.apache.hadoop.io.compress.BZip2Codec,
    org.apache.hadoop.io.compress.SnappyCodec,
    com.hadoop.compression.lzo.LzoCodec,
    com.hadoop.compression.lzo.LzopCodec
    </value>
  </property>
  <property>
    <name>io.compression.codec.lzo.class</name>
    <value>com.hadoop.compression.lzo.LzoCodec</value>
  </property>
</configuration>
```

hdfs-site.xml

```xml
<configuration>
  <!-- 指定HDFS副本的数量 -->
  <property>
    <name>dfs.replication</name>
    <value>1</value>
  </property>
  <!-- 指定Hadoop辅助名称节点主机配置 -->
  <property>
    <name>dfs.namenode.secondary.http-address</name>
    <value>hadoop104:50090</value>
  </property>
</configuration>
```

mapred-site.xml

```xml
<configuration>
  <!-- 指定MR运行在YARN上 -->
  <property>
    <name>mapreduce.framework.name</name>
    <value>yarn</value>
  </property>
  <!-- 历史服务器端地址 -->
  <property>
    <name>mapreduce.jobhistory.address</name>
    <value>hadoop102:10020</value>
  </property>
  <!-- 历史服务器web端地址 -->
  <property>
    <name>mapreduce.jobhistory.webapp.address</name>
    <value>hadoop102:19888</value>
  </property>
</configuration>
```

yarn-site.xml

```xml
<configuration>
  <!-- Reducer获取数据的方式 -->
  <property>
    <name>yarn.nodemanager.aux-services</name>
    <value>mapreduce_shuffle</value>
  </property>
  <!-- 指定YARN的ResourceManager的地址 -->
  <property>
    <name>yarn.resourcemanager.hostname</name>
    <value>hadoop103</value>
  </property>
  <!-- 日志聚集功能使能 -->
  <property>
    <name>yarn.log-aggregation-enable</name>
    <value>true</value>
  </property>
  <!-- 日志保留时间设置7天 -->
  <property>
    <name>yarn.log-aggregation.retain-seconds</name>
    <value>604800</value>
  </property>
</configuration>
```



## Cmd

```shell
> hdfs namenode -format	# 多次格式化需要删除 data,logs
> hadoop-daemon.sh start namenode
> hadoop-daemon.sh stop namenode
> hadoop-daemon.sh start datanode
> hadoop-daemon.sh start datanode
> jps
> yarn-daemon.sh start resourcemanager # 需要在指定节点启动	
> yarn-daemon.sh stop resourcemanager
> yarn-daemon.sh start nodemanager
> yarn-daemon.sh stop nodemanager
> mr-jobhistory-daemon.sh start historyserver
> start-dfs.sh
> stop-dfs.sh
> start-all.sh
> stop-all.sh

> hdfs dfs -rm -r -skipTrash /flume/20190528 # 跳过回收站
> bin/hadoop dfsadmin -safemode leave # 强制关闭safe mode

# 测试HDFS写性能
> hadoop jar hadoop-mapreduce-client-jobclient-2.7.2-tests.jar TestDFSIO -write -nrFiles 10 -fileSize 128MB
# 测试HDFS读性能
> hadoop jar hadoop-mapreduce-client-jobclient-2.7.2-tests.jar TestDFSIO -read -nrFiles 10 -fileSize 128MB
# 删除测试生成数据
> hadoop jar hadoop-mapreduce-client-jobclient-2.7.2-tests.jar TestDFSIO -clean
```







mr-jobhistory-daemon.sh start historyserver

http://hadoop004:8088/cluster

## WordCount

* mapper
* reducer
* driver
* 

## 自定义 FlowBean

## 自定义InputFormat

## 自定义分区Partitioner

将统计结果按照手机归属地不同省份输出到不同文件中

> HashPartitioner (default)

* 继承Partitioner<K, V>
  * <K,V>取决于Mapper.map 输出的K,V
* 重写getPartition
* job.setPartitionerClass()
* Job.setNumReduceTask()

## 自定义排序

* 继承WritableComparable

* 制定 compareTo

## Combiner的两种方式

## WritableComparator

## 自定义 OutputFormat

* TextOutputFormat
* SequenceFileOutputFormat





## 添加LZO支持包

1）先下载lzo的jar项目

<https://github.com/twitter/hadoop-lzo/archive/master.zip>

2）下载后的文件名是hadoop-lzo-master，它是一个zip格式的压缩包，先进行解压，然后用maven编译。生成hadoop-lzo-0.4.20。

3）将编译好后的hadoop-lzo-0.4.20.jar 放入hadoop-2.7.2/share/hadoop/common/

4）同步hadoop-lzo-0.4.20.jar到hadoop103、hadoop104

```xml
> xsync hadoop-lzo-0.4.20.jar
```

### 添加配置

1）core-site.xml增加配置支持LZO压缩

```xml
<configuration>
    <property>
        <name>io.compression.codecs</name>
        <value>
org.apache.hadoop.io.compress.GzipCodec,
org.apache.hadoop.io.compress.DefaultCodec,
org.apache.hadoop.io.compress.BZip2Codec,
org.apache.hadoop.io.compress.SnappyCodec,
com.hadoop.compression.lzo.LzoCodec,
com.hadoop.compression.lzo.LzopCodec
        </value>
    </property>

    <property>
        <name>io.compression.codec.lzo.class</name>
        <value>com.hadoop.compression.lzo.LzoCodec</value>
    </property>
</configuration>
```





2）同步core-site.xml到hadoop103、hadoop104

```shell
> xsync core-site.xml
```



## Hadoop优化

0）HDFS小文件影响

（1）影响NameNode的寿命，因为文件元数据存储在NameNode的内存中

（2）影响计算引擎的任务数量，比如每个小的文件都会生成一个Map任务

1）数据输入小文件处理：

（1）合并小文件：对小文件进行归档（Har）、自定义Inputformat将小文件存储成SequenceFile文件。

（2）采用ConbinFileInputFormat来作为输入，解决输入端大量小文件场景。

（3）对于大量小文件Job，可以开启JVM重用。

2）Map阶段

（1）增大环形缓冲区大小。由100m扩大到200m

（2）增大环形缓冲区溢写的比例。由80%扩大到90%

（3）减少对溢写文件的merge次数。

（4）不影响实际业务的前提下，采用Combiner提前合并，减少 I/O。

3）Reduce阶段

（1）合理设置Map和Reduce数：两个都不能设置太少，也不能设置太多。太少，会导致Task等待，延长处理时间；太多，会导致 Map、Reduce任务间竞争资源，造成处理超时等错误。

（2）设置Map、Reduce共存：调整slowstart.completedmaps参数，使Map运行到一定程度后，Reduce也开始运行，减少Reduce的等待时间。

（3）规避使用Reduce，因为Reduce在用于连接数据集的时候将会产生大量的网络消耗。

（4）增加每个Reduce去Map中拿数据的并行数

（5）集群性能可以的前提下，增大Reduce端存储数据内存的大小。 

4）IO传输

（1）采用数据压缩的方式，减少网络IO的的时间。安装Snappy和LZOP压缩编码器。

（2）使用SequenceFile二进制文件

5）整体

（1）MapTask默认内存大小为1G，可以增加MapTask内存大小为4-5g

（2）ReduceTask默认内存大小为1G，可以增加ReduceTask内存大小为4-5g

（3）可以增加MapTask的cpu核数，增加ReduceTask的CPU核数

（4）增加每个Container的CPU核数和内存大小

（5）调整每个Map Task和Reduce Task最大重试次数



