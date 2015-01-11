#ifndef NEWSERVER_H
#define NEWSERVER_H

#include <QDialog>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include "file.h"

namespace Ui {
class NewServer;
}

class NewServer : public QDialog
{
    Q_OBJECT

public:
    explicit NewServer(QWidget *parent = 0);
    ~NewServer();

    // custom methods
    QString getServerName();
    bool validate_data();

private slots:
    void on_CreateServerButton_clicked();

    void on_CancelServerButton_clicked();

private:
    Ui::NewServer *ui;
};

#endif // NEWSERVER_H
