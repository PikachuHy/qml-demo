#include <string>
#include <map>
#include <iostream>
#include <QString>
#include <QCryptographicHash>

/**
 * Hashes the given string using the HMAC-SHA1 algorithm.
 *
 * \param key The string to be hashed
 * \param secret The string that contains secret word
 * \return The hashed string
 */
static QString hmac_sha1(const QString &key, const QString &secret) {
    // Length of the text to be hashed
    int text_length;
    // For secret word
    QByteArray K;
    // Length of secret word
    int K_length;

    K_length = secret.size();
    text_length = key.size();

    // Need to do for XOR operation. Transforms QString to
    // unsigned char

//    K = secret.toAscii();
    K = secret.toLatin1();

    // Inner padding
    QByteArray ipad;
    // Outer padding
    QByteArray opad;

    // If secret key > 64 bytes use this to obtain sha1 key
    if (K_length > 64) {
        QByteArray tempSecret;

        tempSecret.append(secret);

        K = QCryptographicHash::hash(tempSecret, QCryptographicHash::Sha1);
        K_length = 20;
    }

    // Fills ipad and opad with zeros
    ipad.fill(0, 64);
    opad.fill(0, 64);

    // Copies Secret to ipad and opad
    ipad.replace(0, K_length, K);
    opad.replace(0, K_length, K);

    // XOR operation for inner and outer pad
    for (int i = 0; i < 64; i++) {
        ipad[i] = ipad[i] ^ 0x36;
        opad[i] = opad[i] ^ 0x5c;
    }

    // Stores hashed content
    QByteArray context;

    // Appends XOR:ed ipad to context
    context.append(ipad, 64);
    // Appends key to context
    context.append(key);

    //Hashes inner pad
    QByteArray Sha1 = QCryptographicHash::hash(context, QCryptographicHash::Sha1);

    context.clear();
    //Appends opad to context
    context.append(opad, 64);
    //Appends hashed inner pad to context
    context.append(Sha1);

    Sha1.clear();

    // Hashes outerpad
    Sha1 = QCryptographicHash::hash(context, QCryptographicHash::Sha1);

    // String to return hashed stuff in Base64 format
    QByteArray str(Sha1.toBase64());

    return str;
}
/*
AccessKeyId:my_access_key_id
Action:CreateToken
Version:2019-02-28
Timestamp:2019-04-18T08:32:31Z
Format:JSON
RegionId:cn-shanghai
SignatureMethod:HMAC-SHA1
SignatureVersion:1.0
SignatureNonce:b924c8c3-6d03-4c5d-ad36-d984d3116788

 AccessKeyId=my_access_key_id&Action=CreateToken&Format=JSON&RegionId=cn-shanghai&SignatureMethod=HMAC-SHA1&SignatureNonce=b924c8c3-6d03-4c5d-ad36-d984d3116788&SignatureVersion=1.0&Timestamp=2019-04-18T08%3A32%3A31Z&Version=2019-02-28
 */
using std::map;
using std::string;
unsigned char toHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}
std::string urlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += toHex((unsigned char)str[i] >> 4);
            strTemp += toHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}
// 获取系统当前时间
std::string getCurrentSystemTime()
{
    std::time_t course_start_time1 = time(NULL);
    char buf[32];
    strftime(buf, sizeof(buf), "%FT%TZ", gmtime(&course_start_time1));
//    std::cout << buf << std::endl;
    return std::string(buf);
}

