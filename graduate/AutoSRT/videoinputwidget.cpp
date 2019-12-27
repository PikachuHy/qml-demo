#include "videoinputwidget.h"
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <QLabel>
#include <QtWidgets>
#include <QStandardPaths>
VideoInputWidget::VideoInputWidget(QWidget *parent) : QWidget(parent) {
    setAcceptDrops(true);
    resize(800, 600);
}

void VideoInputWidget::dragEnterEvent(QDragEnterEvent *event) {

    if (event->mimeData()->hasFormat("text/uri-list"))
        //拖拽时间已经接受了用户的拖拽动作
        //if not the code,then dropEvent would not be called
        event->acceptProposedAction();

    QWidget::dragEnterEvent(event);
}

void VideoInputWidget::dropEvent(QDropEvent *event) {
    qDebug() << "dropEvent";
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;
    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty())
        return;
    qDebug() << tr("%1  -- %2").arg(fileName).arg(fileName);
    if (!fileName.endsWith(".mp4")) {
        QMessageBox::warning(this, tr("Drag File Error"), tr("Currently Only Support *.mp4 Video File"));
    }
    emit receiveVideoFile(fileName);
    event->accept();
}

void VideoInputWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    int center_x = this->rect().width() / 2;
    int center_y = this->rect().height() / 2;
    float factor = 1.0 * 4 / 5;
    painter.drawLine(center_x, this->rect().height() * (1 - factor), center_x, this->rect().height() * factor);
    painter.drawLine(this->rect().width() * (1 - factor), center_y, this->rect().width() * factor, center_y);
    painter.drawText(0, this->height()  / 3, this->width(), this->height(),
            Qt::AlignHCenter | Qt::AlignVCenter,
            "Drag Video File to Here OR Click to Choose");
    QWidget::paintEvent(event);
}

void VideoInputWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QString filepath = QFileDialog::getOpenFileName(this,
                tr("Choose Video File"),
               QDir::homePath(),
                 tr("Video (*.mp4)"));
        if (filepath.isEmpty()) {
            return;
        }
        emit receiveVideoFile(filepath);
        event->accept();
        return;
    }
    QWidget::mouseReleaseEvent(event);
}
