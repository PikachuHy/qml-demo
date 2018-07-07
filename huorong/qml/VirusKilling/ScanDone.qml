import QtQuick 2.11
import controller 1.0
ScanDoneForm {
    doneButton.onClicked: {
        QmlController.stackView.pop()
    }
}
