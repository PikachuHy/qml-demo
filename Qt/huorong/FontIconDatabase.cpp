#include "FontIconDatabase.h"
#include <QFile>
#include <QDebug>
#include <QMutex>

static QMap<QString, QString> urlMap;
static QMap<QString, QMap<QString,QString>> fontNameMap;

void FontIconDatabase::init()
{
    urlMap.insert("Material Icons",":/db/codepoints.txt");

    urlMap.insert("Font Awesome 5 Free",":/db/FontAwesome5FreeIcon_codepoints.txt");
    QMapIterator<QString, QString> i(urlMap);
    while (i.hasNext()) {
        i.next();
        qDebug()<<"handle"<<i.key() <<i.value();
        QString filename = i.value();
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)){
            qDebug()<<"Read file"<<filename<<"fail";
            continue;
        }
        QString text = file.readAll();
        auto nameMap = generateNameMap(text);
        fontNameMap.insert(i.key(),nameMap);
    }

}

FontIconDatabase::FontIconDatabase(QObject *parent):QObject (parent)
{

}

QString FontIconDatabase::convertNameToText(QString name, QString fontFamily)
{
    auto nameMap = fontNameMap[fontFamily];
    auto text = nameMap[name];
    return text;
}


QMap<QString, QString> FontIconDatabase::generateNameMap(QString text)
{
    QMap<QString, QString> nameMap;
    auto arr = text.split("\n");
    for(auto it:arr){
        auto items = it.split(" ");
        nameMap.insert(items[0].trimmed(),items[1].trimmed());
    }
    return nameMap;
}
