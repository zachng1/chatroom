#include "client.h"

Client::Client() : socket{new QTcpSocket}
{
    connect(socket, &QIODevice::readyRead,
            this, &Client::receive);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &Client::error);
    connect(socket, &QAbstractSocket::disconnected, this, &Client::disconnected);

}

void Client::connectHost(QString name, QHostAddress address, quint16 port) {
    socket->connectToHost(address, port);

    //need to fix this
    connect(socket, &QTcpSocket::connected, this, [&, name](){
        this->socket->write(name.toStdString().c_str());
        emit connected();
    });
}

void Client::receive() {
    QByteArray message = socket->readAll();
    QString smessage = QString::fromStdString(message.toStdString());
    emit receivedmsg(smessage);
}

void Client::sendMessage(QString message) {
    if (message.contains('\x1b')) {
        emit errInvalid();
        return;
    }
    socket->write(message.toStdString().c_str());
}

void Client::error(QAbstractSocket::SocketError error) {
    std::cout << socket->errorString().toStdString()
              << std::endl;
    socket->disconnectFromHost();
}

void Client::shutdown() {
    socket->write("\x1b");
    socket->disconnectFromHost();
}


