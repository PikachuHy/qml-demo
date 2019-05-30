#include "stdafx.h"
#include "SideItem.h"
#include "Util.h"


SideItem::SideItem(QString icon, QString title, QWidget* parent)
	: QWidget(parent), m_icon(icon), m_title(title)
{
	m_leftPadding = 10;
	m_rightPadding = 5;
	m_iconSize = 64;
	m_rightSideBarWidth = 5;
	m_selected = false;
	setMinimumSize(225, 80);
	setMaximumSize(250, 100);
	resize(230, 90);
}

SideItem::~SideItem()
{
}

bool SideItem::selected()
{
	return m_selected;
}

void SideItem::setSelected(bool flag)
{
	m_selected = flag;
}

QString SideItem::title()
{
	return m_title;
}

void SideItem::setTitle(QString title)
{
	m_title = title;
}

void SideItem::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	paintIcon(painter);
	paintTitle(painter);
	paintRightSideBar(painter);
}

void SideItem::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);
}

void SideItem::mouseDoubleClickEvent(QMouseEvent* event)
{
	QWidget::mouseDoubleClickEvent(event);

}

void SideItem::mouseMoveEvent(QMouseEvent* event)
{
	QWidget::mouseMoveEvent(event);
}

void SideItem::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		// 点击事件
		emit click();
	}
	QWidget::mouseReleaseEvent(event);
}


void SideItem::paintIcon(QPainter& painter)
{
	// 绘制图标
	QString iconPath;
	if (m_selected)
	{
		iconPath = Util::getQrcIconPath(m_icon, Util::activeColor, Util::defaultIconSize);
	} else
	{
		iconPath = Util::getQrcIconPath(m_icon, Util::inactiveColor, Util::defaultIconSize);
	}
	painter.drawPixmap(
		QRect(
			m_leftPadding,
			(size().height() - m_iconSize) / 2,
			m_iconSize,
			m_iconSize),
		QPixmap(iconPath)
		);
}

void SideItem::paintTitle(QPainter& painter)
{
	painter.save();
	// 绘制标签
	painter.setFont(QFont(QString::fromLatin1("微软雅黑"), 16));
	
	int x = m_leftPadding + m_iconSize + 10;
	int y = (size().height() - m_iconSize) / 2;
	int width = this->width() - x -
		(m_rightPadding + m_rightSideBarWidth + 10);
	painter.drawText(
		QRect(x, y, width, m_iconSize),
		Qt::AlignLeft | Qt::AlignVCenter ,
		m_title
	);
	painter.restore();
}

void SideItem::paintRightSideBar(QPainter& painter)
{
	painter.save();
	// 如果是选中状态，绘制右边的侧边条
	if (m_selected)
	{
		painter.setBrush(QColor(18, 150, 219));
		painter.setPen(QPen(QColor(18, 150, 219), 1));
		painter.drawRect(
			size().width() - m_rightPadding - m_rightSideBarWidth,
			(size().height() - m_iconSize) / 2,
			m_rightSideBarWidth,
			m_iconSize
		);
	}
	painter.restore();
}
	