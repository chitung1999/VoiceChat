#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "TCPServer.h"
#include "FileControl.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)
public:
    static Controller *getInstance();
    void initialize();

    bool isConnected() const;
    void setIsConnected(bool newIsConnect);

signals:
    void isConnectedChanged();

public slots:
    void onConnectCompleted(bool isConnect);
    void onRequestLogin(QJsonObject data);
    void onRequestSignUp(QJsonObject data);

    QString hostAddress();
    void doConnect(int port);
    void disconnect();

private:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    TCPServer *m_TCPServer;
    QJsonArray m_dataJson;
    QMap<QString, QString> m_account;
    QString m_ipAddress;

    bool m_isConnected;
};

#endif // CONTROLLER_H
