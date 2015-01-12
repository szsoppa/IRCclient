#ifndef EDITSERVER_H
#define EDITSERVER_H

#include "file.h"
#include "headers.h"

namespace Ui {
class EditServer;
}

class EditServer : public QDialog
{
    Q_OBJECT

public:
    explicit EditServer(QWidget *parent = 0, QString item = NULL);
    ~EditServer();

    void set_current_item(QString item);
    bool validate_data();

private slots:
    void on_CancelButton_clicked();

    void on_AcceptButton_clicked();

private:
    Ui::EditServer *ui;
    QString item;
};

#endif // EDITSERVER_H
