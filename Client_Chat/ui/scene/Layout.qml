import QtQuick 2.0
import "../component"
import AppEnum 1.0

Item {
    id: root

    Image {
        id: bg
        anchors.fill: parent
        source: (CTRL.background == "" ? "" : "file:///") + CTRL.background
    }

    Rectangle {
        id: task_bar
        width: parent.width
        height: 80
        opacity: 0.7
    }

    ButtonImage {
        id: setting
        anchors {
            right: task_bar.right
            rightMargin: 30
            verticalCenter: task_bar.verticalCenter
        }
        scale: 0.7
        opacity: 0.7
        source: "qrc:/img/setting.png"
        onClickButton: CTRL.requestScene(AppEnum.SETTING)
    }

    ButtonImage {
        id: connect
        anchors {
            right: task_bar.right
            rightMargin: 100
            verticalCenter: task_bar.verticalCenter
        }
        scale: 0.7
        opacity: 0.8
        source: CTRL.isConnected ? "qrc:/img/connected.png" : "qrc:/img/disconnected.png"
        onClickButton: CTRL.isConnected ? CTRL.disconnect() : CTRL.doConnect()
    }

    ButtonImage {
        id: home
        anchors {
            right: task_bar.right
            rightMargin: 170
            verticalCenter: task_bar.verticalCenter
        }
        scale: 0.7
        opacity: 0.8
        source: "qrc:/img/home.png"
        onClickButton: CTRL.requestScene(AppEnum.HOME)
    }
}
