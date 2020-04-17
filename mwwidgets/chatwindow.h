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
signals:
    void sendMessage(const QString);
public slots:
    void enable();
    void disable();
    void receiveMessage(const QString message);
    void ownMessage(const QString message);
    void messageConnector();
    void clear();

private:
    QTextEdit * chats;
    QHBoxLayout * sendedit;
    QLineEdit * editor;
    QPushButton * send;
};

#endif // CHATWINDOW_H
