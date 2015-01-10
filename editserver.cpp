#include "editserver.h"
#include "ui_editserver.h"

EditServer::EditServer(QWidget *parent, QString item) :
    QDialog(parent),
    ui(new Ui::EditServer)
{
    ui->setupUi(this);
    this->item = item;
    ui->ServerNameEdit->setText(this->item);
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
        QFile file(QCoreApplication::applicationDirPath () + "/servers.txt");
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QString s;
            QTextStream t(&file);
            while(!t.atEnd())
            {
                QString line = t.readLine();
                if(!line.contains(this->item))
                    s.append(line + "\n");
                else
                    s.append(ui->ServerNameEdit->text()+','+ui->ServerAdressEdit->text()+','
                             +QString::number(ui->ServerPortBox->value()));
            }
            file.resize(0);
            t << s;
            file.close();
        }
    }
    this->close();
}
