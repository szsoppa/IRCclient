#ifndef REGISTER_H
#define REGISTER_H

#include "headers.h"
#include "message.h"

using namespace std;

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

    void set_data(map<QString, QString> data);

private slots:
    void on_RegisterButton_clicked();

    void on_CancelButton_clicked();

private:
    map<QString, QString> data;
    Ui::Register *ui;
};

#endif // REGISTER_H
