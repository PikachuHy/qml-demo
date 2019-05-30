#include "choosearticledialog.h"
#include "ui_choosearticledialog.h"
#include <QtWidgets>
ChooseArticleDialog::ChooseArticleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseArticleDialog)
{
    ui->setupUi(this);
    ui->pushButtonFolder->setIcon(QIcon(":/icon/folder.png"));
    ui->treeWidget->header()->hide();
    QDir rootDir(":/article");
    auto list = rootDir.entryInfoList();
    for(auto dir: list) {
        qDebug() << dir.baseName();
        auto item =  new QTreeWidgetItem();
        item->setText(0, dir.baseName());
        ui->treeWidget->addTopLevelItem(item);
        QDir typeDir(dir.absoluteFilePath());
        for(QString file: typeDir.entryList()) {
            qDebug() << file;
            auto list = QStringList()
                    << file.left(file.length() - 4)
                    << QString("%1/%2").arg(dir.absoluteFilePath()).arg(file);
                                         ;
            item->addChild(new QTreeWidgetItem(list));
        }
    }

    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &ChooseArticleDialog::handleTreeWidgetItemClicked);
}

ChooseArticleDialog::~ChooseArticleDialog()
{
    delete ui;
}

void ChooseArticleDialog::on_pushButtonConfirm_clicked()
{
    emit chooseArticle(ui->textBrowser->toPlainText());
    this->close();
}

void ChooseArticleDialog::handleTreeWidgetItemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    auto path = item->text(1);
    if (!path.isEmpty()) {
        qDebug() << path;
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        auto text = file.readAll();
        ui->textBrowser->setText(text);
        ui->pushButtonConfirm->setEnabled(true);
    } else {
        ui->pushButtonConfirm->setDisabled(true);
    }
}

void ChooseArticleDialog::on_pushButtonFolder_clicked()
{
    auto filepath = QFileDialog::getOpenFileName(
                this,
                tr("Choose Article"),
                QStandardPaths::displayName(QStandardPaths::DocumentsLocation),
                tr("text (*.txt)")
                );
    if (filepath.isEmpty()) {
        return;
    }
    QFile file(filepath);
    if (!file.exists()) {
        return;
    }
    file.open(QIODevice::ReadOnly);
    auto text = file.readAll();
    file.close();

    emit chooseArticle(text);
    this->close();
}
