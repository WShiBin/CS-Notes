## Install

<https://dev.mysql.com/downloads/mysql/>

```shell
> rpm -ivh MySQL-client-5.5.54-1.linux2.6.x86_64.rpm
> rpm -ivh MySQL-client-5.5.54-1.linux2.6.x86_64.rpm
> mysqladmin --version
> mysqladmin –u root password xxxxxx
> rpm -qa | grep -i "mysql"

> service mysql status
> service mysql start
> service mysql stop
> service mysql restart
> chkconfig --list | grep "mysql"
```

Mysql的安装位置

| 参数         | 路径                            | 解释                         | 备注                       |
| :----------- | :------------------------------ | ---------------------------- | -------------------------- |
| --datadir    | /var/lib/mysql/                 | mysql数据库文件的存放路径    |                            |
| --basedir    | /usr/bin                        | 相关命令目录                 | mysqladmin mysqldump等命令 |
| --plugin-dir | /usr/lib64/mysql/plugin         | mysql插件存放路径            |                            |
| --log-error  | /var/lib/mysql/jack.atguigu.err | mysql错误日志路径            |                            |
| --pid-file   | /var/lib/mysql/jack.atguigu.pid | 进程pid文件                  |                            |
| --socket     | /var/lib/mysql/mysql.sock       | 本地连接时用的unix套接字文件 |                            |
|              | /usr/share/mysql                | 配置文件目录                 | mysql脚本及配置文件        |
|              | /etc/init.d/mysql               | 服务启停相关脚本             |                            |



字符集乱码

```mysql
mysql> show variables like '%char%';
```



```mysql
[client]
default-character-set=utf8
[mysqld]
character_set_server=utf8
character_set_client=utf8
collation-server=utf8_general_ci
[mysql]
default-character-set=utf8
```

