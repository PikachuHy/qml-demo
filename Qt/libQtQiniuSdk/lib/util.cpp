#include "util.h"
#include <QCryptographicHash>
#include "qiniu_global.h"
QINIU_BEGIN_NAMESPACE
namespace Util {

/**
 * Hashes the given string using the HMAC-SHA1 algorithm.
 *
 * \param key The string to be hashed
 * \param secret The string that contains secret word
 * \return The hashed string
 */
    QByteArray hmacSha1(const QString &key, const QString &secret) {
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

    QString urlSafe(QString s) {
        while (s.contains("+")) {
            s = s.replace("+", "-");
        }
        while (s.contains("/")) {
            s = s.replace("/", "_");
        }
        return s;
    }
}
QINIU_END_NAMESPACE
