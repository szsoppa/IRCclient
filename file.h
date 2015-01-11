#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QString>
#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <vector>
#include <map>

using namespace std;

class File
{
public:
    File();
    ~File();

    void insert_data(QString server_name, QString server_adress, QString server_port);
    void edit_data(QString pattern, QString server_name, QString server_adress, QString server_port);
    void remove_data(QString item);
    map<QString, QString> get_row(QString pattern);
    vector<QString> get_all_data();
};

#endif // FILE_H
