#include "client.h"

Client::Client() : socket{new QTcpSocket}
{
    connect(socket, &QIODevice::readyRead,
            this, &Client::receive);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &Client::error);
}

void Client::connectHost(QString name, QHostAddress address, quint16 port) {
    socket->connectToHost(address, port);
    socket->waitForConnected(10000);
    socket->write(name.toStdString().c_str());
}

void Client::receive() {
    QByteArray message = socket->readAll();
    QString smessage = QString::fromStdString(message.toStdString());
    emit receivedmsg(smessage);
}

void Client::sendMessage(QString message) {
    socket->write(message.toStdString().c_str());
}

void Client::error(QAbstractSocket::SocketError error) {
    std::cout << socket->errorString().toStdString()
              << std::endl;
}


