import QtQuick 2.0
import "../component/ChatBox"

Item {
    id: root
    anchors.fill: parent

    Item {
        id: title
        width: state.width + username.anchors.leftMargin + username.width
        height: 80
        anchors.horizontalCenter: parent.horizontalCenter
        Rectangle {
            id: state
            width: 20
            height: 20
            radius: 10
            anchors.verticalCenter: parent.verticalCenter
            color: CTRL.isConnected ? "#42f700" : "#999999"
        }
        Text {
            id: username
            anchors {
                left: state.right
                leftMargin: 15
                verticalCenter: parent.verticalCenter
            }
            font.pixelSize: 30
            font.bold: true
            text: CTRL.username
        }
    }

    MessageContent {
        id: content
        anchors.centerIn: parent
    }

    MessageInput {
        id: msg_input
        anchors {
            bottom: parent.bottom
            bottomMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
    }
}
