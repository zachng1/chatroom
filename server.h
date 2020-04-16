#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QNetworkInterface>
#include <iostream>
#include "servermessagehandler.h"
#include "tcpconvenience.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject * parent = nullptr);
    void setPort(int port);
    int port();
    void run();
    void shutdown();
    void incomingConnection(qintptr handle) override;

public slots:
    void addClients();

private:
    int portnum;
    void consoleLog();
    void setName(TcpConvenience * newconnection);
    ServerMessageHandler * handler;
};

#endif // SERVER_H
