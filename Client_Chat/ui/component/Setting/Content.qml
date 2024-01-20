import QtQuick 2.0
import AppEnum 1.0
import "../../component"

Item {
    id: root
    width: 1300
    height: 800

    TextInputBase {
        id: text_input1
        visible: true
        boxWidth: 250
        boxHeight: 60
        boxLeft: text_input1.textLeft + 20
        anchors {
            horizontalCenter: root.horizontalCenter
            verticalCenter: root.verticalCenter
        }
        onTextChanged: input1_request()
    }

    TextInputBase {
        id: text_input2
        visible: true
        boxWidth: 250
        boxHeight: 60
        boxLeft: text_input1.textLeft + 20
        anchors {
            verticalCenter: root.verticalCenter
            left: text_input1.left
        }
        onTextChanged: input2_request()
    }

    states: [
        State {
            name: AppEnum.USERNAME
            PropertyChanges {
                target: text_input1
                title: qsTr("User name")
                content: CTRL.username
            }
            PropertyChanges {target: text_input2; visible: false}
        },
        State {
            name: AppEnum.CONNECT
            PropertyChanges {
                target: text_input1
                anchors.verticalCenterOffset: -40
                title: qsTr("IP Adress Connect")
                content: CTRL.ipAddress
            }
            PropertyChanges {
                target: text_input2
                anchors.verticalCenterOffset: 40
                title: qsTr("Port")
                content: CTRL.port
            }
        },
        State {
            name: AppEnum.BACKGROUND
            PropertyChanges {
                target: text_input1
                anchors.horizontalCenterOffset: - 20
                title: qsTr("Path")
                boxWidth: root.width - text_input1.boxLeft - 160
                content: CTRL.background
            }
            PropertyChanges {target: text_input2; visible: false}
        }
    ]

    function input1_request() {
        switch(parseInt(root.state)) {
        case AppEnum.USERNAME:
            CTRL.changeUsername(text_input1.textInput)
            break
        case AppEnum.CONNECT:
            CTRL.changeIpAddress(text_input1.textInput)
            break
        case AppEnum.BACKGROUND:
            CTRL.changeBackground(text_input1.textInput)
            break
        default:
            break
        }
    }

    function input2_request() {
        switch(parseInt(root.state)) {
        case AppEnum.CONNECT:
            CTRL.changePort(text_input2.textInput)
            break
        default:
            break
        }
    }
}
