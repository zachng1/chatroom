#include "chatwindow.h"

ChatWindow::ChatWindow(QWidget * parent) : QVBoxLayout(parent),
    chats{new QTextEdit},
    sendedit{new QHBoxLayout},
    editor{new QLineEdit},
    send{new QPushButton}
{
    send->setText("Send");
    sendedit->addWidget(editor);
    sendedit->addSpacing(10);
    sendedit->addWidget(send);
    connect(editor, &QLineEdit::returnPressed,
            send, &QPushButton::pressed);
    connect(send, &QPushButton::pressed,
            this, &ChatWindow::messageConnector);

    chats->setReadOnly(true);
    chats->setAlignment(Qt::AlignRight);

    this->addWidget(chats);
    this->addItem(sendedit);
}

void ChatWindow::receiveMessage(const QString message) {
    chats->append(message);
}

void ChatWindow::messageConnector() {
    QString msg = editor->text();
    emit sendMessage(msg);

    receiveMessage(msg);
    editor->setText("");
}

void ChatWindow::disable() {
    send->setEnabled(false);
    editor->setEnabled(false);
}

void ChatWindow::enable() {
    send->setEnabled(true);
    editor->setEnabled(true);
}
