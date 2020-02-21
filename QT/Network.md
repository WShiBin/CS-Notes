

文档: https://doc.qt.io/qt-5/qtnetwork-index.html



模块引入:

```shell
QT += network
```



## Qt对网络模块的支持

分两类:

一种是提供支持http,ftp协议的high-level相关类

* [QNetworkRequest](https://doc.qt.io/qt-5/qnetworkrequest.html):类用来代表一个网络请求,也用做与请求相关的信息的通用容器,例如请求的头信息和加密信息等.构造QNetwrokRequest时使用的URL决定了请求所使用的协议,目前Http,Ftp和本地文件URL支持上传和下载
* [QNetworkAccessManager](https://doc.qt.io/qt-5/qnetworkaccessmanager.html):协调各种网络操作,当我们构造一个QNetwrokRequest后就要使用QNetworkAccessManager来把它分发出去并使用信号槽来报告进度.QNetworkAccessManager还负责协调使用Cookie来存储客户端上的数据,身份验证请求和代理的使用.每个应用程序或库可以创建一个或多个QNetworkAccessManager实例来处理网络通信
* [QNetworkReply](https://doc.qt.io/qt-5/qnetworkreply.html):表示网络请求的回复.当发出一个网络请求后由QNetworkAccessManager创建QNetworkReply.由于QNetworkReply是QIODevice的子类，因此可以同步或异步处理回复; 即作为阻塞或非阻塞操作。QNetworkReply提供的信号可用于单独监控每个回复,也可以使用QNetworkAccessManager的信号来达到此目的



另一种是提供lower-level网络支持的相关类,能用它去实现POP3, SMTP, and NNTP一样的标准协议,也能用他去实现自定义的协议

* [QAbstractSocket](https://doc.qt.io/qt-5/qabstractsocket.html): 该类提供了所有socket类型所共有的基本函数，是QTcpSocket和QUdpSocket的基类，该类包含了这两个类所共有的成员函数

* [QTcpSocket](https://doc.qt.io/qt-5/qtcpsocket.html):用来建立tcp连接,传输数据流
* [QTcpServer](https://doc.qt.io/qt-5/qtcpserver.html):写Tcp服务



![A TCP Stream](assets/tcpstream.png)

在数据传输之前,必须与远程的host和port建立连接,当建立连接之后,ip和port可以通过 [QTcpSocket::peerAddress](https://doc.qt.io/qt-5/qabstractsocket.html#peerAddress)()和[QTcpSocket::peerPort](https://doc.qt.io/qt-5/qabstractsocket.html#peerPort)()获取,可以随时关闭,关闭之后数据传输也会立马终止

QTcpSocket工作是异步的,发送信号去汇报status的改变和errors,它依靠循环的事件去检查是否有数据发送过来,并且自动刷新发送出去的数据. 你能使用 [QTcpSocket::write](https://doc.qt.io/qt-5/qiodevice.html#write)()去发送数据,使用[QTcpSocket::read](https://doc.qt.io/qt-5/qiodevice.html#read)()去读数据,读和写的数据流是独立的,

也可以使用[QTextStream](https://doc.qt.io/qt-5/qtextstream.html) and [QDataStream](https://doc.qt.io/qt-5/qdatastream.html)去读写数据, 但是在读数据之前要先通过调用[QTcpSocket::bytesAvailable](https://doc.qt.io/qt-5/qabstractsocket.html#bytesAvailable)() 去检查是否有足够的数据可以读.

[QTcpServer](https://doc.qt.io/qt-5/qtcpserver.html):调用[QTcpServer::listen](https://doc.qt.io/qt-5/qtcpserver.html#listen)()去配置server,连接 [QTcpServer::newConnection](https://doc.qt.io/qt-5/qtcpserver.html#newConnection)()信号,当有新的连接过来会收到信号,在连接这个信号的slot里面,调用[QTcpServer::nextPendingConnection](https://doc.qt.io/qt-5/qtcpserver.html#nextPendingConnection)()去同意连接,



QAbstractSocket中socket的状态:

* QAbstractSocket::UnconnectedState:socket初始的状态
* QAbstractSocket::HostLookupState:调用connectToHost之后去找主机
* QAbstractSocket::ConnectingState:如果主机被找到,发射HostFound信号
* QAbstractSocket::ConnectedState:当连接被建立的时候,发射发射connected信号
* QAbstractSocket::BoundState:当这个socket被绑定到一个server地址的端口
* QAbstractSocket::ClosingState:关闭一个连接可以调用disconnectFromHost(),并且发送disconnected信号
* QAbstractSocket::ListeningState:For internal use only.

> 如果再这些阶段出现了错误,发送error信号,同时socket的状态仍然为[ConnectedState](https://link.zhihu.com/?target=http%3A//blog.csdn.net/HandsomeHong/article/details/70479098),然后发射disconnected信号. 
>
> 无论什么时候 QAbstractSocket的状态改变都会发射stateChanged()信号



QTcpServer example:

```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractSocket>
#include <QMessageBox>
#include <QTcpSocket>
#include <QObject>
#include <QHostAddress>
#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // tcp server
    tcpServer = new QTcpServer(this);
    // listen
    if (!tcpServer->listen(QHostAddress::Any, 8080)) {
        QMessageBox::critical(this, tr("server"), tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
        close();
        return;
    }
    // new connection
    connect(tcpServer, &QTcpServer::newConnection, this, &MainWindow::onNewConnection);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onNewConnection() {
    // data
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << fortunes[QRandomGenerator::global()->bounded(fortunes.size())];

    // new client connected
    QTcpSocket* socketClient = tcpServer->nextPendingConnection();
    connect(socketClient, &QAbstractSocket::disconnected, socketClient, &QObject::deleteLater);                                  // disconected
    connect(socketClient, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);                                               // data available
    connect(socketClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));  // error
    connect(
        socketClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));  // stateChanged

    // client name, address, port
    qDebug() << socketClient->peerName().toUtf8();
    qDebug() << socketClient->peerAddress().toString();
    qDebug() << socketClient->peerPort();

    // write data
    socketClient->write(block);
    socketClient->disconnectFromHost();
}

void MainWindow::onReadyRead() {
    for (QTcpSocket* socket : sockets) {
        if (socket->bytesAvailable()) {
            QByteArray content = socket->readAll();  // get data
            socket->write(QByteArray::fromStdString(socket->peerAddress().toString().toStdString() + ": msg "));
        }
    }
}

void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState) {
}

void MainWindow::displayError(QAbstractSocket::SocketError error) {
}
```



### Http get请求下载文件

```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QUrl url("https://dldir1.qq.com/weixin/mac/WeChatMac.dmg");
    QFileInfo info(url.path());
    qDebug() << tr("url: %1, filename: %2").arg(url.path()).arg(info.fileName());
    
    file = new QFile("/Users/ben/Desktop/wechat.dmg");
    if (!file->open(QIODevice::ReadWrite)) {
        qDebug() << "file open err";
        delete file;
        file = nullptr;
        return;
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    reply = manager->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::readyRead, this, &MainWindow::httpReadyRead);
    connect(reply, &QNetworkReply::downloadProgress, this, &MainWindow::updateDataReadProgress);
    connect(reply, &QNetworkReply::finished, this, &MainWindow::httpFinished);
}

void MainWindow::httpReadyRead() {
    qDebug() << "start downloading ...";
    if (file) {
        file->write(reply->readAll());
    }
}

void MainWindow::updateDataReadProgress(qint64 byteRead, qint64 totalBytes) {
    qDebug() << tr("downloading %1").arg(byteRead * 1.0 / totalBytes);
}

void MainWindow::httpFinished() {
    qDebug() << "finish download";
    file->flush();
    file->close();
    reply->deleteLater();
}

MainWindow::~MainWindow() {
    delete ui;
}
```



### http Post表单数据

> Content-Type: application/x-www-form-urlencoded

```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QUrl>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QUrlQuery query;
    query.addQueryItem("username", "shibin");
    query.addQueryItem("age", "18");

    QByteArray postData = query.toString(QUrl::FullyEncoded).toUtf8();

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("http://192.168.1.100:14333/postdata"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    reply = manager->post(request, postData);
    connect(reply, &QNetworkReply::finished, this, &MainWindow::httpReplyFinished);
    qDebug() << "init";
}

void MainWindow::httpReplyFinished() {
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << reply->readAll();
    } else {
        qDebug() << "httpReplyFinished" << reply->error();
    }
}

```



### http multipart上传文件

相关类

* QHttpPart
* QHttpMultiPart

| 常量                            | 值   | 描述                                                         |
| :------------------------------ | :--- | :----------------------------------------------------------- |
| QHttpMultiPart::MixedType       | 0    | 对应于 `"multipart/mixed"` 子类型，意味着 body 部位是相互独立的。如 [RFC 2046](https://www.ietf.org/rfc/rfc2046.txt) 所述。 |
| QHttpMultiPart::RelatedType     | 1    | 对应于 `"multipart/related"` 子类型，意味着 body 部位是相互关联的。如 [RFC 2387](https://www.ietf.org/rfc/rfc2387.txt) 所述。 |
| QHttpMultiPart::FormDataType    | 2    | 对应 `"multipart/form-data"` 子类型，意味着 body 部位包含表单元素。如 [RFC 2388](https://www.ietf.org/rfc/rfc2388.txt) 所述。 |
| QHttpMultiPart::AlternativeType | 3    | 对应 `"multipart/alternative"` 子类型，意味着 body 部位是相同信息的替代表示。如 [RFC 2046](https://www.ietf.org/rfc/rfc2046.txt) 所述。 |