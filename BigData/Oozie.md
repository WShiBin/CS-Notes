## Oozie overview 

> 基于工作流引擎的开源框架, Cloudera公司贡献给Apache, 提供对Hadoop MapReduce、Pig Jobs的任务调度与协调。Oozie需要部署到Java Servlet容器中运行。主要用于定时调度任务，多任务可以按照执行的逻辑顺序调度



## Oozie的功能模块

- Workflow工作流: 顺序执行流程节点，支持fork（分支多个节点），join（合并多个节点为一个）
- Coordinator协调者: 定时触发workflow
- Bundle Job 绑定多个Coordinator



## CDH Hadoop Install and conf

```shell
> tar -zxvf ../soft/hadoop-2.5.0-cdh5.3.6.tar.gz  -C ./cdh/
> tar -zxvf ../soft/oozie-4.0.0-cdh5.3.6.tar.gz  -C ./
```





hadoop-env.sh/mapred-env.sh/yarn-env.sh

```shell
export JAVA_HOME=/opt/module/jdk1.8.0_121
```

core-site.xml

```xml
<configuration>
  <!-- 指定HDFS中NameNode的地址 -->
  <property>
    <name>fs.defaultFS</name>
    <value>hdfs://hadoop004:8020</value>
  </property>
  <!-- 指定Hadoop运行时产生文件的存储目录 -->
  <property>
    <name>hadoop.tmp.dir</name>
    <value>/opt/module/cdh/hadoop-2.5.0-cdh5.3.6/data/tmp</value>
  </property>
  <!-- Oozie Server的Hostname -->
  <property>
    <name>hadoop.proxyuser.ben.hosts</name>
    <value>*</value>
  </property> <!-- 允许被Oozie代理的用户组 -->
  <property>
    <name>hadoop.proxyuser.ben.groups</name>
    <value>*</value>
  </property>
</configuration>
```

hdfs-site.xml

```xml
<configuration>
  <!-- 副本数 -->
  <property>
    <name>dfs.replication</name>
    <value>1</value>
  </property>
  <!-- 指定Hadoop辅助名称节点主机配置 -->
  <property>
    <name>dfs.namenode.secondary.http-address</name>
    <value>hadoop006:50090</value>
  </property>
</configuration>
```

mapred-site.xml

```xml
<configuration>
  <!-- 指定mr运行在yarn上 -->
  <property>
    <name>mapreduce.framework.name</name>
    <value>yarn</value>
  </property>
  <!-- 配置 MapReduce JobHistory Server 地址 ，默认端口10020 -->
  <property>
    <name>mapreduce.jobhistory.address</name>
    <value>hadoop005:10020</value>
  </property>
  <!-- 配置 MapReduce JobHistory Server web ui 地址， 默认端口19888 -->
  <property>
    <name>mapreduce.jobhistory.webapp.address</name>
    <value>hadoop005:19888</value>
  </property>
</configuration>
```

yarn-site.xml

```xml
<configuration>
  <!-- reducer获取数据的方式 -->
  <property>
    <name>yarn.nodemanager.aux-services</name>
    <value>mapreduce_shuffle</value>
  </property>
  <!-- 指定YARN的ResourceManager的地址 -->
  <property>
    <name>yarn.resourcemanager.hostname</name>
    <value>hadoop006</value>
  </property>
  <!-- 日志聚焦功能是否开启 -->
  <property>
    <name>yarn.log-aggregation-enable</name>
    <value>true</value>
  </property>
  <!-- 日志保留时间设置7天 -->
  <property>
    <name>yarn.log-aggregation.retain-seconds</name>
    <value>604800</value>
  </property>
  <!-- 任务历史服务 -->
  <property>
    <name>yarn.log.server.url</name>
    <value>http://hadoop005:19888/jobhistory/logs/</value>
  </property>
</configuration>
```



launch

```shell
> sbin/start-dfs.sh
> sbin/start-yarn.sh
> sbin/mr-jobhistory-daemon.sh start historyserver
```

[http://hadoop004:50070](http://hadoop004:50070/)





## Oozie install and conf

```shell
> tar -zxvf ../soft/oozie-4.0.0-cdh5.3.6.tar.gz  -C ./
> tar -zxvf oozie-hadooplibs-4.0.0-cdh5.3.6.tar.gz -C ../
> mkdir libext  # 名字是特定
> cp hadooplibs/hadooplib-2.5.0-cdh5.3.6.oozie-4.0.0-cdh5.3.6/* libext/ 	# copy Jar包
> cp /opt/module/hive/lib/mysql-connector-java-5.1.7-bin.jar ./libext/  # mysql 驱动
> cp /opt/soft/ext-2.2.zip ./libext/  # copy web project
```

oozie-site.xml

```xml
    <property>
        <name>oozie.service.JPAService.jdbc.driver</name>
        <value>com.mysql.jdbc.Driver</value>
    </property>
    <property>
        <name>oozie.service.JPAService.jdbc.url</name>
        <value>jdbc:mysql://hadoop005:3306/oozie</value>
    </property>
    <property>
        <name>oozie.service.JPAService.jdbc.username</name>
        <value>root</value>
    </property>
    <property>
        <name>oozie.service.JPAService.jdbc.password</name>
        <value>shibin</value>
    </property>
		<!-- oozie 关联到 hadoop -->
    <property>
        <name>oozie.service.HadoopAccessorService.hadoop.configurations</name>
        <value>*=/opt/module/cdh/hadoop-2.5.0-cdh5.3.6/etc/hadoop</value>
    </property>
```

## Setup Oozie

MySQL 建库

```sql
> mysql -uroot -p
mysql> create database oozie;
```

```shell
# 上传Oozie目录下的xxx.yarn.tar.gz文件到HDFS, 文件会在 hdfs 上自行解压
> bin/oozie-setup.sh sharelib create -fs hdfs://hadoop102:8020 -locallib oozie-sharelib-4.0.0-cdh5.3.6-yarn.tar.gz  
> bin/ooziedb.sh create -sqlfile oozie.sql -run   # 创建oozie.sql文件,
> bin/oozie-setup.sh prepare-war    # 打包项目，生成war包

> bin/oozied.sh start    # Oozie 启动
> bin/oozied.sh stop		# Oozie关闭
```



## Oozie的使用

