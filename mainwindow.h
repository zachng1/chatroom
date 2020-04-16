#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QMenuBar>
#include <QErrorMessage>
#include <QMessageBox>
#include <cerrno>
#include <string>
#include <iostream>
#include <QNetworkInterface>
#include "mwwidgets/hostdialog.h"
#include "mwwidgets/joindialog.h"
#include "mwwidgets/chatwindow.h"
#include "server.h"
#include "client.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void host();
    void closeServer();
//    void viewClients();

    void join();
//    void disconnect();
//    void changeName();


private:
    void setupMenu();
    HostDialog * hostdialog;
    JoinDialog * joindialog;
    QErrorMessage * error;
    QMessageBox * messagebox;
    Server * server;
    Client * client;

    QAction * hostAct;
    QAction * closeAct;
    QAction * clientsAct;

    QAction * joinAct;

    ChatWindow * chat;


signals:

};

#endif // MAINWINDOW_H
