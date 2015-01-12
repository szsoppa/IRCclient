#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->data = data;
}

Register::~Register()
{
    delete ui;
}

void Register::set_data(map<QString, QString> data)
{
    this->data = data;
}

void Register::on_RegisterButton_clicked()
{
    Message_type type = SIGNUP;
    QString name = ui->LoginEdit->text();
    QString password = ui->PasswordEdit->text();
    QString password_confirmation = ui->ConfirmPasswordEdit->text();
    QString message = QString::number(type) + name + ',' + password + ',' + password_confirmation + ',' + '\n';

    QTcpSocket *socket = new QTcpSocket(this);
    socket->connectToHost(this->data["adress"],QString(this->data["port"]).toInt());
    if( socket->waitForConnected(500))
    {
        socket->write(message.toStdString().c_str());
        socket->waitForBytesWritten(500);
        socket->waitForReadyRead(500);
    }
    socket->close();
    this->close();
}

void Register::on_CancelButton_clicked()
{
    this->close();
}
