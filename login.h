#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <newserver.h>

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

private slots:
    void on_AddServerButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
