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
    EditServer window(this,ui->ServerListWidget->currentItem()->text());
    window.setModal(false);
    window.exec();
}

void Login::add_servers_to_list()
{
    QFile file(QCoreApplication::applicationDirPath () + "/servers.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString s;
        QTextStream t(&file);
        while(!t.atEnd())
        {
            QString line = t.readLine();
            for(int i=0;;i++)
            {
                if (line[i] == ',')
                {
                    line.truncate(i);
                    break;
                }
            }
            ui->ServerListWidget->addItem(line);
        }
        file.close();
    }
}

void Login::on_RemoveServerButton_clicked()
{
    QFile file(QCoreApplication::applicationDirPath () + "/servers.txt");
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s;
        QTextStream t(&file);
        while(!t.atEnd())
        {
            QString line = t.readLine();
            if(!line.contains(ui->ServerListWidget->currentItem()->text()))
                s.append(line + "\n");
        }
        file.resize(0);
        t << s;
        file.close();
    }
    ui->ServerListWidget->takeItem(ui->ServerListWidget->row(ui->ServerListWidget->currentItem()));
}
