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
