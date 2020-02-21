



## Qt官网

https://www.qt.io/

## Qt Download

http://download.qt.io/archive/qt/  5.12 LTS长期支持版本

> Notes: 安装完之后注意查看Qt版本,(菜单栏:Help>About Qt Creator),官网有bug,下载文件和版本对应不上
>
> * 下载的版本是5.12.5, 安装完之后显示是5.13.1版本
>
> * 然后下载5.12.4, 安装完之后显示是5.12.3版本

## Qt Install

https://wiki.qt.io/Install_Qt_5_on_Ubuntu

```shell
# 修改文件权限
chmod +x qt-opensource-linux-x64-5.7.0.run
# 开始安装
./qt-opensource-linux-x64-5.7.0.run	
```

**Install g++**

```shell
sudo apt-get install build-essential
```

**Install generic font configuration library - runtime**字体配置

```shell
sudo apt-get install libfontconfig1
```

**Configure a compiler**配置编译器

> 如果没有自动检测到编译器,需要配置
>
> Launch **Qt Creator**. Go to **Tools > Options**. Click **Build & Run** and select tab **Kit**. 

**Install OpenGL libraries**

```shell
sudo apt-get install mesa-common-dev
```

**创建Qt启动快捷方式**(可选)

在 `桌面`目录下创建名为Qt-Creator.desktop的文件, Exec/Icon参数修改成自己安装的目录

```shell
[Desktop Entry]
Version=1.0
Encoding=UTF-8
Type=Application
Name=QtCreator
Comment=QtCreator
NoDsiplay=true
Exec=/home/shibin/Qt5.12.5/Tools/QtCreator/bin/qtcreator %f
Icon=/home/shibin/Qt5.12.5/5.12.5/Src/qtdoc/doc/images/landing/icon_QtCreator_78x78px.png
Name[en_US]=Qt-Creator
```

```shell
sudo chmod +x Qt-Creator.desktop
```

## Qt uninstall卸载

在Qt的安装目录下有个MaintenanceTool文件, 执行即可

```shell
./Qt5.12.5/MaintenanceTool
```

## Qt Examples And Tutorials

https://doc.qt.io/qt-5/qtexamplesandtutorials.html

all examples : https://doc.qt.io/qt-5/qtexamples.html

## Qt Licensing授权

https://doc.qt.io/qt-5/licensing.html

* 商业授权:Qt licensed under *commercial* licenses
* LGPL授权协议:Qt licensed under the [GNU Lesser General Public License (LGPL)](https://doc.qt.io/qt-5/lgpl.html) version 3
* 特殊协议:Qt代码库引入第三方库, 这些第三方库有自己的授权协议:https://doc.qt.io/qt-5/licenses-used-in-qt.html

#### LGPL 

LGPL是GNU Lesser General Public License (GNU 宽通用公共许可证)的缩写

* 允许商业软件通过类库引用(link)方式使用LGPL类库而不需要开源商业软件的代码。采用LGPL协议的开源代码可以被商业软件作为类库引用并发布和销售
* 如果修改LGPL协议的代码或者衍生, 则所有修改的代码, 涉及修改部分的额外代码和衍生的代码都必须采用LGPL协议

> 总结: 不改人家源码, 只是使用, 啥事没有

#### Qt安装时会有授权协议显示:

![image-20191106144948795](assets/image-20191106144948795.png)



## Qt平台支持

https://doc.qt.io/qtcreator/creator-os-supported-platforms.html