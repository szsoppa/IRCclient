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

QString NewServer::getServerName()
{
    return ui->ServerNameEdit->text();
}

void NewServer::on_CreateServerButton_clicked()
{
    if(validate_data())
    {
        File::insert_data(ui->ServerNameEdit->text(), ui->ServerAdressEdit->text(),
                         QString::number(ui->ServerPortBox->value()));
        this->close();
    }
}

void NewServer::on_CancelServerButton_clicked()
{
    ui->ServerNameEdit->clear();
    this->close();
}

bool NewServer::validate_data()
{
    int counter = 0;
    QMessageBox message_box;
    QString server_address = ui->ServerAdressEdit->text();

    for (QString::iterator it=server_address.begin(); it!=server_address.end(); it++)
    {
        if(*it == '.')
            counter++;
    }
    if (counter != 3 || server_address.length()+1 < 8 || server_address.length()+1 > 16)
    {
        message_box.warning(0,"Wrong data!","You have entered wrong server data format");
        return false;
    }
    return true;
}
