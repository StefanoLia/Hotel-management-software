#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow* M = new MainWindow;
    M->show();
    return app.exec();
}

