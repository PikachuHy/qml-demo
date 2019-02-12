import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("rgb2hex")

    Pane {
        id: pane
        anchors.fill: parent


        Label {
            id: label
            text: qsTr("Label")
        }

        Grid {
            id: grid
            x: 21
            y: 22
            width: 238
            height: 151
            rows: 4
            spacing: 10
            columns: 2
            verticalItemAlignment: Grid.AlignVCenter
            Label{
                text: "R:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: r
                x: 136
                y: 224
                validator: IntValidator{bottom: 0;top:255}
                Keys.onPressed: {
                    if(event.key===Qt.Key_Enter || event.key === Qt.Key_Return){
                        g.focus = true
                        g.selectAll()
                    }
                }
                focus: true
            }
            Label{
                text: "G:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: g
                x: 136
                y: 224
                validator: IntValidator{bottom: 0;top:255}
                Keys.onPressed: {
                    if(event.key===Qt.Key_Enter || event.key === Qt.Key_Return){
                        b.focus = true
                        b.selectAll()
                    }
                }
            }
            Label{
                text: "B:"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: b
                x: 136
                y: 224
                validator: IntValidator{bottom: 0;top:255}
                Keys.onPressed: {
                    if(event.key===Qt.Key_Enter || event.key === Qt.Key_Return){
                        calDec2Hex()
                        result.selectAll()
                    }
                }
            }
            Label{
                text: "Result:"
            }
            TextField{
                id: result
            }
        }

        TextArea {
            id: textArea
            x: 36
            y: 206
            width: 533
            height: 235
        }

        Button {
            id: button
            x: 313
            y: 117
            text: qsTr("计算")
            onPressed: {
                calDec2Hex()
            }
        }

    }
    function toHex(dec){
        dec = parseInt(dec,10)
        var hex = dec.toString(16)
        if(hex.length===1){
            hex = "0"+hex
        }
        return hex
    }
    function calDec2Hex(){

        if(r.text!=="" && g.text!=="" && b.text!==""){
            var hex = "#" + toHex(r.text)+toHex(g.text)+toHex(b.text)
            result.text = hex
            var rgb = "RGB:("+r.text+","+g.text+","+b.text+")"
            textArea.append(rgb+" -> "+hex)
        }else{
            if(r.text===""){
                r.focus = true
            }else if(g.text===""){
                g.focus = true
            }else if(b.text===""){
                b.focus = true
            }
        }
        result.copy()
    }
}
