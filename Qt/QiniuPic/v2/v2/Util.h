#pragma once
namespace Util
{
	// ����״̬�µ���ɫ
	static QString activeColor = "1296db";
	// ʧȥ�������ɫ
	static QString inactiveColor = "8a8a8a";
	// Ĭ��ͼ���С
	static int defaultIconSize = 64;
	// ��ȡͼ��·��
	QString getQrcIconPath(QString name, QString color, int size);
	// �жϱ����ļ��ǲ���ͼƬ
	bool isPicture(QString filepath);
	// �жϵ��ǲ����ھ�����
	bool isPointInRect(QPoint point, QRect rect);
};
