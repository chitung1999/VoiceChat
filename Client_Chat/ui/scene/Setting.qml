import QtQuick 2.0
import "../component"
import "../component/Setting"

Item {
    id: root
    anchors.fill: parent

    Rectangle {
        id: box_hide
        width: 1600
        height: 800
        anchors {
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: 40
            horizontalCenter: parent.horizontalCenter
        }
        color: "#fff"
        Rectangle {
            width: 300
            height: 800
            color: "#969696"
        }
        visible: false
    }

    BorderBase {
        id: box
        anchors.fill: box_hide
        source: box_hide
        borderWidth: 1
        opacity: 0.8
    }

    Text {
        id: title
        anchors {
            top: box.top
            topMargin: 30
            left: box.left
            leftMargin: 20
        }
        font.pixelSize: 30
        font.bold: true
        text: "Setting"
    }

    ListSetting {
        id: option
        anchors {
            top: title.bottom
            topMargin: 23
            left: box.left
        }
    }

    Content {
        id: content
        anchors {
            top: box.top
            right: box.right
        }
        state: option.state
    }
}
