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
    QString message;
    QString text = ui->MessageEdit->text();
    if (text[0] == '\\')
    {
        message = QString::number(Message::Request::COMMAND) +
                          ui->MessageEdit->text() + ' ' + this->nickname + ',' + '\n';
    }
    else
    {
        message = QString::number(Message::Request::COMMAND) +
                          ui->MessageEdit->text() + '\n';
    }
    socket->write(message.toStdString().c_str());
    socket->waitForBytesWritten();
    qDebug() << "Wysylam wiadomosc: " << message;
}

void MainWindow::printMessage(QString message)
{
    ui->textLog->append(message);
}

void MainWindow::showWindow(QString adress, int port, QString nickname)
{
    this->nickname = nickname;
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
    qDebug() << "Wiadomosc: " << message;
    QString temp = message;
    temp.remove(1,message.length()-1);
    int type = temp.toInt();

    if(type == Message::ChannelRespond::ACCEPT)
    {
        message.remove(0,1);
        message.remove('\n');
        ui->textLog->setText("Welcome in " + message + " channel!\nHave a good time! ;)");
    }
    else if (type == Message::ChannelRespond::LIST)
    {
        ui->UserList->clear();
        message.remove(0,1);
        vector<QString> list = Message::GenerateList(message);
        qDebug() << "Rozmiar listy: " << list.size();
        for (int i=0; i<list.size(); i++)
        {
            if (this->nickname.compare(list[i]) != 0)
                ui->UserList->addItem(list[i]);
        }
    }
    else if (type == Message::ChannelRespond::EXIT)
    {
        this->close();
    }
    else if (type == Message::ChannelRespond::MESSAGE)
    {
        message.remove(0,1);
        message.remove('\n');
        ui->textLog->append(message);
    }
    else if(type == Message::ChannelRespond::HELP)
    {
        message.remove(0,1);
        message.remove('\n');
        ui->textLog->append(message);
    }
}
