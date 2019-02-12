#ifndef FONTICONDATABASE_H
#define FONTICONDATABASE_H

#include <QObject>
#include <QMap>
class FontIconDatabase : public QObject
{
    Q_OBJECT
public:
    explicit FontIconDatabase(QObject *parent = nullptr);

signals:

public:
    Q_INVOKABLE static QString convertNameToText(QString name, QString fontFamily);
public:
    static void init();
private:
    static QMap<QString, QString> generateNameMap(QString text);
};

#endif // FONTICONDATABASE_H
