//
// Created by pikachu on 19-2-15.
//

#include <QString>
#include <QtTest>
#include <util.h>
QINIU_USE_NAMESPACE
class UtilTest : public QObject
{
    Q_OBJECT

public:
    UtilTest() = default;

private Q_SLOTS:
    void testHmacSha1();
};

void UtilTest::testHmacSha1()
{
    QByteArray baseString = QString("eyJzY29wZSI6Im15LWJ1Y2tldDpzdW5mbG93ZXIuanBnIiwiZGVhZGxpbmUiOjE0NTE0OTEyMDAsInJldHVybkJvZHkiOiJ7XCJuYW1lXCI6JChmbmFtZSksXCJzaXplXCI6JChmc2l6ZSksXCJ3XCI6JChpbWFnZUluZm8ud2lkdGgpLFwiaFwiOiQoaW1hZ2VJbmZvLmhlaWdodCksXCJoYXNoXCI6JChldGFnKX0ifQ==").toUtf8();
    QByteArray key = QString("MY_SECRET_KEY").toUtf8();
    QString actual = Util::hmacSha1(baseString, key);
    QCOMPARE(actual, QString("wQ4ofysef1R7IKnrziqtomqyDvI="));
}
QTEST_MAIN(UtilTest)
#include "UtilTest.moc"