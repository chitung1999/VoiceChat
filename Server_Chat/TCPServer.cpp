#include "TCPServer.h"

TCPServer::TCPServer(QObject *parent) : QObject(parent)
{
    m_server = new QTcpServer();
}

TCPServer::~TCPServer()
{
    foreach (QTcpSocket* socket, m_listSocket)
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    m_server->deleteLater();
}

void TCPServer::newConnection()
{
    while (m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());
}

void TCPServer::appendToSocketList(QTcpSocket* socket)
{
    m_listSocket.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &TCPServer::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &TCPServer::socketDisconnect);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    qInfo()<<"New connected with IP: " << socket->peerAddress().toString() << "- Port: " << socket->peerPort();
}

void TCPServer::readSocket()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    QDataStream data(socket);
    QByteArray dataBytes;
    data >> dataBytes;

    QJsonDocument jData = QJsonDocument::fromJson(dataBytes);
    QJsonObject objData = jData.object();
    switch (objData["type"].toInt()) {
    case DATATYPE::REQUEST_LOGIN:
        emit requestLogin(objData);
        break;
    case DATATYPE::REQUEST_SIGNUP:
        emit requestSignUp(objData);
        break;
    case DATATYPE::MESSAGE:
        foreach (QTcpSocket *client_socket, m_listSocket) {
            if (client_socket != sender()) {
                QDataStream sendData(client_socket);
                sendData << dataBytes;
            }
        }
        break;
    default:
        break;
    }
}

void TCPServer::socketDisconnect()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QSet<QTcpSocket*>::iterator it = m_listSocket.find(socket);
    if (it != m_listSocket.end()){
        qDebug() <<"A client has been disconnected with IP: " << socket->peerAddress().toString() << " - Port: " << socket->peerPort();
        m_listSocket.remove(*it);
    }

    socket->deleteLater();
}

void TCPServer::socketError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found. Please check the host name and port settings.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.";
        break;
    default:
        QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
        qDebug() << "The following error occurred: " << socket->errorString();
        break;
    }
}

void TCPServer::doConnect(QString ip, int port)
{
    if(port == 0)
        return;

    if(m_server->listen(QHostAddress::Any, port))
    {
        connect(m_server, &QTcpServer::newConnection, this, &TCPServer::newConnection);
        emit connectCompleted(true);
        qDebug() << "Server started! IP: " << ip <<  "- Port: " << port;
    }
    else
    {
        qDebug() << "Unable to start the server: " << m_server->errorString();
    }
}

void TCPServer::disconnect()
{
    if (!m_server->isListening())
        return;

    foreach (QTcpSocket* socket, m_listSocket)
    {
        socket->close();
        socket->deleteLater();
    }
    m_server->close();
    emit connectCompleted(false);
}

void TCPServer::sendDatatoOther(QJsonDocument data)
{
    foreach (QTcpSocket *client_socket, m_listSocket) {
        if (client_socket != sender()) {
            QDataStream sendData(client_socket);
            sendData << data;
        }
    }
}

void TCPServer::sendDatatoSender(QJsonDocument data)
{
    foreach (QTcpSocket *client_socket, m_listSocket) {
        if (client_socket == sender()) {
            QDataStream sendData(client_socket);
            sendData << data;
        }
    }
}
