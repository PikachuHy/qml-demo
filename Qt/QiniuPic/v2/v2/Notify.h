#pragma once
#include <qobject.h>
class Notify :
	public QObject
{
	Q_OBJECT
public:
	Notify(QObject* parent = nullptr);
	~Notify();
	void sendNotify(QString filepath, QString url);
};

