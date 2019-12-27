#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QWidget>
#include <QGraphicsTextItem>

QT_BEGIN_NAMESPACE
class QGraphicsVideoItem;
QT_END_NAMESPACE

class PreviewWidget: public QWidget
{
    Q_OBJECT
    enum {
        SINGLE_SRT,
        ALL
    } PreviewMode;
public:
    PreviewWidget();

public slots:
    void play(qint64 start, qint64 end, const QString & srtText);
    void setPreviewVideoFile(QString filename);
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QMediaPlayer *m_mediaPlayer = nullptr;
    QGraphicsVideoItem *m_videoItem = nullptr;
    QGraphicsTextItem *m_srtTextItem;
    qint64 m_end;
private:
    void positionChanged(qint64 position);

    void calSrtPos() const;
};

#endif // PREVIEWWIDGET_H
