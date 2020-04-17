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
    void shutdown();
signals:
    void receivedmsg(QString message);
    void disconnected();
    void connected();
    void errInvalid();

private:
    QTcpSocket * socket;
};

#endif // CLIENT_H
