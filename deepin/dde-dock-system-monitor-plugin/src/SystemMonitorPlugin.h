//
// Created by pikachu on 7/20/19.
//

#ifndef DDE_DOCK_SYSTEM_MONITER_PLUGIN_SYSTEMMONITORPLUGIN_H
#define DDE_DOCK_SYSTEM_MONITER_PLUGIN_SYSTEMMONITORPLUGIN_H
#include <dde-dock/pluginsiteminterface.h>

#include <QObject>
class QWidget;
class QTimer;
class QLabel;
class SystemMonitorPlugin: public QObject, PluginsItemInterface {
Q_OBJECT
    // 声明实现了的接口
    Q_INTERFACES(PluginsItemInterface)
    // 插件元数据
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "system-monitor.json")
public:
    // 返回插件的名称，必须是唯一值，不可以和其它插件冲突
    const QString pluginName() const override;

    // 插件初始化函数
    void init(PluginProxyInterface *proxyInter) override;

    // 返回插件的 widget
    QWidget *itemWidget(const QString &itemKey) override;

    bool pluginIsAllowDisable() override;

    bool pluginIsDisable() override;

    void pluginStateSwitched() override;

    const QString pluginDisplayName() const override;

    QWidget *itemTipsWidget(const QString &itemKey) override;

private:
    const QString itemCommand(const QString &itemKey) override;

    void displayModeChanged(const Dock::DisplayMode displayMode) override;

private:
    QWidget *m_widget;
    QLabel *m_tipsWidget;
    PluginProxyInterface *m_proxyInter;
};


#endif //DDE_DOCK_SYSTEM_MONITER_PLUGIN_SYSTEMMONITORPLUGIN_H
