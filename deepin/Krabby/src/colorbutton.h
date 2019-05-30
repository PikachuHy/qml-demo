#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>
#include <QColor>
class ColorButton : public QPushButton
{
public:
    ColorButton(QWidget* parent = nullptr);
    void setColor(const QColor &color);

private:
    QColor m_color;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // COLORBUTTON_H
