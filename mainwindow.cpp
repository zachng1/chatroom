#include "mainwindow.h"
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    hostdialog{new HostDialog},
    joindialog{new JoinDialog},
    error{new QErrorMessage},
    messagebox{new QMessageBox},
    server{new Server},
    client{new Client},
    chat{new ChatWindow}
{
    setupMenu();
    chat->disable();
    QWidget * widget = new QWidget;
    widget->setLayout(chat);
    setCentralWidget(widget);
    connect(client, &Client::receivedmsg, chat, &ChatWindow::receiveMessage);
    connect(chat, &ChatWindow::sendMessage, client, &Client::sendMessage);
    connect(client, &Client::connected, chat, &ChatWindow::enable);
    connect(client, &Client::connected, chat, &ChatWindow::clear);
    connect(client, &Client::connected, this, [&](){
        joinAct->setEnabled(false);
        disconnectAct->setEnabled(true);});
    connect(client, &Client::disconnected, chat, &ChatWindow::disable);
    connect(client, &Client::disconnected, this, [&](){
        joinAct->setEnabled(true);
        disconnectAct->setEnabled(false);
    });

    connect(client, &Client::errInvalid, this, &MainWindow::invalidChar);
}

//needs added checking for if either object is in fact running
void MainWindow::closeEvent(QCloseEvent *event) {
    server->shutdown();
    client->shutdown();
    event->accept();
}

void MainWindow::setupMenu() {
    QMenuBar * menu = menuBar();

    QMenu * server = menu->addMenu("&Server");
    hostAct = server->addAction("&Host");
    closeAct = server->addAction("&Close Server");
    closeAct->setEnabled(false);

    connect(hostAct, &QAction::triggered, this, &MainWindow::host);
    connect(closeAct, &QAction::triggered, this, &MainWindow::closeServer);

    QMenu * client = menu->addMenu("&Client");
    joinAct = client->addAction("&Join a Server");
    disconnectAct = client->addAction("&Disconnect");
    disconnectAct->setEnabled(false);

    connect(joinAct, &QAction::triggered, this, &MainWindow::join);
    connect(disconnectAct, &QAction::triggered, this, &MainWindow::disconnectClient);
}

void MainWindow::host() {
    if(hostdialog->exec()) {
        QString p = hostdialog->getPort();
        int portnum;
        try {
            portnum = std::stoi(p.toStdString());
        }
        catch (const std::invalid_argument& e) {
            error->showMessage("Invalid Port Number");
            return;
        }
        catch (...) {
            error->showMessage("Something Went Wrong");
            return;
        }
        portnum = std::stoi(p.toStdString());
        server->setPort(portnum);
        server->run();
        hostAct->setEnabled(false);
        closeAct->setEnabled(true);
    }
}

void MainWindow::closeServer() {
    messagebox->setText("Are you sure you want to close the server?");
    messagebox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (messagebox->exec() == QMessageBox::Yes) {
        server->shutdown();
    }
    hostAct->setEnabled(true);
    closeAct->setEnabled(false);
}

void MainWindow::join() {
    if(joindialog->exec()) {
        QString port = joindialog->port();
        int portnum;
        try {
            portnum = std::stoi(port.toStdString());
        }
        catch (const std::invalid_argument& e) {
            error->showMessage("Port Must Contain only Numbers");
            return;
        }
        catch (...) {
            error->showMessage("Something Went Wrong");
            return;
        }
        QString address = joindialog->ipaddress();
        QHostAddress ipaddress;
        try {
            ipaddress.setAddress(address);
        }
        catch (...) {
            error->showMessage("Invalid IP Address");
            return;
        }
        QString name = joindialog->username();
        if (name.contains(':') || name.contains('@') || name.contains('!')) {
            error->showMessage("Name cannot contain ':', '@', '!'");
            return;
        }
        else if (name.isEmpty()) {
            error->showMessage("Name cannot be empty");
            return;
        }
        client->connectHost(name, ipaddress, portnum);
    }
}

void MainWindow::disconnectClient() {
    client->shutdown();
}

void MainWindow::invalidChar() {
    error->showMessage("Invalid character");
}
