#include "Controller.h"

//#define PATH_DATA "/home/cockpit2024/Documents/VoiceChat/Server_Chat/data.json"
#define PATH_DATA "C:/Users/PVD/Desktop/Project/VoiceChat/Server_Chat/data.json"

Controller::Controller(QObject *parent) : QObject(parent)
{
    initialize();

    m_TCPServer = new TCPServer();
    connect(m_TCPServer, &TCPServer::connectCompleted, this, &Controller::onConnectCompleted);
    connect(m_TCPServer, &TCPServer::requestLogin, this, &Controller::onRequestLogin);
    connect(m_TCPServer, &TCPServer::requestSignUp, this, &Controller::onRequestSignUp);
}

Controller::~Controller()
{
    if (m_TCPServer) {
        delete m_TCPServer;
        m_TCPServer = nullptr;
    }
}

Controller *Controller::getInstance()
{
    static Controller _self;
    return &_self;
}

void Controller::initialize()
{
    m_isConnected = false;

    if(!FileControl::readFile(PATH_DATA, m_dataJson))
        return;

    foreach(QJsonValue value, m_dataJson)
        m_account[value.toObject()["username"].toString()] = value.toObject()["password"].toString();

    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
            m_ipAddress = address.toString();
        }
    }
}

bool Controller::isConnected() const
{
    return m_isConnected;
}

void Controller::setIsConnected(bool newIsConnect)
{
    if (m_isConnected == newIsConnect)
        return;
    m_isConnected = newIsConnect;
    emit isConnectedChanged();
}

void Controller::onConnectCompleted(bool isConnect)
{
    setIsConnected(isConnect);
}

void Controller::onRequestLogin(QJsonObject data)
{
    bool ret = false;
    if(m_account.contains(data["username"].toString()))
        if (m_account[data["username"].toString()] == data["password"].toString()) {
            ret = true;
        }
    QJsonObject retObj;
    retObj["type"] = DATATYPE::RESULT_LOGIN;
    retObj["result"] = ret;
    QJsonDocument jdata(retObj);
    m_TCPServer->sendDatatoSender(jdata);
}

void Controller::onRequestSignUp(QJsonObject data)
{
    bool ret = false;
    if(!m_account.contains(data["username"].toString())) {
        ret = true;
        QString username = data["username"].toString();
        QString password = data["password"].toString();
        m_account[username] = password;

        QJsonObject account;
        account["username"] = username;
        account["password"] = password;
        m_dataJson.append(account);
        FileControl::writeFileJson(PATH_DATA, m_dataJson);
    }

    QJsonObject retObj;
    retObj["type"] = DATATYPE::RESULT_SIGNUP;
    retObj["result"] = ret;
    QJsonDocument jdata(retObj);
    m_TCPServer->sendDatatoSender(jdata);
}

QString Controller::hostAddress()
{
    return m_ipAddress;
}

void Controller::doConnect(int port)
{
    m_TCPServer->doConnect(m_ipAddress, port);
}

void Controller::disconnect()
{
    m_TCPServer->disconnect();
}
