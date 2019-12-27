//
// Created by PikachuHy on 2019/12/19.
//

#include "util.h"
#include <QtCore>
namespace util {
    QString formatUnit(long t) {
        if (t == 0) return "00";
        if (t >= 10) return QString::number(t);
        return "0" + QString::number(t);
    }

    QString formatTime(long time) {
        QString sb;
        // h
        long left = time / (60 * 60 * 1000);
        time %= 60 * 60 * 1000;
        sb.append(formatUnit(left)).append(":");
        // min
        left = time / (60 * 1000);
        time %= 60 * 1000;
        sb.append(formatUnit(left)).append(":");
        // s
        left = time / (1000);
        time %= 1000;
        sb.append(formatUnit(left)).append(",");
        if (time == 0) {
            sb.append("000");
        } else if (time < 10) {
            sb.append("00");
            sb.append(QString::number(time));
        } else if (time < 100) {
            sb.append("0");
            sb.append(QString::number(time));
        } else {
            sb.append(QString::number(time));
        }
        return sb;
    }

/**
 * Hashes the given string using the HMAC-SHA1 algorithm.
 *
 * \param key The string to be hashed
 * \param secret The string that contains secret word
 * \return The hashed string
 */
    QByteArray hmac_sha1(const QString &key, const QString &secret) {
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

    unsigned char toHex(unsigned char x) {
        return x > 9 ? x + 55 : x + 48;
    }

    std::string urlEncode(const std::string &str) {
        std::string strTemp = "";
        size_t length = str.length();
        for (size_t i = 0; i < length; i++) {
            if (isalnum((unsigned char) str[i]) ||
                (str[i] == '-') ||
                (str[i] == '_') ||
                (str[i] == '.') ||
                (str[i] == '~'))
                strTemp += str[i];
            else if (str[i] == ' ')
                strTemp += "+";
            else {
                strTemp += '%';
                strTemp += toHex((unsigned char) str[i] >> 4);
                strTemp += toHex((unsigned char) str[i] % 16);
            }
        }
        return strTemp;
    }

// 获取系统当前时间
    std::string getCurrentSystemTime() {
        std::time_t course_start_time1 = time(NULL);
        char buf[32];
        strftime(buf, sizeof(buf), "%FT%TZ", gmtime(&course_start_time1));
//    std::cout << buf << std::endl;
        return std::string(buf);
    }
}