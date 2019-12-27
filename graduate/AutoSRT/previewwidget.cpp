#include "previewwidget.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtWidgets>
#include <QGraphicsVideoItem>
#include <QGraphicsTextItem>
#include <QTimer>
PreviewWidget::PreviewWidget():QWidget()
{
    PreviewMode = ALL;
    m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    m_videoItem = new QGraphicsVideoItem;
    m_mediaPlayer->setMedia(QUrl::fromLocalFile("/Users/pikachu/src/ali-nls-demo/demo.mp4"));

    m_mediaPlayer->setVolume(50);
//    m_mediaPlayer->play();
    m_mediaPlayer->setVideoOutput(m_videoItem);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &PreviewWidget::positionChanged);
    auto scene = new QGraphicsScene(this);
    auto graphicsView = new QGraphicsView(scene);
    scene->addItem(m_videoItem);

    m_srtTextItem = new QGraphicsTextItem();
    m_srtTextItem->setDefaultTextColor(QColorConstants::White);
    auto font = m_srtTextItem->font();
    font.setPixelSize(26);
    m_srtTextItem->setFont(font);
    auto effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(1, 1);
    m_srtTextItem->setGraphicsEffect(effect);
    scene->addItem(m_srtTextItem);

    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(graphicsView);

    auto btn = new QPushButton("HIDE SRT");
    connect(btn, &QPushButton::clicked, [=]() {
        if (m_srtTextItem->isVisible()) {
            m_srtTextItem->hide();
            btn->setText("SHOW SRT");
        } else {
            m_srtTextItem->show();
            btn->setText("HIDE SRT");
        }
    });
//    layout->addWidget(btn);
    QTimer::singleShot(1000,this, &PreviewWidget::calSrtPos);
}

void PreviewWidget::calSrtPos() const {
    auto textRectSize = m_srtTextItem->boundingRect().size();
    auto target_y = m_videoItem->size().height() - textRectSize.height();
    auto target_x = (m_videoItem->size().width() - textRectSize.width()) / 2;
    m_srtTextItem->setPos(target_x, target_y);

}

void PreviewWidget::play(qint64 start, qint64 end, const QString & srtText) {
    PreviewMode = SINGLE_SRT;
    if (m_mediaPlayer->state() == QMediaPlayer::PlayingState) {
        m_mediaPlayer->pause();
    }
    m_end = end;
    m_srtTextItem->setPlainText(srtText);
    m_srtTextItem->show();
    calSrtPos();
    m_mediaPlayer->setPosition(start);
    m_mediaPlayer->play();
}

void PreviewWidget::positionChanged(qint64 position) {
    if (PreviewMode == ALL) return;
    if (position >= m_end) {
        m_mediaPlayer->pause();
        m_srtTextItem->hide();
    }
}

void PreviewWidget::setPreviewVideoFile(QString filename) {
    m_mediaPlayer->stop();
    m_mediaPlayer->setMedia(QUrl::fromLocalFile(filename));
    m_mediaPlayer->play();
    m_videoItem->show();
    QTimer::singleShot(500, [=](){
        m_mediaPlayer->pause();
    });
}

void PreviewWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    m_videoItem->setSize(event->size());
    calSrtPos();
}
