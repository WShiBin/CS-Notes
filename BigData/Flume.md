> Flume is a distributed, reliable, and available service for efficiently collecting, aggregating, and moving large amounts of log data. It has a simple and flexible architecture based on streaming data flows. It is robust and fault tolerant with tunable reliability mechanisms and many failover and recovery mechanisms. It uses a simple extensible data model that allows for online analytic application.

![Agent component diagram](Flume.assets/DevGuide_image00.png)



## Flume拦截器

```xml
    <dependency>
        <groupId>org.apache.flume</groupId>
        <artifactId>flume-ng-core</artifactId>
        <version>1.7.0</version>
    </dependency>
```

实现Interceptor 

### CMD

```bash
> bin/flume-ng agent --conf conf/ --name a1 --conf-file conf/file-flume-hdfs.conf -Dflume.root.logger=Debug,consol

```

* --conf flume配置
* --name flume名字
* --conf-file job任务的配置
* -D 动态配置



### Flume异常处理

1）问题描述：如果启动消费Flume抛出如下异常

> ERROR hdfs.HDFSEventSink: process failed
>
> java.lang.OutOfMemoryError: GC overhead limit exceeded

2）解决方案步骤：

（1）在hadoop102服务器的/opt/module/flume/conf/flume-env.sh文件中增加如下配置

```shell
export JAVA_OPTS="-Xms100m -Xmx2000m -Dcom.sun.management.jmxremote"
```

```shell
> xsync flume-env.sh
```

