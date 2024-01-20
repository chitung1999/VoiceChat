#include "Controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    initialize();

    m_TCPClient = new TCPClient();
    m_thread = new QThread(this);
    m_TCPClient->moveToThread(m_thread);

    //request to TCPClient
    connect(this, &Controller::requestConnect, m_TCPClient, &TCPClient::doConnect);
    connect(this, &Controller::requestDisconnect, m_TCPClient, &TCPClient::disconnect);
    connect(this, &Controller::requestSendData, m_TCPClient, &TCPClient::sendData);

    //receive from TCPClient
    connect(m_TCPClient, &TCPClient::receiveData, this, &Controller::receiveData);
    connect(m_TCPClient, &TCPClient::sendNtfUI, this, &Controller::receiveNotify);
    connect(m_TCPClient, &TCPClient::connectCompleted, this, &Controller::onConnectCompleted);

    m_thread->start();
}

Controller::~Controller()
{
    if (m_TCPClient) {
        delete m_TCPClient;
        m_TCPClient = nullptr;
    }

    m_thread->quit();
    m_thread->wait();
}

Controller *Controller::getInstance()
{
    static Controller _self;
    return &_self;
}

void Controller::initialize()
{
    m_isConnected = false;
    m_isLogin = false;

    m_scene = "qrc:/ui/scene/Home.qml";
    m_ipAddress = IP_ADDRESS;
    m_port = PORT_CONENCT;
    m_username = "Admin";


    if(!FileControl::readFile(PATH_DATA + QString("/config.json"), m_dataJson))
        return;

    if (!m_dataJson.value("IPAddress").toString().isEmpty())
        m_ipAddress = m_dataJson.value("IPAddress").toString();

    if (!m_dataJson.value("name").toString().isEmpty())
        m_username = m_dataJson.value("name").toString();

    if (!m_dataJson.value("port").isUndefined())
        m_port = m_dataJson.value("port").toInt();

    QString path = m_dataJson.value("background").toString();
    if (!path.isEmpty() && FileControl::checkFileImg(path))
        m_background = path;
}

QString Controller::scene() const
{
    return m_scene;
}

void Controller::setScene(QString newScene)
{
    if (m_scene == newScene)
        return;
    m_scene = newScene;
    emit sceneChanged();
}

const QString &Controller::background() const
{
    return m_background;
}

void Controller::setBackground(const QString &newBackground)
{
    if (m_background == newBackground)
        return;
    m_background = newBackground;
    emit backgroundChanged();
}

const QString &Controller::username() const
{
    return m_username;
}

void Controller::setUsername(const QString &newUsername)
{
    if(m_username == newUsername)
        return;
    m_username = newUsername;
    emit usernameChanged();
}

const QString &Controller::ipAddress() const
{
    return m_ipAddress;
}

void Controller::setIpAddress(const QString &newIpAddress)
{
    if(m_ipAddress == newIpAddress)
        return;
    m_ipAddress = newIpAddress;
    emit ipAddressChanged();
}

const QString &Controller::popupNotify() const
{
    return m_popupNotify;
}

void Controller::setPopupNotify(const QString &newPopupNotify)
{
    m_popupNotify = newPopupNotify;
    emit popupNotifyChanged();
}

const int &Controller::port() const
{
    return m_port;
}

void Controller::setPort(const int &newPort)
{
    if(m_port == newPort)
        return;
    m_port = newPort;
    emit portChanged();
}

const bool &Controller::isConnected() const
{
    return m_isConnected;
}

void Controller::setIsConnected(const bool &newIsConnected)
{
    if(m_isConnected == newIsConnected)
        return;
    m_isConnected = newIsConnected;
    emit isConnectedChanged();
}

const bool &Controller::isLogin() const
{
    return m_isLogin;
}

void Controller::setIsLogin(const bool &newIsLogin)
{
    if(m_isLogin == newIsLogin)
        return;
    m_isLogin = newIsLogin;
    emit isLoginChanged();
}

const bool &Controller::isRecording() const
{
    return m_isRecording;
}

void Controller::setIsRecording(const bool &newIsRecording)
{
    if(m_isRecording == newIsRecording)
        return;
    m_isRecording = newIsRecording;
    emit isRecordingChanged();
}

MessageModel *Controller::message()
{
    return &m_message;
}

