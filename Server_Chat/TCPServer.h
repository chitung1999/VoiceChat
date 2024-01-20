#ifndef TCPCTRL_H
#define TCPCTRL_H

#include <QObject>
#include <QDataStream>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

enum DATATYPE {
    REQUEST_LOGIN,
    RESULT_LOGIN,
    REQUEST_SIGNUP,
    RESULT_SIGNUP,
    MESSAGE
};

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);
    ~TCPServer();

    void doConnect(QString ip, int port);
    void disconnect();
    void sendDatatoSender(QJsonDocument data);
    void sendDatatoOther(QJsonDocument data);

signals:
    void connectCompleted(bool isConnect);
    void requestLogin(QJsonObject account);
    void requestSignUp(QJsonObject account);

private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void socketDisconnect();
    void socketError(QAbstractSocket::SocketError socketError);

private:
    QTcpServer* m_server;
    QSet<QTcpSocket*> m_listSocket;
};

#endif // TCPCTRL_H
