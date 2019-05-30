#include "util.h"
#include <QCryptographicHash>
#include "qiniu_global.h"
QINIU_BEGIN_NAMESPACE
namespace Util {

    QByteArray hmacSha1(QByteArray baseString, QByteArray key) {
     int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
     if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
      key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
     }

     QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char "6"
     QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char "quot;
     // ascii characters 0x36 ("6") and 0x5c ("quot;) are selected because they have large
     // Hamming distance (http://en.wikipedia.org/wiki/Hamming_distance)

     for (int i = 0; i < key.length(); i++) {
      innerPadding[i] =
              innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
      outerPadding[i] =
              outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
     }

// result = hash ( outerPadding CONCAT hash ( innerPadding CONCAT baseString ) ).toBase64
     QByteArray total = outerPadding;
     QByteArray part = innerPadding;
     part.append(baseString);
     total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
     QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
     return hashed.toBase64();
    }
}
QINIU_END_NAMESPACE
