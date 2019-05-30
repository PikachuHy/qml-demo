#pragma once

#include <QWidget>
#include "ui_QiniuSetting.h"

class QiniuSetting : public QWidget
{
	Q_OBJECT

public:
	QiniuSetting(QWidget *parent = Q_NULLPTR);
	~QiniuSetting();

private:
	Ui::QiniuSetting ui;
};
