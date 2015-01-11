#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QString>
#include <QCoreApplication>
#include <QTextStream>
#include <vector>

using namespace std;

class File
{
public:
    File();
    ~File();

    void insert_data(QString server_name, QString server_adress, QString server_port);
    void edit_data(QString pattern, QString server_name, QString server_adress, QString server_port);
    void remove_data(QString item);
    vector<QString> get_data();
};

#endif // FILE_H
