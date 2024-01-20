import QtQuick 2.0

Item {
    id: root

    height: name_id.height + box.height + 25
    width: parent.width
    state: root.isCurrentClient ? "CURRENT" : "OTHER"

    property string name
    property string message
    property bool isCurrentClient

    Text {
        id: name_id
        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 20
        }
        font.pixelSize: 15
        color: "#5f5f5f"
    }

    Rectangle {
        id: box
        width: message_id.width + 40
        height: message_id.height + 10
        anchors {
            top: name_id.bottom
            topMargin: 5
            left: parent.left
        }
        radius: 20
        Text {
            id: message_backup
            text: root.message
            font.pixelSize: 35
            visible: false
        }
        Text {
            id: message_id
            text: root.message
            width: message_backup.width > 800 ? 800 : message_backup.width
            wrapMode: Text.WordWrap
            anchors.centerIn: parent
            font.pixelSize: 35
        }
    }

    states: [
        State {
            name: "CURRENT"
            PropertyChanges {target: name_id; text:""; height: 0}
            PropertyChanges {target: box; anchors.leftMargin: root.width - box.width - 30; color: "#5ca5d1"}
            PropertyChanges {target: message_id; color: "#000"}
        },
        State {
            name: "OTHER"
            PropertyChanges {target: name_id; text: root.name}
            PropertyChanges {target: box; anchors.leftMargin: 30; color: "#eeeeee"}
            PropertyChanges {target: message_id; color: "#000"}
        }
    ]
}
