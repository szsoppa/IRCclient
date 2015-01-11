#include "editserver.h"
#include "ui_editserver.h"

EditServer::EditServer(QWidget *parent, QString item) :
    QDialog(parent),
    ui(new Ui::EditServer)
{
    ui->setupUi(this);
    this->item = item;
    map<QString, QString> row = File::get_row(this->item);
    ui->ServerNameEdit->setText(row["server"]);
    ui->ServerAdressEdit->setText(row["adress"]);
    ui->ServerPortBox->setValue(QString(row["port"]).toInt());
}

EditServer::~EditServer()
{
    delete ui;
}

void EditServer::set_current_item(QString item)
{
    this->item = item;
}

void EditServer::on_CancelButton_clicked()
{
    this->close();
}

bool EditServer::validate_data()
{
    int counter = 0;
    QMessageBox messageBox;
    QString server_address = ui->ServerAdressEdit->text();

    for (QString::iterator it=server_address.begin(); it!=server_address.end(); it++)
    {
        if(*it == '.')
            counter++;
    }
    if (counter != 3 || server_address.length()+1 < 8)
    {
        messageBox.critical(0,"Wrong data!","You have entered wrong server data format");
        return false;
    }
    return true;
}

void EditServer::on_AcceptButton_clicked()
{
    if(validate_data())
    {
        File::edit_data(this->item, ui->ServerNameEdit->text(), ui->ServerAdressEdit->text(),
                       QString::number(ui->ServerPortBox->value()));
        this->close();
    }
}
