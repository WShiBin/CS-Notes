

## Git支持的协议:

* 本地协议Local
* HTTP协议
* SSH协议
* Git协议



**Git支持的协议面临/需要解决的问题**

* 传输问题(传输,数据压缩)
* 校验问题(不是谁都可以去推送)



## 本地协议Local

用于本机,或团队每一 个成员都对一个共享的文件系统拥有访问权, 从本地版本库克隆(clone)、推送(push)以及拉取(pull)

```shell
$ git clone /opt/git/project.git
$ git clone file:///opt/git/project.git
$ git remote add local_proj /opt/git/project.git
```



## HTTP协议

分**智能(Smart)HTTP协议**和**哑(Dumb)HTTP协议**,在 Git 1.6.6版本之前只有一个方式可用，十分简单并且通常是只读模式的。 Git 1.6.6版本引入了一种新的、更智能的协议，让Git可以像通过 SSH 那样智能的协商和传输数据

#### 智能(Smart) HTTP 协议

优点:

* 可以使用 HTTP 协议的用户名/密码的基础授权，免去设置 SSH 公钥,系统上缺少 SSH 相关程序也可以使用git
* HTTP/S 协议被广泛使用，一般的企业防火墙都会允许这些端口的数据通过
* 即支持像 git:// 协议一样设置匿名服务，也可以像 SSH 协议一样提供传输时的授权和加密

```shell
$ git clone https://example.com/gitproject.git
$ git remote add origin https://example.com/gitproject.git
```

#### ~~哑(Dumb) HTTP 协议~~

 

## SSH 协议

```shell
$ git clone ssh://user@server/project.git
$ git clone user@server:project.git # scp风格写法
```

>  如果不指定用户，Git 会使用当前登录的用户名

**优点**

* 上手成本低,大家都熟悉
* SSH 访问是安全的 —— 所有传输数据都要经过授权和加密
* SSH 协议很高效，在传输前也会尽量压缩数据

**缺点**

* 不能通过他实现匿名访问, 在公司内网络使用还好,其它场景不太合适

## Git 协议

> 这是包含在 Git 里的一个特殊的守护进程;它监听在一个特定的端口(9418)，类似于 SSH 服务，但是访问无需任何授权。 要让版本库支持 Git 协议，需要先创建一个 git-daemon-export-ok 文 件 —— 它是 Git 协议守护进程为这个版本库提供服务的必要条件 —— 但是除此之外没有任何安全措施。 要么谁 都可以克隆这个版本库，要么谁也不能。 这意味着，通常不能通过 Git 协议推送。 由于没有授权机制，一旦你 开放推送操作，意味着网络上知道这个项目 URL 的人都可以向项目推送数据。 不用说，极少会有人这么做

**优点**

* Git 协议是 Git 使用的网络传输协议里最快的

**缺点**

* Git 协议缺点是缺乏授权机制

> Note:Github中repo的url(git@github.com:WShiBin/homebrew-versions.git)使用的是ssh协议, 并非git协议



## 遇到的问题

### 生成ssh key

> 在实际使用中,有时需要使用多套公钥/私钥对,ssh-kegen加选项`-f`指定不同应用场景的私钥/公钥

```shell
$ ssh-keygen -t rsa -b 4096 -C "15519900807@qq.com"  # 默认生成id_rsa/id_rsa.pub
$ ssh-keygen -t rsa -b 4096 -C "15519900807@qq.com" -f ~/.ssh/vdiscovery
```



> 在实际使用中，有时需要使用多套公钥/私钥对

### git使用https协议遇到的问题

> ping git.vdiscovery.cn 指向49.4.12.132

```shell
$ git clone https://49.4.12.132/WShiBin/FactoryTest.git # error
$ git clone https://git.vdiscovery.cn/WShiBin/FactoryTest 
```





