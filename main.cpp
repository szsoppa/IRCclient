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
    QObject::connect(&window1, SIGNAL(finished(int)), &window2, SLOT(show()));
    window1.show();
    return a.exec();
}
