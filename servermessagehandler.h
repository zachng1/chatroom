#ifndef SERVERMESSAGEHANDLER_H
#define SERVERMESSAGEHANDLER_H

#include <QObject>
#include <QList>
#include <QHostAddress>
#include <QTcpSocket>
#include <QByteArray>
#include <iostream>
#include "tcpconvenience.h"

class ServerMessageHandler : public QObject
{
    Q_OBJECT
public:
    ServerMessageHandler();
    void addClient(TcpConvenience * newclient);
    void broadcast(TcpConvenience * sender);
    void removeClient(TcpConvenience * toremove);
    void shutdown();

private:
    QList<TcpConvenience *> * clients;

};

#endif // SERVERMESSAGEHANDLER_H
