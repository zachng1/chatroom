#include "servermessagehandler.h"

ServerMessageHandler::ServerMessageHandler() : QObject(),
    clients{new QList<TcpConvenience *>}
{
}

void ServerMessageHandler::addClient(TcpConvenience *newclient) {
    clients->push_back(newclient);
}

void ServerMessageHandler::broadcast(TcpConvenience *sender) {
    QByteArray data = sender->readAll();
    if (data.length() == 0) {
        removeClient(sender);
        std::cout << "Removed a client" << std::endl;
    }
    for (auto &i: *clients) {
        if (i == sender) continue;
        i->write(i->name().toStdString().c_str());
        i->write(": ");
        if(i->write(data) < data.length()) {
            std::cout << "error at " << i->peerAddress().toString().toStdString() << std::endl;
        }
    }
}

void ServerMessageHandler::removeClient(TcpConvenience * toremove) {
    int i = clients->indexOf(toremove);
    clients->removeAt(i);
    toremove->disconnectFromHost();
    //delete once disconnected
    connect(toremove, &QAbstractSocket::disconnected,
            this, [&, toremove](){toremove->deleteLater();}
    );
}

void ServerMessageHandler::shutdown() {
    for (auto &i: *clients) {
        removeClient(i);
    }
}
