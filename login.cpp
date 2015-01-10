#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
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
    if( window.exec() )
        qDebug() << "Gitarka";
    else
        qDebug() << "Lipda";

    ui->ServerListWidget->addItem(window.getServerName());
}
