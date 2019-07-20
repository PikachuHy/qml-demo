//
// Created by pikachu on 7/20/19.
//

#include "SystemMonitorPlugin.h"
#include "SystemMonitorWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
const QString SystemMonitorPlugin::pluginName() const {
    return QString("System Monitor");
}

void SystemMonitorPlugin::init(PluginProxyInterface *proxyInter) {
    qDebug() << "init System Monitor Plugin";
    m_proxyInter = proxyInter;
    m_widget = new SystemMonitorWidget();
    m_tipsWidget = new QLabel();
    if (displayMode() == Dock::Efficient) {
        // 如果插件没有被禁用则在初始化插件时才添加主控件到面板上
        if (!pluginIsDisable()) {
            m_proxyInter->itemAdded(this, pluginName());
        }
    }
}

QWidget *SystemMonitorPlugin::itemWidget(const QString &itemKey) {
    return m_widget;
}

bool SystemMonitorPlugin::pluginIsAllowDisable() {
    // 告诉 dde-dock 本插件允许禁用
    return true;
}

bool SystemMonitorPlugin::pluginIsDisable() {
    // 第二个参数 “disabled” 表示存储这个值的键（所有配置都是以键值对的方式存储的）
    // 第三个参数表示默认值，即默认不禁用
    return m_proxyInter->getValue(this, "disabled", false).toBool();
}

void SystemMonitorPlugin::pluginStateSwitched() {
    // 获取当前禁用状态的反值作为新的状态值
    const bool disabledNew = !pluginIsDisable();
    // 存储新的状态值
    m_proxyInter->saveValue(this, "disabled", disabledNew);
    if (displayMode() == Dock::Efficient) {
        // 根据新的禁用状态值处理主控件的加载和卸载
        if (disabledNew) {
            m_proxyInter->itemRemoved(this, pluginName());
        } else {
            m_proxyInter->itemAdded(this, pluginName());
        }
    }
}

const QString SystemMonitorPlugin::pluginDisplayName() const {
    return tr("System Monitor");
}

QWidget *SystemMonitorPlugin::itemTipsWidget(const QString &itemKey) {
    m_tipsWidget->setText("System Monitor v1.0.0");
    return m_tipsWidget;
}

const QString SystemMonitorPlugin::itemCommand(const QString &itemKey) {
    qDebug() << "item command";
    return "deepin-system-monitor";
}

void SystemMonitorPlugin::displayModeChanged(const Dock::DisplayMode displayMode) {
    if (displayMode == Dock::DisplayMode::Fashion) {
        m_proxyInter->itemRemoved(this, pluginName());
    } else {
        m_proxyInter->itemAdded(this, pluginName());
    }
}
