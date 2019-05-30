#include "stdafx.h"
#include "UploadArea.h"
#include "Util.h"
#include "QiniuUploadManager.h"

UploadArea::UploadArea(QWidget *parent) : QWidget(parent)
{
	m_padding = 20;
	m_radius = 25;
	m_hover = false;
	setMouseTracking(true);
	setMinimumSize(400, 300);
	setAcceptDrops(true);
}


UploadArea::~UploadArea()
{
}

void UploadArea::mousePressEvent(QMouseEvent* event)
{
}

void UploadArea::mouseReleaseEvent(QMouseEvent* event)
{
}

void UploadArea::mouseDoubleClickEvent(QMouseEvent* event)
{
	auto pos = event->pos();
	// 如果点在矩形区域内
	auto rect = calBorderRect();
	if (Util::isPointInRect(pos, rect))
	{
		emit click();
	}

}

void UploadArea::mouseMoveEvent(QMouseEvent* event)
{
	auto pos = event->pos();
	// 如果点在矩形区域内
	auto rect = calBorderRect();
	if (Util::isPointInRect(pos, rect))
	{
		if (m_hover != true)
		{
			m_hover = true;
			repaint();
		}
	} else
	{
		if (m_hover != false)
		{
			m_hover = false;
			repaint();
		}
	}
}

QRect UploadArea::calBorderRect()
{
	return QRect(
		m_padding, m_padding,
		size().width() - m_padding * 2,
		size().height() - m_padding * 2
	);
}

void UploadArea::drawBorder(QPainter& painter)
{
	painter.save();
	if (m_hover)
	{
		painter.setBrush(QColor(138, 138, 138));
	}
	// 绘制矩形上传区域
	painter.drawRoundedRect(
		calBorderRect(),
		m_radius, m_radius
	);
	painter.restore();
}

void UploadArea::drawUploadIcon(QPainter& painter)
{
	// 绘制上传图标
	QPixmap uploadIcon = QPixmap(Util::getQrcIconPath("up-load", Util::activeColor, 64));
	int w = uploadIcon.size().width();
	int h = uploadIcon.size().height();
	painter.drawPixmap(
		(size().width() - w) / 2,
		(size().height() - h) / 2 + h,
		w ,
		h ,
		uploadIcon
	);
}

void UploadArea::paintEvent(QPaintEvent* event)
{

	QPainter painter(this);
	drawBorder(painter);
	drawUploadIcon(painter);
	painter.save();
	painter.setFont(QFont(QString::fromLatin1("微软雅黑"), 16));

	painter.drawText(
		QRect(
			m_padding, m_padding,
			size().width() - m_padding * 2,
			size().height() - m_padding * 2
		),
		Qt::AlignCenter,
		QStringLiteral("拖动文件到此处，或者点击上传")
	);
	painter.restore();
}

void UploadArea::dragEnterEvent(QDragEnterEvent* event)
{
	//如果为文件，则支持拖放
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void UploadArea::dropEvent(QDropEvent* event)
{
	QiniuUploadManager manager;
	manager.uploadUrlList(event->mimeData()->urls());
}
