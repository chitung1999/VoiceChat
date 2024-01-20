import QtQuick 2.0
import AppEnum 1.0

Item {
    id: root

    state: AppEnum.USERNAME

    ListModel {
        id: option

        ListElement {
            stateItem: AppEnum.USERNAME
            titleItem: qsTr("User Name")
            sourceItem: "qrc:/img/username.png"
        }
        ListElement {
            stateItem: AppEnum.CONNECT
            titleItem: qsTr("Connect")
            sourceItem: "qrc:/img/connect.png"
        }
        ListElement {
            stateItem: AppEnum.BACKGROUND
            titleItem: qsTr("BackGround")
            sourceItem: "qrc:/img/bg_icon.png"
        }
    }

    Column {
        Repeater {
            id: repeat
            model: option
            Rectangle {
                width: 300
                height: 80
                color: "transparent"
                Image {
                    width: 32
                    height: 32
                    anchors {
                        left: parent.left
                        leftMargin: 40
                        verticalCenter: parent.verticalCenter
                    }
                    source: sourceItem
                }
                Text {
                    anchors {
                        left: parent.left
                        leftMargin: 90
                        verticalCenter: parent.verticalCenter
                    }
                    font.pixelSize: 20
                    text: titleItem
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: parent.color = "#bcbcbc"
                    onExited:  parent.color = "transparent"
                    onClicked: root.state = stateItem
                }
            }
        }
    }

    Rectangle {
        id: choose
        y: choose.height * root.state
        width: 8
        height: 80
        color: "#008896"
    }
}
