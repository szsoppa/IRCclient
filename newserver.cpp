#include "newserver.h"
#include "ui_newserver.h"

NewServer::NewServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewServer)
{
    ui->setupUi(this);
}

NewServer::~NewServer()
{
    delete ui;
}

void NewServer::on_CreateServerButton_clicked()
{
    Login login;
    login.createNewItem(ui->ServerNameEdit->text());
    qDebug() << ui->ServerNameEdit->text();
}

void NewServer::on_CancelServerButton_clicked()
{
    this->close();
}
