import QtQuick 2.12
import QtQuick.Window 2.12
import "scene"
import "component"

Window {
    id: root
    visible: true
    visibility: Window.Maximized
    minimumWidth: 960
    minimumHeight: 500
    title: "VoiceChat"

    Item {
        width: 1920
        height: 1001
        anchors.centerIn: parent
        scale: parent.width / 1920

        Layout {
            id: layout
            anchors.fill: parent
        }

        Loader {
            id: content
            anchors.fill: parent
            source: CTRL.scene
        }

        MouseArea {
            id: lock_screen
            anchors.fill: parent
            enabled: popup.visible
        }

        PopupNotify {
            id: popup
            anchors.fill: parent
        }
    }
}
