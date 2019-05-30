#include "setting.h"
#include <QVariant>
#include <QSettings>
QString setting_key_keyboard_audio = "keyboard_audio";
QString setting_key_correct_char_color = "correct_char_color";
QString setting_key_wrong_char_color = "wrong_char_color";
QString setting_key_untyped_char_color = "untyped_char_color";
Setting::Setting()
{
    m_setting = new QSettings();
}

void Setting::setKeyboardAudio(bool flag)
{
    m_setting->setValue(setting_key_keyboard_audio, flag);
    m_setting->sync();
}

bool Setting::keyboardAudio()
{
    return m_setting->value(setting_key_keyboard_audio).toBool();
}

void Setting::setCorrectCharColor(QColor color)
{
    m_setting->setValue(setting_key_correct_char_color, QVariant(color.rgba()));
    m_setting->sync();
}

QColor Setting::correctCharColor()
{
    auto v = m_setting->value(setting_key_correct_char_color).toUInt();
    return v == 0 ? QColor(Qt::gray) : QColor::fromRgba(v);
}

void Setting::setWrongCharColor(QColor color)
{
    m_setting->setValue(setting_key_wrong_char_color, QVariant(color.rgba()));
    m_setting->sync();
}

QColor Setting::wrongCharColor()
{
    auto v = m_setting->value(setting_key_wrong_char_color).toUInt();
    return v == 0 ? QColor(Qt::red) : QColor::fromRgba(v);
}

void Setting::setUntypedCharColor(QColor color)
{
    m_setting->setValue(setting_key_untyped_char_color, QVariant(color.rgba()));
    m_setting->sync();
}

QColor Setting::untypedCharColor()
{
    auto v = m_setting->value(setting_key_untyped_char_color).toUInt();
    return v == 0 ? QColor(Qt::black) : QColor::fromRgba(v);
}
