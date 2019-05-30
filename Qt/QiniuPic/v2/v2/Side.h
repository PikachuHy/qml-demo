#pragma once
#include <qwidget.h>
class SideItem;
class Side :
	public QWidget
{
	Q_OBJECT
public:
	Side(QWidget* parent = nullptr);
	~Side();
signals:
	void currentItemChange(QString itemName);
private:
	QList<SideItem*> m_sideItemList;

private:
	void clearSelected();
};

