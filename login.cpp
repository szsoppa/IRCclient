#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "editserver.h"
#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    add_servers_to_list();
}

Login::~Login()
{
    delete ui;
}

void Login::createNewItem(const QString & name)
{
    this->close();
    ui->ServerListWidget->addItem(name);
}

void Login::on_AddServerButton_clicked()
{
    NewServer window;
    window.setModal(false);
    window.exec();
    ui->ServerListWidget->addItem(window.getServerName());
}

void Login::on_EditServerButton_clicked()
{
    if(ui->ServerListWidget->count() != 0 && ui->ServerListWidget->currentRow() != -1)
    {
        EditServer window(this,ui->ServerListWidget->currentItem()->text());
        window.setModal(false);
        window.exec();
        add_servers_to_list();
    }
}

void Login::add_servers_to_list()
{
    ui->ServerListWidget->clear();
    vector<QString> list = File::get_all_data();
    for (vector<QString>::iterator it=list.begin(); it!=list.end(); it++)
        ui->ServerListWidget->addItem(*it);
}

void Login::on_RemoveServerButton_clicked()
{
    if(ui->ServerListWidget->count() != 0 && ui->ServerListWidget->currentRow() != -1)
    {
        File::remove_data(ui->ServerListWidget->currentItem()->text());
        ui->ServerListWidget->takeItem(ui->ServerListWidget->row(ui->ServerListWidget->currentItem()));
    }
}

void Login::on_ConnectToServerButton_clicked()
{
    if(ui->ServerListWidget->count() != 0 && ui->ServerListWidget->currentRow() != -1)
    {
        map<QString, QString> data = File::get_row(ui->ServerListWidget->currentItem()->text());
        QTcpSocket *socket = new QTcpSocket(this);
        socket->connectToHost(data["adress"],QString(data["port"]).toInt());
        if( socket->waitForConnected(500))
        {
            Message_type type = SIGNIN;
            QString message = QString::number(type)+ui->LoginEdit->text()+','+ui->PasswordEdit->text()+',';
            qDebug() << message;
            socket->write(message.toStdString().c_str());
            socket->waitForBytesWritten(500);
            socket->waitForReadyRead(500);

        }
        socket->close();
    }
}

void Login::on_RegisterButton_clicked()
{

}
