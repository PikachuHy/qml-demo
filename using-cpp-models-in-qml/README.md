# Using C++ Models in QML

参考视频：[Using C++ Models in QML {tutorial}](https://www.youtube.com/watch?v=9BcAYDlpuT8)

这个视频比较长，40多分钟，内容也比较丰富。

## 主要功能

- 一个简单的待办事项
- 可以增加新的待办事项，也可以删除已经完成的事情

## 源码

### ToDoList.qml

```qml
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import ToDo 1.0
ColumnLayout{
    Frame {
        Layout.fillWidth: true
        ListView{
            id:listView
            implicitWidth: 300
            implicitHeight: 300
            anchors.fill: parent
            clip: true

            model: ToDoModel{
                list:toDoList
            }

            delegate: RowLayout{
                width: listView.width
                CheckBox{
                    checked: model.done
                    onCheckedChanged: model.done = checked
                }
                TextField{
                    Layout.fillWidth: true
                    text: model.description
                    onEditingFinished: model.description = text
                }
            }
        }
    }
    RowLayout{
        Button{
            text:qsTr("Add new item")
            onClicked: toDoList.appendItem()
            Layout.fillWidth: true
        }
        Button{
            text:qsTr("Remove complete items")
            onClicked: toDoList.removeCompletedItem()
            Layout.fillWidth: true
        }
    }
}

```

### main.qml

```qml
import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("To Do List")

    ToDoList{
        anchors.centerIn: parent
    }
}

```

### ToDoList.h

```c++
#ifndef TODOLIST_H
#define TODOLIST_H
#include <QObject>
#include <QVector>
struct ToDoItem{
    bool done;
    QString description;
    bool equals(const ToDoItem& item) const {
        return this->done == item.done && this->description == item.description;
    }
};
class ToDoList : public QObject
{
    Q_OBJECT
public:
    explicit ToDoList(QObject *parent = nullptr);
    QVector<ToDoItem> items() const;
    bool setItemAt(int index, const ToDoItem &item);
signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();
public slots:
    void appendItem();
    void removeCompletedItem();
private:
    QVector<ToDoItem> m_items;
};

#endif // TODOLIST_H

```



### ToDoList.cpp

```c++
#include "ToDoList.h"

ToDoList::ToDoList(QObject *parent) : QObject(parent)
{
    m_items.append({true,"Wash the car"});
    m_items.append({false,"Fix the sink"});
}

QVector<ToDoItem> ToDoList::items() const
{
    return m_items;
}

bool ToDoList::setItemAt(int index, const ToDoItem &item)
{
    if(index < 0 || index >= m_items.size()){
        return false;
    }
    const ToDoItem& oldItem = m_items[index];
    if(oldItem.equals(item)){
        return false;
    }
    m_items[index] = item;
    return true;
}

void ToDoList::appendItem()
{
    emit preItemAppended();
    ToDoItem item;
    item.done = false;
    m_items.append(item);
    emit postItemAppended();
}

void ToDoList::removeCompletedItem()
{
    for(int i=0;i<m_items.size();){
        if(m_items[i].done){
            emit preItemRemoved(i);
            m_items.remove(i);
            emit postItemRemoved();
        }else{
            i++;
        }
    }
}

```

### ToDoModel.h

```c++
#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <QAbstractListModel>
class ToDoList;

class ToDoModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ToDoList *list READ list WRITE setList)
public:
    explicit ToDoModel(QObject *parent = nullptr);
    enum{
        DoneRole = Qt::UserRole,
        DescriptionRole
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    ToDoList* m_list;
    // QAbstractItemModel interface
public:
    virtual QHash<int, QByteArray> roleNames() const override;
    ToDoList *list() const;
    void setList(ToDoList *list);
};

#endif // TODOMODEL_H

```

### ToDoModel.cpp

```c++
#include "ToDoModel.h"
#include "ToDoList.h"
ToDoModel::ToDoModel(QObject *parent)
    : QAbstractListModel(parent),
      m_list(nullptr)
{
}

int ToDoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || m_list == nullptr)
        return 0;

    return m_list->items().size();
}

QVariant ToDoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || m_list==nullptr)
        return QVariant();
    auto item = m_list->items().at(index.row());
    switch (role) {
    case DoneRole:{
        return QVariant(item.done);
    }
    case DescriptionRole:{
        return QVariant(item.description);
    }
    }
    return QVariant();
}

bool ToDoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(m_list == nullptr){
        return false;
    }
    auto item = m_list->items().at(index.row());

    switch (role) {
    case DoneRole:{
        item.done = value.toBool();
        break;
    }
    case DescriptionRole:{
        item.description = value.toString();
        break;
    }
    }
    if (m_list->setItemAt(index.row(),item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ToDoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

ToDoList *ToDoModel::list() const
{
    return m_list;
}

void ToDoModel::setList(ToDoList *list)
{
    beginResetModel();
    if(m_list != nullptr){
        m_list->disconnect(this);
    }
    m_list = list;
    if(m_list!=nullptr){
        connect(m_list,&ToDoList::preItemAppended,[=](){
            const int index = m_list->items().size();
            beginInsertRows(QModelIndex(),index,index);
        });
        connect(m_list,&ToDoList::postItemAppended,[=](){
            endInsertRows();
        });
        connect(m_list,&ToDoList::preItemRemoved,[=](int index){
            beginRemoveRows(QModelIndex(),index,index);
        });
        connect(m_list,&ToDoList::postItemRemoved,[=](){
            endRemoveRows();
        });
    }
    endResetModel();
}

QHash<int, QByteArray> ToDoModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DoneRole] = "done";
    names[DescriptionRole] = "description";
    return names;
}

```

### main.cpp

```c++
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ToDoModel.h"
#include "ToDoList.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<ToDoModel>("ToDo",1,0,"ToDoModel");
    qmlRegisterUncreatableType<ToDoList>("ToDo",1,0,"ToDoList",
        QStringLiteral("ToDoList should not be created in QMl"));
    ToDoList toDoList;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("toDoList",&toDoList);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

```



## 截图

### 最后的运行效果

![image](http://oh913j3dl.bkt.clouddn.com//qml/using_cpp_models_in_qml/0.gif)

### 自己做的时候留下的部分截图

![image](http://oh913j3dl.bkt.clouddn.com//qml/using_cpp_models_in_qml/0.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/using_cpp_models_in_qml/1.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/using_cpp_models_in_qml/2.png)

## 思考与总结

虽然是一个简单的ToDo-List，却是目前做过的最难的一个qml Demo，牵涉到的Qt相关的知识非常多。

- 在Layout中使用fillWidth: true使控件填充满

不同于css中设置display的方式，qml的layout采用这种方式使得控件填充满layout，同时还可以实现对其，如这个例子中的两个Button的宽度和ListView宽度一样

- Model-View-Delegate的使用

在我的使用经历中，Qt的这个模式是一个很难的点，我看了很多视频教程，也尝试着自己去写基于这个模式的Demo，往往是失败告终。在这次的ToDo-List中，视频非常详细的介绍了从简单的model，一步一步到复杂的model，如何编写，如何使用。我认为是这个视频对我最大的帮助之一。

- 使用信号槽实现的双向绑定

我开始只能把model的数据展示在listview上，如果我去勾选框或者去编辑，model是感应不到的，是不会改变的。后来是onCheckedChanged和onEditingFinished两个槽函数，把改变的数据赋给模型，才完成这个双向绑定。

- 在QML是用C++编写的models

本来这是这个视频的重点，结果发现，在最后使用的时候，非常简单，两个注册函数就搞定了。反倒是把大量的精力花在了如何编写model上。在编辑器中，qml对于C++槽函数的智能提示也做得非常的好，很方便。