//void ASSERT_EQ(std::string &a, std::string &b) {
#define ASSERT_EQ(a, b) \
{\
    bool cmp = a == b; \
    std::cout << (cmp) << std::endl; \
    if (!cmp) { \
        const char *pp = a.c_str(); \
        const char *qq = b.c_str(); \
        char *p = (char *)pp; \
        char *q = (char *)qq; \
        while(*p == *q) { \
            p++; \
            q++; \
        } \
        printf("%s\n", p); \
        printf("%s\n", q); \
        printf("%s:%d\n", __FILE__, __LINE__); \
        exit(1); \
    } \
}\
//}
int main1() {
    string AccessKeySecret="my_access_key_secret";
    map<string, string> m;
    m["AccessKeyId"]="my_access_key_id";
    m["Action"]="CreateToken";
    m["Version"]="2019-02-28";
    m["Timestamp"]="2019-04-18T08:32:31Z";
    m["Format"]="JSON";
    m["RegionId"]="cn-shanghai";
    m["SignatureMethod"]="HMAC-SHA1";
    m["SignatureVersion"]="1.0";
    m["SignatureNonce"]="b924c8c3-6d03-4c5d-ad36-d984d3116788";
    string queryString;
    for(auto it: m) {
        queryString.append("&").append(urlEncode(it.first)).append("=").append(urlEncode(it.second));
    }
    queryString = queryString.substr(1);
    std::cout << queryString << std::endl;
    string target = "AccessKeyId=my_access_key_id&Action=CreateToken&Format=JSON&RegionId=cn-shanghai&SignatureMethod=HMAC-SHA1&SignatureNonce=b924c8c3-6d03-4c5d-ad36-d984d3116788&SignatureVersion=1.0&Timestamp=2019-04-18T08%3A32%3A31Z&Version=2019-02-28";
    ASSERT_EQ(queryString, target);
    string strSign;
    strSign.append("GET").append("&")
    .append(urlEncode("/")).append("&")
    .append(urlEncode(queryString));
    target = "GET&%2F&AccessKeyId%3Dmy_access_key_id%26Action%3DCreateToken%26Format%"
             "3DJSON%26RegionId%3Dcn-shanghai%26SignatureMethod%3DHMAC-SHA1%26Signatu"
             "reNonce%3Db924c8c3-6d03-4c5d-ad36-d984d3116788%26SignatureVersion%3D1.0"
             "%26Timestamp%3D2019-04-18T08%253A32%253A31Z%26Version%3D2019-02-28";
    ASSERT_EQ(strSign, target);
    string signature = hmac_sha1(QString::fromStdString(strSign), QString::fromStdString(AccessKeySecret+"&")).toStdString();
    target = "hHq4yNsPitlfDJ2L0nQPdugdEzM=";
    ASSERT_EQ(signature, target);
    string queryStringWithSign = "Signature=" + urlEncode(signature) + "&" + queryString;
    target = "Signature=hHq4yNsPitlfDJ2L0nQPdugdEzM%3D&AccessKeyId=my_access_key_id&Action=CreateToken&Format=JSON&RegionId=cn-shanghai&SignatureMethod=HMAC-SHA1&SignatureNonce=b924c8c3-6d03-4c5d-ad36-d984d3116788&SignatureVersion=1.0&Timestamp=2019-04-18T08%3A32%3A31Z&Version=2019-02-28";
    ASSERT_EQ(queryStringWithSign, target);
    return 0;
}
string genTokenRequestParam(const string & AccessKeyId, const string &AccessKeySecret) {
    map<string, string> m;
    m["AccessKeyId"]=AccessKeyId;
    m["Action"]="CreateToken";
    m["Version"]="2019-02-28";
    m["Timestamp"]=getCurrentSystemTime();
    m["Format"]="JSON";
    m["RegionId"]="cn-shanghai";
    m["SignatureMethod"]="HMAC-SHA1";
    m["SignatureVersion"]="1.0";
    m["SignatureNonce"]="b924c8c3-6d03-4c5d-ad36-d984d3116788";
    string queryString;
    for(auto it: m) {
        queryString.append("&").append(urlEncode(it.first)).append("=").append(urlEncode(it.second));
    }
    queryString = queryString.substr(1);
    std::cout << queryString << std::endl;
    string target = "AccessKeyId=my_access_key_id&Action=CreateToken&Format=JSON&RegionId=cn-shanghai&SignatureMethod=HMAC-SHA1&SignatureNonce=b924c8c3-6d03-4c5d-ad36-d984d3116788&SignatureVersion=1.0&Timestamp=2019-04-18T08%3A32%3A31Z&Version=2019-02-28";
//    ASSERT_EQ(queryString, target);
    string strSign;
    strSign.append("GET").append("&")
    .append(urlEncode("/")).append("&")
    .append(urlEncode(queryString));
//    target = "GET&%2F&AccessKeyId%3Dmy_access_key_id%26Action%3DCreateToken%26Format%"
//             "3DJSON%26RegionId%3Dcn-shanghai%26SignatureMethod%3DHMAC-SHA1%26Signatu"
//             "reNonce%3Db924c8c3-6d03-4c5d-ad36-d984d3116788%26SignatureVersion%3D1.0"
//             "%26Timestamp%3D2019-04-18T08%253A32%253A31Z%26Version%3D2019-02-28";
//    ASSERT_EQ(strSign, target);
    string signature = hmac_sha1(QString::fromStdString(strSign), QString::fromStdString(AccessKeySecret+"&")).toStdString();
    target = "hHq4yNsPitlfDJ2L0nQPdugdEzM=";
//    ASSERT_EQ(signature, target);
    string queryStringWithSign = "Signature=" + urlEncode(signature) + "&" + queryString;
    target = "Signature=hHq4yNsPitlfDJ2L0nQPdugdEzM%3D&AccessKeyId=my_access_key_id&Action=CreateToken&Format=JSON&RegionId=cn-shanghai&SignatureMethod=HMAC-SHA1&SignatureNonce=b924c8c3-6d03-4c5d-ad36-d984d3116788&SignatureVersion=1.0&Timestamp=2019-04-18T08%3A32%3A31Z&Version=2019-02-28";
//    ASSERT_EQ(queryStringWithSign, target);
    return queryStringWithSign;
}
string gen2(const string & AccessKeyId,
        const string &AccessKeySecret,
        const string &AppKey) {
    map<string, string> m;
    m["AccessKeyId"]=AccessKeyId;
    m["Action"]="SubmitTask";
//    m["Product"]="nls-filetrans";
    m["Version"]="2018-08-17";
    m["Timestamp"]=getCurrentSystemTime();
//    m["Timestamp"]="2019-12-17T01:50:16Z";
    m["Format"]="JSON";
    m["RegionId"]="cn-shanghai";
    m["SignatureMethod"]="HMAC-SHA1";
    m["SignatureVersion"]="1.0";
    m["SignatureNonce"]="ce41cb44-5e64-4fb0-808a-e2994d437756";
    string url = "https://nls-demo.oss-cn-hangzhou.aliyuncs.com/%E9%98%BF%E9%87%8C%E4%BA%91%E6%B5%8B%E8%AF%95.mp3?Expires=1576470050&OSSAccessKeyId=TMP.hjK9Ysxsi3Nmb9UrbwuAovZkqZP2SoXXCWGRYepuAMwrPTpCEsNEupY9sNeZxaTE8gL8DnWkaauFrU84goDvoRsevho7VenJmRzC7XUQSof3auJLsnBptpMGR4TDiF.tmp&Signature=irCPD%2F29VqFxvVijsOjl5nstTy4%3D";
    m["Task"]=R"({"appkey":")"+AppKey+R"(","file_link":")"+url+"\"}";
    std::cout << m["Task"] << std::endl;
