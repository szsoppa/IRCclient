#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(767,675);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SendButton_clicked()
{
}

void MainWindow::printMessage(QString message)
{
    ui->textLog->append(message);
}

void MainWindow::showWindow(QString adress, QString port)
{
    QMessageBox message_box;
    connect(&message_box, SIGNAL(accepted()), this, SLOT(close()));
    socket = new QTcpSocket(this);
    socket->connectToHost(adress, port.toInt());
    if (!socket->waitForConnected() )
        message_box.critical(0,"Error","Disconnected from the server");
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(checkForMessage()));
    this->show();
}

void MainWindow::checkForMessage()
{
    QString message = socket->readAll();
    ui->textLog->append(message);
}
