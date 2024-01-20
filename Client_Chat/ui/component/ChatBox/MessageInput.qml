import QtQuick 2.0
import "../../component"

Item {
    id: root
    width: 1400
    height: 80
    Rectangle {
        id: box
        anchors.fill: parent
        radius: 50
        border.width: 2
        border.color: "#008896"
        opacity: 0.8
    }

    ButtonImage {
        id: record
        width: 48
        height: 48
        anchors {
            left: box.left
            leftMargin: 20
            verticalCenter: box.verticalCenter
        }
        scalePressed: 0.9
        source: CTRL.isRecording ? "qrc:/img/recording.png" : "qrc:/img/record.png"
    }

    TextInput {
        id: input
        font.pixelSize: 35
        width: parent.width - input.anchors.leftMargin - 40
        anchors {
            left: parent.left
            leftMargin: 90
            verticalCenter: parent.verticalCenter
        }
        clip: true
        Keys.onReturnPressed: {
            if(input.text != "") {
                CTRL.requestSendMessage(input.text)
                input.text = ""
            }
        }
    }

    Text {
        id: input_backup
        anchors.fill: input
        opacity: 0.7
        visible: input.text == ""
        font.pixelSize: 35
        text: "Aa"
    }
}
