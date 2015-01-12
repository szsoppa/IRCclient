#ifndef FILE_H
#define FILE_H

#include "headers.h"

using namespace std;

class File
{
public:
    File();
    ~File();

    static void insert_data(QString server_name, QString server_adress, QString server_port);
    static void edit_data(QString pattern, QString server_name, QString server_adress, QString server_port);
    static void remove_data(QString item);
    static map<QString, QString> get_row(QString pattern);
    static vector<QString> get_all_data();
};

#endif // FILE_H
