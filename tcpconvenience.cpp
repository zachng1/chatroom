#include "tcpconvenience.h"

TcpConvenience::TcpConvenience(QObject * parent) :
    QTcpSocket(parent)
{
}

QString TcpConvenience::name() {
    return username;
}

void TcpConvenience::setName(QString name) {
    username = name;
}
