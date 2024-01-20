#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGuiApplication>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <QDir>
#include "common/AppEnum.h"
#include "common/Define.h"
#include "common/FileControl.h"
#include "common/TCPClient.h"
#include "model/MessageModel.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString scene        READ scene          WRITE setScene          NOTIFY sceneChanged)
    Q_PROPERTY(QString background   READ background     WRITE setBackground     NOTIFY backgroundChanged)
    Q_PROPERTY(QString username     READ username       WRITE setUsername       NOTIFY usernameChanged)
    Q_PROPERTY(QString ipAddress    READ ipAddress      WRITE setIpAddress      NOTIFY ipAddressChanged)
    Q_PROPERTY(QString popupNotify  READ popupNotify    WRITE setPopupNotify    NOTIFY popupNotifyChanged)
    Q_PROPERTY(int port             READ port           WRITE setPort           NOTIFY portChanged)
    Q_PROPERTY(bool isConnected     READ isConnected    WRITE setIsConnected    NOTIFY isConnectedChanged)
    Q_PROPERTY(bool isLogin         READ isLogin        WRITE setIsLogin        NOTIFY isLoginChanged)
    Q_PROPERTY(bool isRecording     READ isRecording    WRITE setIsRecording    NOTIFY isRecordingChanged)
public:
    static Controller *getInstance();
    void initialize();

    QString scene() const;
    void setScene(QString newScene);

    const QString &background() const;
    void setBackground(const QString &newBackground);

    const QString &username() const;
    void setUsername(const QString &newUsername);

    const QString &ipAddress() const;
    void setIpAddress(const QString &newIpAddress);

    const QString &popupNotify() const;
    void setPopupNotify(const QString &newPopupNotify);

    const int &port() const;
    void setPort(const int &newPort);

    const bool &isConnected() const;
    void setIsConnected(const bool &newIsConnected);

    const bool &isLogin() const;
    void setIsLogin(const bool &newIsLogin);

    const bool &isRecording() const;
    void setIsRecording(const bool &newIsRecording);

    MessageModel *message();

signals:
    void sceneChanged();
    void backgroundChanged();
    void usernameChanged();
    void ipAddressChanged();
    void popupNotifyChanged();
    void portChanged();
    void isConnectedChanged();
    void isLoginChanged();
    void isRecordingChanged();

    //request to TCPClient
    void requestConnect(QString ip, int port);
    void requestDisconnect();
    void requestSendData(QJsonDocument data);

public slots:
    void requestScene(int state);
    void requestSendMessage(QString message);

    void changeBackground(QString path);
    void changeUsername(QString username);
    void changeIpAddress(QString ip);
    void changePort(int port);

    void doConnect();
    void disconnect();

    void requestLogin(QString username, QString password);
    void requestSignUp(QString username, QString password, QString re_password);

    //receive from TCPClient
    void receiveData(QJsonDocument data);
    void receiveNotify(QString ntf);
    void onConnectCompleted(bool isConnect);

private:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    MessageModel m_message;
    TCPClient *m_TCPClient;
    QThread *m_thread;
    QJsonObject m_dataJson;
    QString m_scene;
    QString m_background;
    QString m_username;
    QString m_ipAddress;
    QString m_popupNotify;
    int m_port;
    bool m_isConnected;
    bool m_isLogin;
    bool m_isRecording;
};

#endif // CONTROLLER_H
