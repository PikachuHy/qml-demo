#include "colorbutton.h"
#include <QPainter>
#include <QDebug>
ColorButton::ColorButton(QWidget *parent): QPushButton(parent)
{
    setAutoFillBackground(true);
}

void ColorButton::setColor(const QColor &color)
{
    m_color = color;
    update();
}


void ColorButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    auto p = this->palette();
    p.setColor(QPalette::Button, m_color);
    setPalette(p);
}
