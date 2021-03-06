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
    if (validate_data())
    {
        int type = Message::Request::SIGNUP;
        QMessageBox message_box;
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
            QString response = socket->readAll();
            socket->close();
            if (response.toInt() == Message::Respond::OK)
            {
                this->close();
            }
            else
            {
                message_box.warning(0,"User already exists!","User already exists!");
            }
        }
        else
        {
            message_box.warning(0,"Server doesn't respond!","Server doesn't respond!");
            socket->close();
        }
    }
}

void Register::on_CancelButton_clicked()
{
    this->close();
}

bool Register::validate_data()
{
    QMessageBox message_box;

    if (ui->LoginEdit->text().count() != 0 &&
        ui->PasswordEdit->text().compare(ui->ConfirmPasswordEdit->text()) == 0)
        return true;

    message_box.warning(0,"Wrong data!","You have entered wrong user data");
    return false;
}
