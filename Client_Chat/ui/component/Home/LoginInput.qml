import QtQuick 2.0
import "../../component"

Rectangle {
    id: root
    width: 700
    height: 100
    radius: 20

    property string source
    property string text_backup
    property string sourceHide
    property bool isHideWord: false
    property alias textInput: text_input.text

    Image {
        id: img
        source: root.source
        opacity: 0.6
        anchors {
            left: parent.left
            leftMargin: 30
            verticalCenter: parent.verticalCenter
        }
    }


    ButtonImage {
        id: button_hide
        source: root.sourceHide
        opacity: 0.6
        anchors {
            right: parent.right
            rightMargin: 20
            verticalCenter: parent.verticalCenter
        }
        onClickButton: root.isHideWord  = !root.isHideWord
    }

    Text {
        id: text_backup
        width: text_input.width
        font.pixelSize: text_input.font.pixelSize
        anchors {
            top: text_input.top
            left: text_input.left
        }
        opacity: 0.6
        visible: text_input.text == ""
        text: root.text_backup
    }

    TextInput {
        id: text_input
        width: parent.width - text_input.anchors.leftMargin - button_hide.anchors.rightMargin * 2 - button_hide.width
        font.pixelSize: 35
        clip: true
        anchors {
            left: parent.left
            leftMargin: 90
            verticalCenter: parent.verticalCenter
        }
        echoMode: root.isHideWord ? TextInput.Password : TextInput.Normal
    }
}