void Controller::requestScene(int state)
{
    QString scene;
    switch (state) {
    case AppEnum::APP::HOME:
        if (m_isLogin) {
            scene = "qrc:/ui/scene/ChatBox.qml";
        } else {
            scene = "qrc:/ui/scene/Home.qml";
        }
        break;
    case AppEnum::APP::SETTING:
        scene = "qrc:/ui/scene/Setting.qml";
        break;
    case AppEnum::APP::SIGNUP:
        scene = "qrc:/ui/scene/SignUp.qml";
        break;
    default:
        scene = "qrc:/ui/scene/Home.qml";
        break;
    }
    setScene(scene);
}

void Controller::changeBackground(QString path)
{
    if(!FileControl::checkFileImg(path)) {
        setPopupNotify("Cann't open file: " + path);
        return;
    }

    m_dataJson["background"] = path;
    FileControl::writeFileJson(PATH_DATA + QString("/config.json"), m_dataJson);
    setBackground(path);
}

void Controller::changeUsername(QString username)
{
    m_dataJson["name"] = username;
    FileControl::writeFileJson(PATH_DATA + QString("/config.json"), m_dataJson);
    setUsername(username);
}

void Controller::changeIpAddress(QString ip)
{
    m_dataJson["IPAddress"] = ip;
    FileControl::writeFileJson(PATH_DATA + QString("/config.json"), m_dataJson);
    setIpAddress(ip);
}

void Controller::changePort(int port)
{
    m_dataJson["port"] = port;
    FileControl::writeFileJson(PATH_DATA + QString("/config.json"), m_dataJson);
    setPort(port);
}

void Controller::doConnect()
{
    emit requestConnect(m_ipAddress, m_port);
}

void Controller::disconnect()
{
    emit requestDisconnect();
}

void Controller::requestSendMessage(QString message)
{
    if (!m_isConnected) {
        setPopupNotify("You are offline!");
        return;
    }

    QJsonObject data;
    data["type"] = AppEnum::MESSAGE;
    data["username"] = m_username;
    data["message"] = message;
    QJsonDocument jdata(data);
    emit requestSendData(jdata);

    MessageItem item(m_username, message, true);
        m_message.append(item);
}

void Controller::requestLogin(QString username, QString password)
{
    if(!m_isConnected) {
        setPopupNotify("You are offline!");
        return;
    }

    if(username.isEmpty() || password.isEmpty()) {
        setPopupNotify("Username or Password is invalid!");
        return;
    }

    QJsonObject data;
    data["type"] = AppEnum::REQUEST_LOGIN;
    data["username"] = username;
    data["password"] = password;
    QJsonDocument jdata(data);
    emit requestSendData(jdata);
}

void Controller::requestSignUp(QString username, QString password, QString re_password)
{
    if(!m_isConnected) {
        setPopupNotify("You are offline!");
        return;
    }

    if(username.isEmpty() || password.isEmpty() || re_password.isEmpty()) {
        setPopupNotify("Username or Password is invalid!");
        return;
    }

    if(password != re_password) {
        setPopupNotify("Re-enter the password does not match!");
        return;
    }

    QJsonObject data;
    data["type"] = AppEnum::REQUEST_SIGNUP;
    data["username"] = username;
    data["password"] = password;
    QJsonDocument jdata(data);
    emit requestSendData(jdata);
}

void Controller::receiveData(QJsonDocument data)
{
    QJsonObject objData = data.object();
    switch (objData["type"].toInt()) {
    case AppEnum::DATATYPE::RESULT_LOGIN:
        if(objData["result"].toBool()) {
            setIsLogin(true);
            requestScene(AppEnum::APP::HOME);
        } else {
            setPopupNotify("Username or Password is invalid!");
        }
        break;
    case AppEnum::DATATYPE::RESULT_SIGNUP:
        if(objData["result"].toBool()) {
            setPopupNotify("Account successfully created!");
            setIsLogin(true);
            requestScene(AppEnum::APP::HOME);
        } else {
            setPopupNotify("This username already exists!");
        }
        break;
    case AppEnum::DATATYPE::MESSAGE:
        m_message.append(MessageItem(objData["username"].toString(), objData["message"].toString(), false));
        break;
    default:
        break;
    }
}

void Controller::receiveNotify(QString ntf)
{
    setPopupNotify(ntf);
}

void Controller::onConnectCompleted(bool isConnect)
{
    setIsConnected(isConnect);
}
