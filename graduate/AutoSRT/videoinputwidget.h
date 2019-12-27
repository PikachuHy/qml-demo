#ifndef VIDEOINPUTWIDGET_H
#define VIDEOINPUTWIDGET_H

#include <QWidget>

class VideoInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoInputWidget(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void receiveVideoFile(QString filename);
private:
};

#endif // VIDEOINPUTWIDGET_H
