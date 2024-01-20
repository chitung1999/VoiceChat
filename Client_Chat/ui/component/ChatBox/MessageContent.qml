import QtQuick 2.0
import QtQuick.Controls 2.14

Item {
    id: root
    width: 1800
    height: 750

    Rectangle {
        id: box
        anchors.fill: parent
        radius: 30
        border.width: 2
        border.color: "#008896"
        opacity: 0.8
    }

    ListView {
        id: msg
        anchors.fill: box
        clip: true
        currentIndex: LISTMSG.length - 1
        model: LISTMSG
        delegate: MessageItem {
            isCurrentClient: model.isCurrentClient
            name: model.name
            message: model.message
        }

        ScrollBar.vertical: ScrollBar {
            anchors {
                right: parent.right
                rightMargin: 10
            }
            background: Rectangle {
                implicitWidth: 10
                color: "transparent"
            }
            contentItem: Rectangle {
                implicitWidth: 10
                radius: 5
                color: "gray"
            }
        }
    }
}
