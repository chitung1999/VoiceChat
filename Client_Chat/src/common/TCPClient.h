#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonDocument>
#include <QDebug>

class TCPClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPClient(QObject *parent = nullptr);
    ~TCPClient();

    QTcpSocket *getSocket();

signals:
    void receiveData(QJsonDocument data);
    void sendNtfUI(QString ntf);
    void connectCompleted(bool isConnect);

public slots:
    void readSocket();
    void socketDisconnect();
    void socketError(QAbstractSocket::SocketError socketError);

    //receive slots from VoiceChat
    void doConnect(QString ip, int port);
    void disconnect();
    void sendData(QJsonDocument data);

private:
    QTcpSocket* m_socket;
};

#endif // TCPCLIENT_H
