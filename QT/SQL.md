文档:https://doc.qt.io/qt-5/qtsql-index.html

| Class                                                        | description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [QSql](https://doc.qt.io/qt-5/qsql.html)                     | Contains miscellaneous identifiers used throughout the Qt SQL module |
| [QSqlDatabase](https://doc.qt.io/qt-5/qsqldatabase.html)     | Handles a connection to a database                           |
| [QSqlDriver](https://doc.qt.io/qt-5/qsqldriver.html)         | Abstract base class for accessing specific SQL databases     |
| [QSqlDriverCreator](https://doc.qt.io/qt-5/qsqldrivercreator.html) | Template class that provides a SQL driver factory for a specific driver type |
| [QSqlDriverCreatorBase](https://doc.qt.io/qt-5/qsqldrivercreatorbase.html) | The base class for SQL driver factories                      |
| [QSqlError](https://doc.qt.io/qt-5/qsqlerror.html)           | SQL database error information                               |
| [QSqlField](https://doc.qt.io/qt-5/qsqlfield.html)           | Manipulates the fields in SQL database tables and views      |
| [QSqlIndex](https://doc.qt.io/qt-5/qsqlindex.html)           | Functions to manipulate and describe database indexes        |
| [QSqlQuery](https://doc.qt.io/qt-5/qsqlquery.html)           | Means of executing and manipulating SQL statements           |
| [QSqlQueryModel](https://doc.qt.io/qt-5/qsqlquerymodel.html) | Read-only data model for SQL result sets                     |
| [QSqlRecord](https://doc.qt.io/qt-5/qsqlrecord.html)         | Encapsulates a database record                               |
| [QSqlRelationalTableModel](https://doc.qt.io/qt-5/qsqlrelationaltablemodel.html) | Editable data model for a single database table, with foreign key support |
| [QSqlResult](https://doc.qt.io/qt-5/qsqlresult.html)         | Abstract interface for accessing data from specific SQL databases |
| [QSqlTableModel](https://doc.qt.io/qt-5/qsqltablemodel.html) | Editable data model for a single database table              |



在Qt中加入sql module

```shell
QT += sql
```



在Qt中使用sql有两个方式:

* sql方式:使用sql语句和相关API去CRUD
* API方式:使用[QSqlTableModel](https://doc.qt.io/qt-5/qsqltablemodel.html) 类去CRUD



## SQL模块层次结构

**驱动层Driver Layer**

> 实现了特定数据库与sql如接口的底层桥接,相关类: [QSqlDriver](https://doc.qt.io/qt-5/qsqldriver.html), [QSqlDriverCreator](https://doc.qt.io/qt-5/qsqldrivercreator.html), [QSqlDriverCreatorBase](https://doc.qt.io/qt-5/qsqldrivercreatorbase.html), [QSqlDriverPlugin](https://doc.qt.io/qt-5/qsqldriverplugin.html), and [QSqlResult](https://doc.qt.io/qt-5/qsqlresult.html).

**SQL接口层SQL API Layer**

> 使用这些类去访问数据库,使用 [QSqlDatabase](https://doc.qt.io/qt-5/qsqldatabase.html)用来去连接数据库,[QSqlQuery](https://doc.qt.io/qt-5/qsqlquery.html)用来和数据库进行交互操作,还有其它支持的类: [QSqlError](https://doc.qt.io/qt-5/qsqlerror.html), [QSqlField](https://doc.qt.io/qt-5/qsqlfield.html), [QSqlIndex](https://doc.qt.io/qt-5/qsqlindex.html), and [QSqlRecord](https://doc.qt.io/qt-5/qsqlrecord.html).

**用户接口层User Interface Layer**

> 提供从数据库到用于数据表示的窗休的映射,相关类有[QSqlQueryModel](https://doc.qt.io/qt-5/qsqlquerymodel.html), [QSqlTableModel](https://doc.qt.io/qt-5/qsqltablemodel.html), and [QSqlRelationalTableModel](https://doc.qt.io/qt-5/qsqlrelationaltablemodel.html)



### QSQLITE SQLite version 3 Data Types

https://doc.qt.io/qt-5/sql-types.html

| QSQLITE [SQLite](https://doc.qt.io/qt-5/qtsql-attribution-sqlite.html#sqlite) version 3 data type | SQL type description                                         | Recommended input (C++ or Qt data type)                      |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| NULL                                                         | NULL value.                                                  | NULL                                                         |
| INTEGER                                                      | Signed integer, stored in 8, 16, 24, 32, 48, or 64-bits depending on the magnitude of the value. | typedef qint8/16/32/64                                       |
| REAL                                                         | 64-bit floating point value.                                 | By default mapping to [QString](https://doc.qt.io/qt-5/qstring.html) |
| TEXT                                                         | Character string (UTF-8, UTF-16BE or UTF-16-LE).             | Mapped to [QString](https://doc.qt.io/qt-5/qstring.html)     |
| CLOB                                                         | Character large string object                                | Mapped to [QString](https://doc.qt.io/qt-5/qstring.html)     |
| BLOB                                                         | The value is a BLOB of data, stored exactly as it was input. | Mapped to [QByteArray](https://doc.qt.io/qt-5/qbytearray.html) |



### 连接数据库

https://doc.qt.io/qt-5/qsqldatabase.html

```c++
    qDebug() << QSqlDatabase::drivers();  // 打印安装的Qt支持的数据库驱动

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");  // 通过标记来使用哪一种数据库
    db.setDatabaseName(QDir::home().absolutePath() + QDir::separator() + "FactoryTest/Datas/Databases/database.db");  // ":memory:"创建内存数据库
    db.setHostName("host_name");
    db.setUserName("user_name");
    db.setPassword("passwd");

    if (!db.open()) {
        qDebug() << db.lastError();
    }

    // show all tables in databases;
    qDebug() << db.tables();
```

**设置连接数据库时的选项参数**

| [SQLite](https://doc.qt.io/qt-5/qtsql-attribution-sqlite.html#sqlite)支持的Option | Details        |
| ------------------------------------------------------------ | -------------- |
| QSQLITE_BUSY_TIMEOUT                                         | 超时时间       |
| QSQLITE_OPEN_READONLY                                        | 只读模式       |
| QSQLITE_OPEN_URI                                             | open url       |
| QSQLITE_ENABLE_SHARED_CACHE                                  | 开启共享cache  |
| QSQLITE_ENABLE_REGEXP                                        | 开启正则表达式 |

> 格式:一个QString, 用`;`分隔的选项名或是`option=value`的键值对

```c++
...
// ODBC connection
db.setConnectOptions("SQL_ATTR_ACCESS_MODE=SQL_MODE_READ_ONLY;SQL_ATTR_TRACE=SQL_OPT_TRACE_ON"); // set ODBC options
if (!db.open()) {
    db.setConnectOptions(); // don't try to set this option
    ...
}
```



### 创建表

```c++
    QSqlQuery query;
    bool isCreateTableSucc = query.exec(
        "create table automobil (id int primary key, "
        "attribute varchar, "
        "type varchar, "
        "kind varchar, "
        "nation int, "
        "carnumber int, "
        "elevaltor int, "
        "distance int, "
        "oil int, "
        "temperature int )");
    if (isCreateTableSucc) {
        qDebug() << "create table success";
    } else {
        qDebug() << "create table failed" << query.lastError();
    }
```



### 查询数据

```c++
    QSqlQuery query("SELECT country FROM artist");
    while (query.next()) {
        QString country = query.value(0).toString();
        doSomething(country);
    }
```

```c++
    QSqlQuery query("SELECT * FROM artist");
    int fieldNo = query.record().indexOf("country"); // QSqlRecord通过列名获取索引
    while (query.next()) {
        QString country = query.value(fieldNo).toString();
        doSomething(country);
    }
```



### 插入数据

通过`:field_name`来填充数据

```c++
    QSqlQuery query;
    query.prepare("INSERT INTO person (id, forename, surname) "
                  "VALUES (:id, :forename, :surname)");
    query.bindValue(":id", 1001);
    query.bindValue(":forename", "Bart");
    query.bindValue(":surname", "Simpson");
    query.exec();
```

通过数据序列来填充数据

```c++
    QSqlQuery query;
    query.prepare("INSERT INTO person (id, forename, surname) "
                  "VALUES (:id, :forename, :surname)");
    query.bindValue(0, 1001);
    query.bindValue(1, "Bart");
    query.bindValue(2, "Simpson");
    query.exec();
```

通过`?`号加序列来填充数据

```c++
    QSqlQuery query;
    query.prepare("INSERT INTO person (id, forename, surname) "
                  "VALUES (?, ?, ?)");
    query.bindValue(0, 1001);
    query.bindValue(1, "Bart");
    query.bindValue(2, "Simpson");
    query.exec();
```

通过addBindValue按顺序添加来填充数据

```c++
    QSqlQuery query;
    query.prepare("INSERT INTO person (id, forename, surname) "
                  "VALUES (?, ?, ?)");
    query.addBindValue(1001);
    query.addBindValue("Bart");
    query.addBindValue("Simpson");
    query.exec();
```

```c++
    QSqlQuery query;
    query.prepare("CALL AsciiToInt(?, ?)");
    query.bindValue(0, "A");
    query.bindValue(1, 0, QSql::Out);
    query.exec();
    int i = query.boundValue(1).toInt(); // i is 65
```

### 更新数据

```c++
    QSqlQuery query;
    query.prepare(QString("update automobil set attribute=?,type=?,"
                          "kind=?,"
                          "nation=?,"
                          "carnumber=?,"
                          "elevaltor=?,"
                          "distance=?,"
                          "oil=?,"
                          "temperature=? where id = %1"));
    query.bindValue(0, "silun");
    query.bindValue(2, "jiaoche");
    query.bindValue(3, "fukang");
    query.bindValue(4, rand() % 100);
    query.bindValue(5, rand() % 10000);
    query.bindValue(6, rand() % 300);
    query.bindValue(7, rand() % 200000);
    query.bindValue(8, rand() % 52);
    query.bindValue(9, rand() % 100);
    if (!query.exec()) {
        QSqlError error = query.lastError();
        qDebug() << QObject::tr("insert %1, err: %2").arg(i).arg(error.driverText());
    }
```

### 删除数据

```c++
    QSqlQuery query;
    bool succ = query.exec("delete from automobil where id = 15");
    if (!succ) {
        qDebug() << "delete err:" << query.lastError();
    }
```