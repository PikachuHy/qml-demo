#ifndef CHOOSEARTICLEDIALOG_H
#define CHOOSEARTICLEDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseArticleDialog;
}
class QTreeWidgetItem;
class ChooseArticleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseArticleDialog(QWidget *parent = 0);
    ~ChooseArticleDialog();
signals:
    void chooseArticle(QString text);
private slots:
    void on_pushButtonConfirm_clicked();
    void handleTreeWidgetItemClicked(QTreeWidgetItem *item, int column);
    void on_pushButtonFolder_clicked();

private:
    Ui::ChooseArticleDialog *ui;
};

#endif // CHOOSEARTICLEDIALOG_H
