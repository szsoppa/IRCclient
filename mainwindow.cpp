#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>

QTcpSocket *socket;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(ui->textLog->toPlainText(),4000);
    if( socket->waitForConnected(500) )
    {
        ui->textLog->append("Connected");

        socket->waitForBytesWritten(10);
        socket->waitForReadyRead(30);

        ui->textLog->append(socket->readAll());
    }
    else
    {
        ui->textLog->setText("Not connected");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    socket->close();
}
