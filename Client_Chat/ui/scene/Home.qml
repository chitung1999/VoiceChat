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
            topMargin: 130
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

    ButtonText {
        id: login_button
        width: 300
        height: 100
        radius: 5
        anchors {
            top: password.bottom
            topMargin: 30
            horizontalCenter: username.horizontalCenter
        }
        color: "#008896"
        border.width: 0
        name: "Log In"
        onClickButton: CTRL.requestLogin(username.textInput, password.textInput)
    }

    Text {
        id: signup_question
        anchors {
            top: login_button.bottom
            topMargin: 20
            left: login_button.left
        }
        font.pixelSize: 25
        text: "No account?"
    }

    Text {
        id: signup
        anchors {
            top: login_button.bottom
            topMargin: 20
            left: signup_question.right
            leftMargin: 10
        }
        font.pixelSize: 25
        color: "#008896"
        text: "Create one!"

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: signup.opacity = 0.7
            onExited: signup.opacity = 1
            onClicked: CTRL.requestScene(AppEnum.SIGNUP)
        }
    }
}
