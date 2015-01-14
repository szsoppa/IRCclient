#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "editserver.h"

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
    else
    {
        QMessageBox message_box;
        message_box.warning(0,"Wrong data!","Please choose one of the servers to edit");
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
    else
    {
        QMessageBox message_box;
        message_box.warning(0,"Wrong data!","Please choose one of the servers to remove");
    }
}

void Login::on_ConnectToServerButton_clicked()
{
    if(ui->ServerListWidget->count() != 0 && ui->ServerListWidget->currentRow() != -1)
    {
        if(ui->NicknameEdit->text().count() != 0 &&
           ui->LoginEdit->text().count() != 0 && ui->PasswordEdit->text().count() != 0)
        {
            map<QString, QString> data = File::get_row(ui->ServerListWidget->currentItem()->text());
            QTcpSocket *socket = new QTcpSocket(this);
            socket->connectToHost(data["adress"],QString(data["port"]).toInt());
            if( socket->waitForConnected())
            {
                int type = Message::Request::SIGNIN;
                QString message = QString::number(type)+ui->LoginEdit->text()+','+ui->PasswordEdit->text()+','+ui->NicknameEdit->text()+','+'\n';
                socket->write(message.toStdString().c_str());
                socket->waitForBytesWritten();
                socket->waitForReadyRead();
                QString response = socket->readAll();
                if (response.toInt() == Message::Respond::OK)
                {
                    emit loginAccepted(data["adress"],data["port"]);
                    socket->close();
                    this->close();
                }
                socket->close();
            }
        }
        else
        {
            QMessageBox message_box;
            message_box.warning(0,"Wrong data!","Please provide all data required to connect");
        }
    }
    else
    {
        QMessageBox message_box;
        message_box.warning(0,"Wrong data!","Please choose one of the servers to establish connection");
    }
}

void Login::on_RegisterButton_clicked()
{
    if(ui->ServerListWidget->count() != 0 && ui->ServerListWidget->currentRow() != -1)
    {
        Register window;
        window.setModal(false);
        window.set_data(File::get_row(ui->ServerListWidget->currentItem()->text()));
        window.exec();
    }
    else
    {
        QMessageBox message_box;
        message_box.warning(0,"No server error!","Please choose server on which you want to register");
    }
}
