#pragma once
#include <qwidget.h>
class UploadArea :
	public QWidget
{
	Q_OBJECT
public:
	UploadArea(QWidget *parent = nullptr);
	~UploadArea();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

	void dragEnterEvent(QDragEnterEvent *event) override;
	void dropEvent(QDropEvent *event) override;
signals:
	void click();
private:
	int m_padding;
	int m_radius;
	bool m_hover;
private:
	void drawBorder(QPainter& painter);
	void drawUploadIcon(QPainter& painter);
	QRect calBorderRect();
};

