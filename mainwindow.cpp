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
    if (socket->write(message.toStdString().c_str()) == -1)
    {
        QMessageBox message_box;
        message_box.critical(0,"Server error","You have been disconnected from the server");
        this->close();
    }
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
    socket = new QTcpSocket(this);
    socket->connectToHost(this->adress, this->port);
    if(!socket->waitForConnected())
    {
        message_box.critical(0,"Server error","Server disconnected");
        this->close();
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(checkForMessage()));
    connect(ui->MessageEdit, SIGNAL(returnPressed()), ui->SendButton, SIGNAL(clicked()));
    this->show();
}

int MainWindow::checkForMessage()
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
        QString pattern = QString("$").append(this->nickname);
        QTime time;
        QStringList list = message.split(",");
        QString nickname = list[0];
        message.remove(0,nickname.length()+1);
        if (!message.contains(pattern) && message[0] == '$')
        {
            qDebug() << "WESZLO";
            return 0;
        }
        message = "[" + time.currentTime().toString("hh:mm:ss") + "]" + "  " +
                  "<@" + nickname + "> " + ": " + message;
        ui->textLog->append(message);
    }
    else if(type == Message::ChannelRespond::HELP)
    {
        message.remove(0,1);
        message = "**************************\n" + message +
                  "**************************";
        ui->textLog->append(message);
    }
}

void MainWindow::on_MainWindow_destroyed()
{
    QString message = QString::number(Message::Command::EXIT) + '\n';
    socket->write(message.toStdString().c_str());
    qDebug() << "Wyslane";
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QString message;
    message = QString::number(Message::Request::COMMAND) +
                      "\\exit" + ' ' + this->nickname + ',' + '\n';
    qDebug() << message;
    socket->write(message.toStdString().c_str());
    socket->waitForBytesWritten();
    this->close();
}
