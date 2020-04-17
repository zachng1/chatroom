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


    chats->setFontFamily("Cambria");
    chats->setFontItalic(true);
    chats->setReadOnly(true);

    this->addWidget(chats);
    this->addItem(sendedit);
}

void ChatWindow::receiveMessage(const QString message) {
    if (message.startsWith('@')) {
        chats->setTextColor(Qt::black);
        chats->setAlignment(Qt::AlignCenter);
        chats->append(message.mid(1, message.length()) + "\n");
        return;
    }
    else if (message.startsWith('!')) {
        chats->setTextColor(Qt::black);
        chats->setAlignment(Qt::AlignCenter);
        chats->append(message.mid(1, message.length()) + "\n");
        return;
    }

    chats->setTextColor(Qt::black);
    chats->setAlignment(Qt::AlignLeft);
    int splitat = message.indexOf(':') + 1;
    chats->append(message.left(splitat));
    chats->moveCursor(QTextCursor::End);
    chats->setTextColor(Qt::gray);
    chats->insertPlainText(message.right(message.length()-splitat) + '\n');
}

void ChatWindow::ownMessage(const QString message) {
    chats->setTextColor(Qt::black);
    chats->setAlignment(Qt::AlignRight);
    chats->append(message + "\n");
}

void ChatWindow::messageConnector() {
    QString msg = editor->text();
    emit sendMessage(msg);
    ownMessage(msg);
    editor->setText("");
}

void ChatWindow::clear() {
    chats->clear();
}

void ChatWindow::disable() {
    send->setEnabled(false);
    editor->setEnabled(false);
}

void ChatWindow::enable() {
    send->setEnabled(true);
    editor->setEnabled(true);
}
