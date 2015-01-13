#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "thread.h"
#include <QTcpSocket>

QTcpSocket *socket;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(767,675);
    Thread thread;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SendButton_clicked()
{

}

void MainWindow::runThread()
{

}
