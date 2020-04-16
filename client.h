#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <iostream>

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    void connectHost(QString name, QHostAddress address, quint16 port);
public slots:
    void receive();
    void sendMessage(QString message);
    void error(QAbstractSocket::SocketError error);
signals:
    void receivedmsg(QString message);

private:
    QTcpSocket * socket;
};

#endif // CLIENT_H
