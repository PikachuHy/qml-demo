import QtQuick 2.11
Circle {
    id: receiveButton

    function receive(value){
        displayText = value
        clicknotify.running = true
    }

    SequentialAnimation on buttonColor {
        id: clicknotify
        running: false


        ColorAnimation {
            from: "red"
            to: "blue"
            duration: 500
        }

        ColorAnimation {
            from: "blue"
            to: "red"
            duration: 500
        }
    }
}
