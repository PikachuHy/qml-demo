#ifndef SETTING_H
#define SETTING_H

#include <QObject>
#include <QColor>

class QSettings;
class Setting
{
public:
    Setting();
    void setKeyboardAudio(bool flag);
    bool keyboardAudio();
    void setCorrectCharColor(QColor color);
    QColor correctCharColor();
    void setWrongCharColor(QColor color);
    QColor wrongCharColor();
    void setUntypedCharColor(QColor color);
    QColor untypedCharColor();
private:
    QSettings *m_setting;
};

#endif // SETTING_H
