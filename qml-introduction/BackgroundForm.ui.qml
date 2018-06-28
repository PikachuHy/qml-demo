import QtQuick 2.11

Item {
    width: 400
    height: 400

    Rectangle {
        id: rectangle
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#80d5f6"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }
        anchors.fill: parent
    }
}