//    m["Product"]="nls-filetrans";
    string queryString;
    for(auto it: m) {
        queryString.append("&").append(urlEncode(it.first)).append("=").append(urlEncode(it.second));
    }
    queryString = queryString.substr(1);
    std::cout << queryString << std::endl;
    string strSign;
    strSign.append("POST").append("&")
    .append(urlEncode("/")).append("&")
    .append(urlEncode(queryString));
    std::cout << strSign << std::endl;
    string signature = hmac_sha1(QString::fromStdString(strSign), QString::fromStdString(AccessKeySecret+"&")).toStdString();

    string queryStringWithSign = "Signature=" + urlEncode(signature) + "&" + queryString;
    return queryStringWithSign;
}
string genGetTaskResultRequestParam(const string & AccessKeyId,
                                    const string &AccessKeySecret,
                                    const string &TaskId) {
    map<string, string> m;
    m["AccessKeyId"]=AccessKeyId;
    m["Action"]="GetTaskResult";
    m["TaskId"]=TaskId;
//    m["Product"]="nls-filetrans";
    m["Version"]="2018-08-17";
//    m["Timestamp"]=getCurrentSystemTime();
    m["Timestamp"]="2019-12-17T03:24:47Z";
    m["Format"]="JSON";
    m["RegionId"]="cn-shanghai";
    m["SignatureMethod"]="HMAC-SHA1";
    m["SignatureVersion"]="1.0";
    m["SignatureNonce"]="2aa27764-6769-413b-959a-d6ae9ae88225";
    string queryString;
    for(auto it: m) {
        queryString.append("&").append(urlEncode(it.first)).append("=").append(urlEncode(it.second));
    }
    queryString = queryString.substr(1);
    std::cout << queryString << std::endl;
    string strSign;
    strSign.append("GET").append("&")
    .append(urlEncode("/")).append("&")
    .append(urlEncode(queryString));
    std::cout << strSign << std::endl;
    string target = "GET&%2F&AccessKeyId%3D9yVbit0fM2kkofoh%26Action%3DGetTaskResult%26Format%3DJSON%26RegionId%3Dcn-shanghai%26SignatureMethod%3DHMAC-SHA1%26SignatureNonce%3D2aa27764-6769-413b-959a-d6ae9ae88225%26SignatureVersion%3D1.0%26TaskId%3D4c35022c207b11eaa48d6f9e4aa9bb45%26Timestamp%3D2019-12-17T03%253A24%253A47Z%26Version%3D2018-08-17";
    ASSERT_EQ(strSign, target);
    string signature = hmac_sha1(QString::fromStdString(strSign), QString::fromStdString(AccessKeySecret+"&")).toStdString();

    string queryStringWithSign = "Signature=" + urlEncode(signature) + "&" + queryString;
    return queryStringWithSign;
}
int main2() {
    string ret = genTokenRequestParam("<>", "<>");
    std::cout << "http://nls-meta.cn-shanghai.aliyuncs.com/?" <<ret << std::endl;
//    string s = getCurrentSystemTime();
//    std::cout << s << std::endl;
    return 0;
}

int main3() {
    string json = "{\"NlsRequestId\":\"6508f453c55c4cc6aa08201622b49560\",\"ErrMsg\":\"\",\"RequestId\":\"733F0681-B024-476C-94B5-B715E516CF19\",\"Token\":{\"ExpireTime\":1576630684,\"Id\":\"5f2a5864b5054415bf3a77e9d5529d4d\",\"UserId\":\"1000455180445775\"}}";
    std::cout << json << std::endl;
    return 0;
}

int main4() {
//    string domain = "filetrans.cn-shanghai.aliyuncs.com";
    string ret = gen2("<>", "<>", "<>");
    std::cout << "http://filetrans.cn-shanghai.aliyuncs.com/?" << ret << std::endl;
    return 0;
}
/*
{
    "StatusCode": 21050000,
    "StatusText": "SUCCESS",
    "RequestId": "3EBC27DF-5175-4505-9608-4CB408A43EED",
    "TaskId": "c8aba046207311ea82d6297db598041e"
}

 */

int main() {
    string ret = genGetTaskResultRequestParam("<>", "<>",
                                              "<>");
    std::cout << "http://filetrans.cn-shanghai.aliyuncs.com/?" << ret << std::endl;
    return 0;
}