#include "file.h"

File::File()
{
}

File::~File()
{
}

void File::insert_data(QString server_name, QString server_adress, QString server_port)
{
    QFile file(QCoreApplication::applicationDirPath () + "/servers.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append );
    QTextStream out(&file);
    out << server_name <<',' << server_adress << ',';
    out << server_port << ',' << '\n';
    file.close();
}

void File::edit_data(QString pattern, QString server_name, QString server_adress, QString server_port)
{
    QFile file(QCoreApplication::applicationDirPath () + "/servers.txt");
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s;
        QTextStream t(&file);
        while(!t.atEnd())
        {
            QString line = t.readLine();
            if(!line.contains(pattern))
                s.append(line + "\n");
            else
                s.append(server_name+','+server_adress+','+server_port+','+'\n');
        }
        file.resize(0);
        t << s;
        file.close();
    }
}

void File::remove_data(QString item)
{
    QFile file(QCoreApplication::applicationDirPath () + "/servers.txt");
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s;
        QTextStream t(&file);
        while(!t.atEnd())
        {
            QString line = t.readLine();
            if(!line.contains(item))
                s.append(line + "\n");
        }
        file.resize(0);
        t << s;
        file.close();
    }
}

map<QString, QString> File::get_row(QString pattern)
{
    map<QString, QString> row;
    QFile file(QCoreApplication::applicationDirPath () + "/servers.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString server_name;
        QTextStream t(&file);
        while(!t.atEnd())
        {
            QString line = t.readLine();
            for(int i=0;;i++)
            {
                if (line[i] == ',')
                {
                    server_name = line;
                    server_name.truncate(i);
                    break;
                }
            }
            if (server_name.compare(pattern) == 0)
            {
                vector<QString> list;
                QString temp;
                for( QString::iterator it=line.begin(); it!=line.end(); ++it)
                {
                    if(*it == ',')
                    {
                        list.push_back(temp);
                        temp.clear();
                        continue;
                    }
                    temp.push_back(*it);
                }
                row["server"] = list[0];
                row["adress"] = list[1];
                row["port"] = list[2];
                file.close();
                return row;
            }
        }
    }
    file.close();
    return row;
}

vector<QString> File::get_all_data()
{
    vector<QString> list;
    QFile file(QCoreApplication::applicationDirPath () + "/servers.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream t(&file);
        while(!t.atEnd())
        {
            QString line = t.readLine();
            for(int i=0;;i++)
            {
                if (line[i] == ',')
                {
                    line.truncate(i);
                    break;
                }
            }
            list.push_back(line);
        }
    }
    file.close();
    return list;
}
