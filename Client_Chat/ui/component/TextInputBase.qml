import QtQuick 2.0

Item {
    id: root
    height: box.height
    width: title.width + box.width
    property string title
    property string content
    property alias textInput: username.text
    property alias textLeft: title.width
    property int fontSize: 30
    property int boxWidth
    property int boxHeight
    property int boxLeft

    signal textChanged()

    Text {
        id: title
        text: root.title
        font.pixelSize: root.fontSize
        font.bold: true
    }

    Rectangle {
        id: box
        width: root.boxWidth
        height: root.boxHeight
        radius: 10
        anchors {
            verticalCenter: title.verticalCenter
            left: parent.left
            leftMargin: root.boxLeft
        }
        border.color: "#000"
        border.width: 2

        TextInput {
            id: username
            font.pixelSize: root.fontSize
            width: parent.width - 30
            anchors.centerIn: parent
            text: root.content
            focus: false
            clip: true
        }

        ButtonImage {
            id: done
            anchors {
                verticalCenter: username.verticalCenter
                left: username.right
                leftMargin: 30
            }
            visible: username.focus
            source: "qrc:/img/ok.png"
            onClickButton: {
                if (username.focus) {
                    username.focus = false
                    root.textChanged()
                }
            }
        }

        Keys.onReturnPressed: {
            if (username.focus) {
                username.focus = false
                root.textChanged()
            }
        }
    }
}
