#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

class Toolbar : public QWidget
{
    Q_OBJECT
public:
    explicit Toolbar(QWidget *parent = nullptr);

signals:
    void reset();
    void chooseArticle();
public slots:
};

#endif // TOOLBAR_H
