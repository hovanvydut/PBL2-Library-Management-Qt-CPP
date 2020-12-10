#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //LoginDialog d;
    //d.show();
    w.showAndLogin();

    return a.exec();
}
