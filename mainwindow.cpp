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
}

void MainWindow::setupMenu() {
    QMenuBar * menu = menuBar();

    QMenu * server = menu->addMenu("&Server");
    hostAct = server->addAction("&Host");
    closeAct = server->addAction("&Close Server");
    closeAct->setEnabled(false);
    server->addSeparator();
    clientsAct = server->addAction("&Clients");
    clientsAct->setEnabled(false);

    connect(hostAct, &QAction::triggered, this, &MainWindow::host);
    connect(closeAct, &QAction::triggered, this, &MainWindow::closeServer);

    QMenu * client = menu->addMenu("&Client");
    joinAct = client->addAction("&Join a Server");
    client->addAction("&Disconnect")->setEnabled(false);
    client->addSeparator();
    client->addAction("&Set Name");

    connect(joinAct, &QAction::triggered, this, &MainWindow::join);
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
        clientsAct->setEnabled(true);
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
    clientsAct->setEnabled(false);
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
        client->connectHost(name, ipaddress, portnum);
        chat->enable();
    }
}
