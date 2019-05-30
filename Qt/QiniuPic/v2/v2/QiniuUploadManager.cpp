#include "stdafx.h"
#include "QiniuUploadManager.h"
#include "qiniu/io.h"
#include "qiniu/rs.h"
#include "Notify.h"
#include "Util.h"
#include "QiniuPicApplication.h"
#include "Setting.h"
/*debug ����*/
void debug_log(Qiniu_Client *client, Qiniu_Error err) {
	printf("\nerror code: %d, message: %s\n", err.code, err.message);
	printf("response header:\n%s", Qiniu_Buffer_CStr(&client->respHeader));
	printf("response body:\n%s", Qiniu_Buffer_CStr(&client->b));
	printf("\n\n\n");
	qDebug() << "error code: " << err.code << ", message: " << err.message;
	qDebug() << "response header: " << Qiniu_Buffer_CStr(&client->respHeader);
	qDebug() << "response body: " << Qiniu_Buffer_CStr(&client->b);
}
QiniuUploadManager::QiniuUploadManager()
{
}


QiniuUploadManager::~QiniuUploadManager()
{
}

void QiniuUploadManager::upload(QString filepath)
{
	qDebug() << "upload file: " << filepath;
	Qiniu_Global_Init(-1);

	Qiniu_Io_PutRet putRet;
	Qiniu_Client client;
	Qiniu_RS_PutPolicy putPolicy;
	Qiniu_Io_PutExtra putExtra;

	const char *accessKey = "fTVwJVnuuZ3au8z9J4TO9Zxg9Ptfee9kIPks0Hzx";
	const char *secretKey = "wPXGQ50rtBpbI5fdidh_D3S5WkA6Bn0zI_DD926V";
	const char *bucket = "pikachu-blog";
	QString keyString = QString("/%1/%2/%3")
		.arg(QDateTime::currentDateTime().toString("yyyyMMdd"))
		.arg(QDateTime::currentDateTime().toTime_t())
		.arg(QFileInfo(filepath).fileName());
	qDebug() << "keyString: " << keyString;
	// �������в���ɾ�������ܺϲ���ֻ���������״̬���ܱ�֤key�ǲ������
	QByteArray keyBa = keyString.toLocal8Bit();
	const char* key = keyBa.data();
	qDebug() << "key: " << key;
	// ͬ��
	QByteArray filepathBa = filepath.toLocal8Bit();
	const char *localFile = filepathBa.data();
	qDebug() << "local file: " << localFile;
	Qiniu_Mac mac;
	mac.accessKey = accessKey;
	mac.secretKey = secretKey;

	Qiniu_Zero(putPolicy);
	Qiniu_Zero(putExtra);

	putPolicy.scope = bucket;
	char *uptoken = Qiniu_RS_PutPolicy_Token(&putPolicy, &mac);

	//���û�������
	//Qiniu_Use_Zone_Beimei(Qiniu_False);
	//Qiniu_Use_Zone_Huabei(Qiniu_True);
	Qiniu_Use_Zone_Huadong(Qiniu_True);
	//Qiniu_Use_Zone_Huanan(Qiniu_True);

	//put extra
	//putExtra.upHost="http://nbxs-gate-up.qiniu.com";

	//init
	Qiniu_Client_InitMacAuth(&client, 1024, &mac);
	Qiniu_Error error = Qiniu_Io_PutFile(&client, &putRet, uptoken, key, localFile, &putExtra);
	if (error.code != 200) {
		qDebug() << "upload file" << bucket << ":" << key << "error.";
		printf("upload file %s:%s error.\n", bucket, key);
		debug_log(&client, error);
	}
	else {
		/*200, ��ȷ������, �����ͨ��statRet������ѯһЩ��������ļ�����Ϣ*/
		printf("upload file %s:%s success.\n\n", bucket, key);
		qDebug() << "upload file" << bucket << ":" << key << "success.";
		printf("key:\t%s\n", putRet.key);
		printf("hash:\t%s\n", putRet.hash);
		qDebug() << "key:" << putRet.key;
		qDebug() << "hash:" << putRet.hash;
		QString url = QString("http://cdn.pikachu.net.cn/%1").arg(key);
		auto text = calCopyText(url);
		qDebug() << "copy text: " << text;
		qApp->clipboard()->setText(text);
		Notify notify;
		notify.sendNotify(filepath, url);
		auto setting = qApp->setting();
		setting->addUploadImageUrl(url);
	}

	Qiniu_Free(uptoken);
	Qiniu_Client_Cleanup(&client);
}

void QiniuUploadManager::uploadImage(QImage image)
{
	if (image.isNull())
	{
		qDebug() << "ͼƬΪ�գ�ȡ���ϴ�";
		return;
	}
	QTemporaryFile* tmpFile = new QTemporaryFile("QiniuPic.XXXXXX.png");
	if (!tmpFile->open()) {
		qDebug() << "����ʱ�ļ�ʧ��";
		return;
	}
	QString tmpFilePath = tmpFile->fileName();
	qDebug() << "tmp file: " << tmpFilePath;
	auto saveResult = image.save(tmpFilePath);
	if (!saveResult)
	{
		qDebug() << "�����ļ�������ʧ��";
		return;
	}
	upload(tmpFilePath);
	// ���֪ͨ��Ҫ����ʱͼƬ������
	QTimer::singleShot(60 * 1000, [=]()
	{
		tmpFile->deleteLater();
	});
}

void QiniuUploadManager::uploadUrlList(QList<QUrl> urlList)
{
	for (QUrl it : urlList)
	{
		// �ж��ǲ��Ǳ����ļ�����������
		if (!it.isLocalFile())
		{
			qDebug() << it << "is not local file. skip����!";
			continue;
		}
		QString localFile = it.toLocalFile();
		// �ж��ǲ���ͼƬ����������
		if (!Util::isPicture(localFile))
		{
			qDebug() << localFile << "is not picture. skip!!!";
			continue;
		}
		qDebug() << "upload local file: " << localFile;
		upload(localFile);
	}
}

QString QiniuUploadManager::calCopyText(QString url)
{
	auto setting = qApp->setting();
	QString text;
	if (setting->copyLinkTypeIsURL())
	{
		text = url;
	}
	else if (setting->copyLinkTypeIsHTML())
	{
		text = QString("<img src=\"%1\"/>").arg(url);
	} else
	{
		text = QString("![img](%1)").arg(url);
	}
	return text;
}
