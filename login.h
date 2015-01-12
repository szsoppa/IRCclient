#ifndef LOGIN_H
#define LOGIN_H

#include <newserver.h>
#include "message.h"
#include "headers.h"
#include "register.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void createNewItem(const QString & name);

signals:
    void loginAccepted();

private slots:
    void on_AddServerButton_clicked();

    void on_EditServerButton_clicked();

    void on_RemoveServerButton_clicked();

    void on_ConnectToServerButton_clicked();

    void on_RegisterButton_clicked();

private:
    Ui::Login *ui;
    void add_servers_to_list();
};

#endif // LOGIN_H
