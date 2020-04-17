#include "server.h"

Server::Server(QObject * parent) : QTcpServer(parent),
    portnum{8074}, //default port
    handler{new ServerMessageHandler}
{
    connect(this, &QTcpServer::newConnection,
            this, &Server::addClients);
}

void Server::setPort(int port) {
    portnum = port;
}

int Server::port() {
    return portnum;
}

void Server::run() {
    listen(QHostAddress::AnyIPv4, portnum);
    consoleLog();
}

void Server::shutdown() {
    close();
    handler->shutdown();
}

void Server::incomingConnection(qintptr handle) {
    TcpConvenience * newconnection = new TcpConvenience;
    newconnection->setSocketDescriptor(handle);
    addPendingConnection(newconnection);
    emit newConnection();
}

void Server::addClients() {
    while (hasPendingConnections()) {
        TcpConvenience * newclient = static_cast<TcpConvenience *>(nextPendingConnection());
        //this subclass allows adding a name identifier to the client
        //cast works because we overrode incomingConnection


        //SORRY!!! but it only needs to do this once, on connect!
        connect(newclient, &QAbstractSocket::readyRead, this,
                [&, newclient]() {
        this->setName(newclient);
        handler->addClient(newclient);
        std::cout << "New connection from "
                  << newclient->peerAddress().toString().toStdString()
                  << std::endl;
        disconnect(newclient, nullptr, this, nullptr);
        });
    }
}

void Server::consoleLog() {
    //from https://doc.qt.io/qt-5/qtnetwork-fortuneserver-example.html
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    std::cout << "Listening on "
              << ipAddress.toStdString()
              << ": "
              << serverPort()
              << std::endl;
}

void Server::setName(TcpConvenience *newconnection) {
    QByteArray name = newconnection->readAll();
    QString QSName = QString::fromStdString(name.toStdString());

    newconnection->setName(QSName);
    connect(newconnection, &QIODevice::readyRead,
            handler,
            [&, newconnection](){handler->broadcast(newconnection);}
    );
}
