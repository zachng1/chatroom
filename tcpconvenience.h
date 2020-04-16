#ifndef TCPCONVENIENCE_H
#define TCPCONVENIENCE_H

#include <QTcpSocket>
#include <iostream>

class TcpConvenience : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpConvenience(QObject * parent = nullptr);
    QString name();
    void setName(QString name);

private:
    QString username;
};

#endif // TCPCONVENIENCE_H
