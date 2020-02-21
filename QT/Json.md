## 文档:

https://doc-snapshots.qt.io/qt5-5.9/json.html

| Class                                                        | descriptions                                                 |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [QJsonArray](https://doc-snapshots.qt.io/qt5-5.9/qjsonarray.html) | Encapsulates a JSON array                                    |
| [QJsonDocument](https://doc-snapshots.qt.io/qt5-5.9/qjsondocument.html) | Way to read and write JSON documents                         |
| [QJsonParseError](https://doc-snapshots.qt.io/qt5-5.9/qjsonparseerror.html) | Used to report errors during JSON parsing                    |
| [QJsonObject](https://doc-snapshots.qt.io/qt5-5.9/qjsonobject.html) | Encapsulates a JSON object                                   |
| [QJsonObject::const_iterator](https://doc-snapshots.qt.io/qt5-5.9/qjsonobject-const-iterator.html) | QJsonObject::const_iterator class provides an STL-style const iterator for QJsonObject |
| [QJsonObject::iterator](https://doc-snapshots.qt.io/qt5-5.9/qjsonobject-iterator.html) | QJsonObject::iterator class provides an STL-style non-const iterator for QJsonObject |
| [QJsonValue](https://doc-snapshots.qt.io/qt5-5.9/qjsonvalue.html) | Encapsulates a value in JSON                                 |

## 相关Json核心类

* QJsonValue,QJsonObject,QJsonArray:是Json元素的基本单位

* QJsonDocument:用来读/写Json

* QJsonParseError:Json解析中的出错信息相关类

* QJsonObject::iterator,QJsonObject::const_iterator:Json迭代器, 用于去迭代Json中的元素



## QJsonObject:

```c++
// init
QJsonObject jsonObject
{
    {"key1", 1},
    {"key2", 6.6},
    {"key3", "Hello world"},
    {"array", QJsonArray({1, 2, 3})}
};

// add data
QJsonObject jsonObject;
jsonObject["key1"] = 1;
jsonObject["key2"] = 6.6;
jsonObject.insert("key3", "Hello world");
jsonObject["array"] = QJsonArray({1, 2, 3}); 

// convert between QJsonObject and QVariantMap
QJsonObject fromVariantMap(const QVariantMap &map)
QVariantMap QJsonObject::toVariantMap() const
```

### QJsonArray:

```c++
// init
QJsonArray jsonArray = { 1, 6.6, QString("Hello world") };

// add data
QJsonArray jsonArray;
jsonArray.append(1);
jsonArray.append(6.6);
jsonArray.insert(2, "Hello world");


QJsonArray fromVariantList(const QVariantList &list)
QVariantList QJsonArray::toVariantList() const
```

### QJsonDocument:

```c++
QJsonDocument(const QJsonObject &object)
QJsonDocument(const QJsonArray &array)

QByteArray toJson() const

bool isNull() const // 如果返回为true则JSON数据解析不正确或为空。
```



## Example:

```json
{
    "FirstName": "John",
    "LastName": "Doe",
    "Age": 43,
    "Address": {
        "Street": "Downing Street 10",
        "City": "London",
        "Country": "Great Britain"
    },
    "Phone numbers": [
        "+44 1234567",
        "+44 2345678"
    ]
}
```



**Json的生成:**

```c++
    QJsonObject* rootObj = new QJsonObject();          // 根节点
    rootObj->insert("FirstName", QJsonValue("John"));  // 用insert方式插入一个element(String)
    (*rootObj)["LastName"] = "Doe";                    // 用[]操作符方式插入一个element
    rootObj->insert("Age", 43);                      // 插入一个value是int的类型的element(int)

    // 准备插入一个Json Obj
    QJsonObject* addressObj = new QJsonObject();
    addressObj->insert("Street", "Downing Street 10");
    addressObj->insert("City", "London");
    addressObj->insert("Country", "Great Britain");
    rootObj->insert("Address", *addressObj);  // 给根节点插入一个Json obj

    // 准备插入一个Json Array
    QJsonArray* phoneNumberArr = new QJsonArray();
    phoneNumberArr->push_back("+44 1234567");                        // stl 兼容的方式插入
    phoneNumberArr->append("+44 2345678");                           //
    phoneNumberArr->insert(phoneNumberArr->begin(), "+44 2345678");  // insert方式加入
    (*phoneNumberArr) += QJsonValue("+44 2345678");         // 用+=操作符的方式来插入一个element
    rootObj->insert("Phone number", *phoneNumberArr);       // 给根节点插入一个Json Array

		// 通过QJsonObject构建QJsonDocument
    QJsonDocument* doc = new QJsonDocument(*rootObj);
    qDebug() << doc->toJson(QJsonDocument::JsonFormat::Indented);
    qDebug() << doc->toJson(QJsonDocument::JsonFormat::Compact);
    qDebug() << doc->toJson();

    // other function
    rootObj->size();               // size
    rootObj->length();             // 同上,源码调用size();
    rootObj->count();              // 同上,源码调用size();
    rootObj->keys();               // key List集k合
    rootObj->isEmpty();            // 是不是穿
    rootObj->find("Address");      // 查找key为Address的节点,返回迭代器
    rootObj->take("Address");      // 取key为Address的节点
    rootObj->remove("Address");    // 移除key为Address的节点
    rootObj->contains("Address");  // 是否包含这个key
```



**解析Json**

```c++
    QJsonParseError err;
    QJsonDocument docStr = QJsonDocument::fromJson(jsonStr, &err);

    // error
    if (err.error != QJsonParseError::ParseError::NoError) {
        qDebug() << "json parse error : " << err.errorString();
        return;
    }

    QJsonObject rootObj;
    QJsonArray rootArr;
    // 判断是Obj还是Array
    if (docStr.isObject()) {
        rootObj = docStr.object();
    } else if (docStr.isArray()) {
        rootArr = docStr.array();
    }

    // qDebug() << docStr.isObject();

    // 直接通过[]操作符去取
    QJsonObject addressObj = docStr["Address"].toObject();  // no error; convert to Obj
    qDebug() << "age : " << docStr["Age"].toInt();          // no error; convert to int
    qDebug() << "age : " << docStr["Age"].toDouble();       // no error; convert to double
    qDebug() << "aaa : " << docStr["aaaaa"].isUndefined();  // true

    // 迭代去攻取element
    rootObj = docStr.object();
    for (auto begin = rootObj.constBegin(); begin != rootObj.constEnd(); begin++) {
        if (begin->isArray()) {
            QJsonArray addressArr = begin->toArray();
            qDebug() << addressArr.size();
            for (int i = 0; i < addressArr.size(); i++) {
                qDebug() << addressArr[i].toString();
            }
        } else if (begin->isDouble()) {
            qDebug() << begin->toDouble();
        } else if (begin->isObject()) {
            qDebug() << begin->toObject();
        } else if (begin->isString()) {
            qDebug() << begin->toString();
        }

        // enum Type {
        //     Null =  0x0,
        //     Bool = 0x1,
        //     Double = 0x2,
        //     String = 0x3,
        //     Array = 0x4,
        //     Object = 0x5,
        //     Undefined = 0x80
        // };
        qDebug() << begin->type(); // 
    }
```



### QJsonDocument::JsonFormat

QJsonDocument::Indented

```json
    {
        "Array": [
            true,
            999,
            "string"
        ],
        "Key": "Value",
        "null": null
    }
```

QJsonDocument::Compact

```
    {"Array":[true,999,"string"],"Key":"Value","null":null}
```

