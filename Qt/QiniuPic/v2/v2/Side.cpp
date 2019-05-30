#include "stdafx.h"
#include "Side.h"
#include "SideItem.h"
#include "Util.h"


Side::Side(QWidget* parent): QWidget(parent)
{
	QVBoxLayout *vBox = new QVBoxLayout(this);
	vBox->addStretch();
	SideItem * uploadSideItem = new SideItem("up-load", QStringLiteral("ͼƬ�ϴ�"), this);
	uploadSideItem->setSelected(true);
	vBox->addWidget(uploadSideItem);
	SideItem* photoSideItem = new SideItem("photo", QStringLiteral("������"), this);
	vBox->addWidget(photoSideItem);
	SideItem* settingSideItem = new SideItem("setting", QStringLiteral("��ţ����"), this);
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
