#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    app.setApplicationName("Chat");
    app.setApplicationDisplayName("Chat");

    window.show();
    return app.exec();
}
