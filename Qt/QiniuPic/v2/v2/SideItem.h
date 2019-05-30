#pragma once
#include <qwidget.h>
class SideItem :
	public QWidget
{
	Q_OBJECT
public:
	SideItem(QString icon, QString title, QWidget *parent = nullptr);
	~SideItem();
	bool selected();
	void setSelected(bool flag);
	QString title();
	void setTitle(QString title);
signals:
	void click();
protected:
	void paintEvent(QPaintEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
private:
	QString m_icon;
	QString m_title;
	int m_leftPadding;
	int m_rightPadding;
	int m_iconSize;
	int m_rightSideBarWidth;
	bool m_selected;


private:
	void paintIcon(QPainter& painter);
	void paintTitle(QPainter& painter);
	void paintRightSideBar(QPainter& painter);
};

