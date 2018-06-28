import QtQuick 2.11
import QtQuick.Dialogs 1.2
Page3Form {
    comboBox.model: ["Dog", "Fish", "Cat", "Bird"]
    button.onClicked: {
        var msg = "Ordering: " + textField.text + "\r\n"
        msg = msg + "Your " + Math.round(dial.value) + " years old " + comboBox.currentText
        messageDialog.text = msg
        messageDialog.open()
    }
    dial.onValueChanged: {
        progressBar.value = dial.value
        label1.text = Math.round(progressBar.value) + " years old"
    }
    MessageDialog{
        id: messageDialog
        title: qsTr("Hello World")
        text: ""
        onAccepted: Qt.quit()
    }
}
