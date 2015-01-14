#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "message.h"
#include "headers.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_SendButton_clicked();
    void printMessage(QString message);
    void showWindow(QString adress, int port);
    void checkForMessage();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QString adress;
    int port;
};

#endif // MAINWINDOW_H
