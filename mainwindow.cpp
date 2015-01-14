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
    QString message = QString::number(Message::Request::COMMAND) +
                      ui->MessageEdit->text() + '\n';
    socket->write(message.toStdString().c_str());
    socket->waitForBytesWritten();
}

void MainWindow::printMessage(QString message)
{
    ui->textLog->append(message);
}

void MainWindow::showWindow(QString adress, int port)
{
    this->adress = adress;
    this->port = port;
    QMessageBox message_box;
    connect(&message_box, SIGNAL(accepted()), this, SLOT(close()));
    socket = new QTcpSocket(this);
    socket->connectToHost(this->adress, this->port);
    if(!socket->waitForConnected())
        message_box.critical(0,"Error","Server disconnected");
    connect(socket, SIGNAL(readyRead()), this, SLOT(checkForMessage()));
    this->show();
}

void MainWindow::checkForMessage()
{
    QString message = socket->readAll();
    ui->textLog->append(message);
}
