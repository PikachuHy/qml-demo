#include "stdafx.h"
#include "Side.h"
#include "SideItem.h"
#include "Util.h"


Side::Side(QWidget* parent): QWidget(parent)
{
	QVBoxLayout *vBox = new QVBoxLayout(this);
	vBox->addStretch();
	SideItem * uploadSideItem = new SideItem("up-load", QStringLiteral("图片上传"), this);
	uploadSideItem->setSelected(true);
	vBox->addWidget(uploadSideItem);
	SideItem* photoSideItem = new SideItem("photo", QStringLiteral("相册管理"), this);
	vBox->addWidget(photoSideItem);
	SideItem* settingSideItem = new SideItem("setting", QStringLiteral("七牛设置"), this);
	vBox->addWidget(settingSideItem);
	vBox->addStretch();
	setLayout(vBox);
	m_sideItemList << uploadSideItem << photoSideItem << settingSideItem;
	for(SideItem* it : m_sideItemList)
	{
		connect(it, &SideItem::click, [=]()
		{
			clearSelected();
			it->setSelected(true);
			emit currentItemChange(it->title());
			repaint();
		});
	}
}

Side::~Side()
{
}

void Side::clearSelected()
{
	for (SideItem* it : m_sideItemList)
	{
		it->setSelected(false);
	}

}
