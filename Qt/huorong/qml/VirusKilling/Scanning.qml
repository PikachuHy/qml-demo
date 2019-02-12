import QtQuick 2.11
import "../controller"
import controller 1.0
ScanningForm {
    stopButton.onClicked: {
        QmlController.stackView.pop()
        QmlController.stackView.push("ScanDone.qml")
        QmlController.header.title = "扫描已完成"
    }
    pauseButton.onClicked: {
        pauseButton.checked=!pauseButton.checked
        pauseButton.text = pauseButton.checked?"继续":"暂停"
    }
    normalButton.onClicked: {
        updateChecked()
    }
    normalButton.onCheckedChanged: {
        updateButton()
    }
    highSpeedButton.onClicked: {
        updateChecked()
    }
    highSpeedButton.onCheckedChanged: {
        updateButton()
    }
    function updateChecked(){
        if(!normalButton.checked){
            normalButton.checked = true;
            highSpeedButton.checked = false
        }else if(!highSpeedButton.checked){
            normalButton.checked = false;
            highSpeedButton.checked = true
        }
    }

    function updateButton(){
        normalButton.backgroundColor = normalButton.checked?"#bda184":"white"
        normalButton.textColor = !normalButton.checked?"#bda184":"white"
        highSpeedButton.backgroundColor = highSpeedButton.checked?"#bda184":"white"
        highSpeedButton.textColor = !highSpeedButton.checked?"#bda184":"white"
    }
}
