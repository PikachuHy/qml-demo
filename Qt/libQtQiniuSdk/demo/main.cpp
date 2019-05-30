#include <QCoreApplication>
#include <QtQiniu>
#include <QFile>
QINIU_USE_NAMESPACE
QByteArray getFileData()
{
    // 需要换成图片的路径
    QFile file("/home/pikachu/CLionProjects/libQtQiniuSdk/logo-qiniu.png");
    file.open(QIODevice::ReadOnly);
    QByteArray fdata = file.readAll();
    file.close();
    return fdata;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 需要换成自己的Key
    QString accessKey = "<accessKey>";
    QString secretKey = "<secretKey>";
    // 需要换成自己的存储空间
    QString bucket = "<bucket>";
    Auth auth(accessKey, secretKey);
    QString key = "test.png";
    UploadManager manager;
    auto token = auth.getUploadToken(bucket, key);
    manager.put(getFileData(), key, token);
    return QCoreApplication::exec();
}
