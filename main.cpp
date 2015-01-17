#include "mainwindow.h"
#include "login.h"
#include "headers.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login window1;
    MainWindow window2;
    QObject::connect(&window1, SIGNAL(loginAccepted(QString, int, QString)),
                     &window2, SLOT(showWindow(QString, int, QString)));
    window1.show();
    return a.exec();   
}
