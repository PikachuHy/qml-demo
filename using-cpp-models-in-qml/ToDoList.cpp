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
