

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

### 4.1.2 添加配置

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

[atguigu@hadoop102 hadoop]$ xsync core-site.xml