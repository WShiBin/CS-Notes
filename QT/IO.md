

> Qt中IO相关类
>
> 文档:https://doc.qt.io/qt-5/io.html

| Class                                                        | description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [QBuffer](https://doc.qt.io/qt-5/qbuffer.html)               | QIODevice interface for a QByteArray                         |
| [QDataStream](https://doc.qt.io/qt-5/qdatastream.html)       | Serialization of binary data to a QIODevice                  |
| [QDir](https://doc.qt.io/qt-5/qdir.html)                     | Access to directory structures and their contents            |
| [QFile](https://doc.qt.io/qt-5/qfile.html)                   | Interface for reading from and writing to files              |
| [QFileDevice](https://doc.qt.io/qt-5/qfiledevice.html)       | Interface for reading from and writing to open files         |
| [QFileInfo](https://doc.qt.io/qt-5/qfileinfo.html)           | System-independent file information                          |
| [QFileSystemWatcher](https://doc.qt.io/qt-5/qfilesystemwatcher.html) | Interface for monitoring files and directories for modifications |
| [QIODevice](https://doc.qt.io/qt-5/qiodevice.html)           | The base interface class of all I/O devices in Qt            |
| [QImageReader](https://doc.qt.io/qt-5/qimagereader.html)     | Format independent interface for reading images from files or other devices |
| [QImageWriter](https://doc.qt.io/qt-5/qimagewriter.html)     | Format independent interface for writing images to files or other devices |
| [QProcess](https://doc.qt.io/qt-5/qprocess.html)             | Used to start external programs and to communicate with them |
| [QProcessEnvironment](https://doc.qt.io/qt-5/qprocessenvironment.html) | Holds the environment variables that can be passed to a program |
| [QResource](https://doc.qt.io/qt-5/qresource.html)           | Interface for reading directly from resources                |
| [QSaveFile](https://doc.qt.io/qt-5/qsavefile.html)           | Interface for safely writing to files                        |
| [QSettings](https://doc.qt.io/qt-5/qsettings.html)           | Persistent platform-independent application settings         |
| [QSocketNotifier](https://doc.qt.io/qt-5/qsocketnotifier.html) | Support for monitoring activity on a file descriptor         |
| [QStorageInfo](https://doc.qt.io/qt-5/qstorageinfo.html)     | Provides information about currently mounted storage and drives |
| [QTemporaryDir](https://doc.qt.io/qt-5/qtemporarydir.html)   | Creates a unique directory for temporary use                 |
| [QTemporaryFile](https://doc.qt.io/qt-5/qtemporaryfile.html) | I/O device that operates on temporary files                  |
| [QTextDocumentWriter](https://doc.qt.io/qt-5/qtextdocumentwriter.html) | Format-independent interface for writing a QTextDocument to files or other devices |
| [QTextStream](https://doc.qt.io/qt-5/qtextstream.html)       | Convenient interface for reading and writing text            |
| [QUrl](https://doc.qt.io/qt-5/qurl.html)                     | Convenient interface for working with URLs                   |
| [QUrlQuery](https://doc.qt.io/qt-5/qurlquery.html)           | Way to manipulate a key-value pairs in a URL's query         |



## QFile

> 用来read和write文本或二进行文件. 也可以使用更方便的[QTextStream](https://doc.qt.io/qt-5/qtextstream.html) or [QDataStream](https://doc.qt.io/qt-5/qdatastream.html)
>
> 一般在创建的时候传递文件名,也可以通过setFileName()去设置,文件分割符统一使用`/`,与系统无关
>
> 高级的文件相关操作可以查看[QFileInfo](https://doc.qt.io/qt-5/qfileinfo.html) 和 [QDir](https://doc.qt.io/qt-5/qdir.html).

文件权限

* NotOpen

* ReadOnly

* WriteOnly

* ReadWrite

* Append

* Truncate

* Text

* Unbuffered

* NewOnly

* ExistingOnly

相关API

* exists:文件是否存在
* remove:删除文件
* open:打开文件
* close:关闭文件
* flush:flushed文件
* read:读文件
* readLine:读文件中的一行
* write:写入到文件
* writeLine:写入一行到文件
* getChar:从文件中获取一个字符
* putChar:写一个字符到文件中去
* size:文件大小
* pos:(position)在读写过程中,指针的位置
* seek:移动文件读写的指针
* atEnd:是否到了文件结尾

#### Example:读一个文本文件

```c++
    QFile file("in.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        process_line(line);
    }
```

#### Example:目录,相对路径

```c++
QFile file;
QDir::setCurrent("/tmp");
file.setFileName("readme.txt");
QDir::setCurrent("/home");
file.open(QIODevice::ReadOnly);      // opens "/home/readme.txt" under Unix
```



## QTextStream

> 方便的去读写文本文件

```c++
    // read
		QFile file("in.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        process_line(line);
    }

		// write
    QFile file("out.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << "The magic number is: " << 49 << "\n";

		// readline
    QFile file("/proc/modules");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
        process_line(line);
        line = in.readLine();
    }
```



## QDataStream

> 提供了二进制数据的 [QIODevice](https://doc.qt.io/qt-5/qiodevice.html)

```c++
// write
QFile file("file.dat");
file.open(QIODevice::WriteOnly);
QDataStream out(&file);   // we will serialize the data into the file
out << QString("the answer is");   // serialize a string
out << (qint32)42;        // serialize an integer

// read
QFile file("file.dat");
file.open(QIODevice::ReadOnly);
QDataStream in(&file);    // read the data serialized from the file
QString str;
qint32 a;
in >> str >> a;           // extract "the answer is" and 42
```



> If you are producing a new binary data format, such as a file format for documents created by your application, you could use a QDataStream to write the data in a portable format. Typically, you would write a brief header containing a magic string and a version number to give yourself room for future expansion. For example:

write

```c++
QFile file("file.xxx");
file.open(QIODevice::WriteOnly);
QDataStream out(&file);

// Write a header with a "magic number" and a version
out << (quint32)0xA0B0C0D0;
out << (qint32)123;

out.setVersion(QDataStream::Qt_4_0);

// Write the data
out << lots_of_interesting_data;
```

read

```c++
QFile file("file.xxx");
file.open(QIODevice::ReadOnly);
QDataStream in(&file);

// Read and check the header
quint32 magic;
in >> magic;
if (magic != 0xA0B0C0D0)
    return XXX_BAD_FILE_FORMAT;

// Read the version
qint32 version;
in >> version;
if (version < 100)
    return XXX_BAD_FILE_TOO_OLD;
if (version > 123)
    return XXX_BAD_FILE_TOO_NEW;

if (version <= 110)
    in.setVersion(QDataStream::Qt_3_2);
else
    in.setVersion(QDataStream::Qt_4_0);

// Read the data
in >> lots_of_interesting_data;
if (version >= 120)
    in >> data_new_in_XXX_version_1_2;
in >> other_interesting_data;
```

## QDir

```c++
QDir directory("Documents/Letters");
QString path = directory.filePath("contents.txt");
QString absolutePath = directory.absoluteFilePath("contents.txt");

// Check if a directory exists:
QDir dir("example");
if (!dir.exists())
    qWarning("Cannot find the example directory");

// Traversing directories and reading a file:
QDir dir = QDir::root();                 // "/"
if (!dir.cd("tmp")) {                    // "/tmp"
    qWarning("Cannot find the \"/tmp\" directory");
} else {
    QFile file(dir.filePath("ex1.txt")); // "/tmp/ex1.txt"
    if (!file.open(QIODevice::ReadWrite))
        qWarning("Cannot create the file %s", file.name());
}
```

Example:显示一个目录下所有有文件,按文件大小从小到大排序

```c++
#include <QDir>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    std::cout << "     Bytes Filename" << std::endl;
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                .arg(fileInfo.fileName()));
        std::cout << std::endl;
    }
    return 0;
}
```

## QFileInfo

> 提供一些获取高级文件信息的方法

```c++
QFileInfo info1("/home/bob/bin/untabify");
info1.isSymLink();          // returns true
info1.absoluteFilePath();   // returns "/home/bob/bin/untabify"
info1.size();               // returns 56201
info1.symLinkTarget();      // returns "/opt/pretty++/bin/untabify"
```

## QBuffer

> 内存文件

```c++
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);
    buffer.write("msg\n");
    buffer.write("msg\n");
    buffer.write("msg\n");
    buffer.write("msg\n");
    buffer.seek(0);
    char tmp;
    buffer.getChar(&tmp);
    qDebug() << tmp;
    qDebug() << buffer.getChar(&tmp);
    qDebug() << buffer.getChar(&tmp);

    // write
    buffer.seek(0);
    QTextStream out(&buffer);
    //    out.writeBytes("xixi", 4);
    QString str;
    out >> str;
    out << "hehe";
    qDebug() << str;
    qDebug() << "--------------";

    // read
    buffer.seek(0);
    QByteArray byteArr;
    QTextStream in(&buffer);
    while (!in.atEnd()) {
        qDebug() << in.readLine();
    }

    buffer.close()
```

Example:把数据保存到图片文件

```c++
    QBuffer buffer;
    QDataStream in(&buffer);
    in << "pic data";  // write data into buffer
    QPixmap pixmap("/Users/ben/watcher/aaa.png");
    pixmap.save(&buffer, "PNG");
    buffer.close();
    qDebug() << pixmap.size();
```



## QFileSystemWatcher

> 用来监控文件或目录的修改,The [fileChanged](https://doc.qt.io/qt-5/qfilesystemwatcher.html#fileChanged)() signal is emitted when a file has been modified, renamed or removed from disk. Similarly, the [directoryChanged](https://doc.qt.io/qt-5/qfilesystemwatcher.html#directoryChanged)() signal is emitted when a directory or its contents is modified or removed.

```c++
void MainWindow::qfileSystemWatcherTest() {
    QFileSystemWatcher watcher(this);
    watcher.addPath("/Users/ben/watcher");
    connect(&watcher, &QFileSystemWatcher::fileChanged, this, &MainWindow::onFileChanged);
    connect(&watcher, &QFileSystemWatcher::directoryChanged, this, &MainWindow::onDirectoryChanged);
    qDebug() << watcher.files();
    qDebug() << watcher.directories();
}

void MainWindow::onFileChanged(const QString& path) {
    qDebug() << tr("onFileChanged path: %1").arg(path);
}

void MainWindow::onDirectoryChanged(const QString& path) {
    qDebug() << tr("onDirectoryChanged path: %1").arg(path);
}
```

