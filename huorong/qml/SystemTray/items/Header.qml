import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3
HeaderForm {
    visible: false
    background.gradient: Gradient {
        GradientStop {
            position: 0
            color: Qt.darker("orange")
        }

        GradientStop {
            position: 0.905
            color: Qt.lighter("orange")
        }
    }
}
