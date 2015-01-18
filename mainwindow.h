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
    void closeEvent(QCloseEvent *event);
    ~MainWindow();

private slots:
    void on_SendButton_clicked();
    void printMessage(QString message);
    void showWindow(QString adress, int port, QString);
    void checkForMessage();

    void on_MainWindow_destroyed();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QString adress;
    QString nickname;
    int port;
};

#endif // MAINWINDOW_H
