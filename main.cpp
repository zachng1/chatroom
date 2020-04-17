#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    app.setApplicationName("Chat");
    app.setApplicationDisplayName("Chat");
    window.resize(app.primaryScreen()->size() * 0.7);
    QFontDatabase::addApplicationFont(":resources/fonts/cambriai.ttf");


    window.show();
    return app.exec();
}
