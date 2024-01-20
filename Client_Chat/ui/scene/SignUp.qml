import QtQuick 2.0
import AppEnum 1.0
import "../component/Home"
import "../component"

Item {
    id: root

    Rectangle {
        id: box
        width: 1000
        height: 600
        radius: 30
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: 50
        }
        color: "#e4e4e4"
        opacity: 0.9
    }

    Rectangle {
        id: login_box
        width: 135
        height: login_box.width
        radius: login_box.width
        anchors {
            horizontalCenter: box.horizontalCenter
            top: box.top
            topMargin: - login_box.height / 2
        }
        color: "#fff"

        Image {
            id: login_icon
            anchors.centerIn: parent
            scale: 0.5
            source: "qrc:/img/login.png"
        }
    }

    LoginInput {
        id: username
        anchors {
            top: box.top
            topMargin: 100
            horizontalCenter: box.horizontalCenter
        }
        source: "qrc:/img/login_user.png"
        text_backup: "Username"
    }

    LoginInput {
        id: password
        anchors {
            top: username.bottom
            topMargin: 30
            horizontalCenter: username.horizontalCenter
        }
        isHideWord: true
        source: "qrc:/img/login_password.png"
        sourceHide: password.isHideWord ? "qrc:/img/login_hide.png" : "qrc:/img/login_show.png"
        text_backup: "Password"
    }

    LoginInput {
        id: re_password
        anchors {
            top: password.bottom
            topMargin: 30
            horizontalCenter: username.horizontalCenter
        }
        isHideWord: true
        source: "qrc:/img/login_password.png"
        sourceHide: password.isHideWord ? "qrc:/img/login_hide.png" : "qrc:/img/login_show.png"
        text_backup: "Re-enter Password"
    }

    ButtonText {
        id: cancel_button
        width: 250
        height: 70
        radius: 20
        anchors {
            top: re_password.bottom
            topMargin: 30
            left: username.left
        }
        color: "#999999"
        border.width: 0
        name: "Cancel"
        onClickButton: CTRL.requestScene(AppEnum.Home)
    }

    ButtonText {
        id: ok_button
        width: cancel_button.width
        height: cancel_button.height
        radius: cancel_button.radius
        anchors {
            bottom: cancel_button.bottom
            right: username.right
        }
        color: "#008896"
        border.width: 0
        name: "OK"
        onClickButton: CTRL.requestSignUp(username.textInput, password.textInput, re_password.textInput)
    }
}
