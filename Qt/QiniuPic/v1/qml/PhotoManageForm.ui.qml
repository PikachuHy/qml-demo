import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtWebEngine 1.8
import QtWebView 1.1

Item {
    width: 400
    height: 400
    property alias webView: webView
    WebEngineView {
        id: webView
        anchors.fill: parent
    }
}
