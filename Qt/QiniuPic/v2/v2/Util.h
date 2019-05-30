#pragma once
namespace Util
{
	// 激活状态下的颜色
	static QString activeColor = "1296db";
	// 失去焦点的颜色
	static QString inactiveColor = "8a8a8a";
	// 默认图标大小
	static int defaultIconSize = 64;
	// 获取图标路径
	QString getQrcIconPath(QString name, QString color, int size);
	// 判断本地文件是不是图片
	bool isPicture(QString filepath);
	// 判断点是不是在矩形内
	bool isPointInRect(QPoint point, QRect rect);
};
