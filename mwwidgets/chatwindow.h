#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QTextEdit>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>

class ChatWindow : public QVBoxLayout
{
    Q_OBJECT
public:
    ChatWindow(QWidget * parent=nullptr);
    void enable();
    void disable();
signals:
    void sendMessage(const QString);
public slots:
    void receiveMessage(const QString message);
    void messageConnector();

private:
    QTextEdit * chats;
    QHBoxLayout * sendedit;
    QLineEdit * editor;
    QPushButton * send;
};

#endif // CHATWINDOW_H
