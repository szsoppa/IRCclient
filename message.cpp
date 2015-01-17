#include "message.h"

namespace Message
{
namespace Request
{
    int SIGNUP = 0;
    int SIGNIN = 1;
    int COMMAND = 2;
}

namespace Respond
{
    const int OK = 0;
    const int DENY = 1;
    const int NICK_TAKEN = 2;
    const int WRONG_SIGN_IN_DATA = 3;
    const int WRONG_SIGN_UP_DATA = 4;
}

namespace ChannelRespond
{
    const int ACCEPT = 0;
    const int  DENY = 1;
    const int HELP = 2;
    const int EXIT = 3;
    const int LIST = 4;
    const int MESSAGE = 5;
}

namespace Data
{
    int WRONG_DATA = -1;
}

// commands
namespace Command
{
    const int CONNECT = 0;
    const int HELP = 1;
    const int EXIT = 2;
    const int CHANNEL = 3;
}

// methods
int RecognizeType(QString message)
{
    if (message.compare("connect") == 0)
        return 0;
    else if (message.compare("help") == 0)
        return 1;
    else if (message.compare("exit") == 0)
        return 2;
    else return Data::WRONG_DATA;
}

vector<QString> ParseMessage(QString message)
{
    vector<QString> list;
    if (message[0] == '\\')
    {
        message.remove(0,1);
        foreach( QString str, message.split(" "))
        {
            list.push_back(str);
        }
        return list;

    }
    list.push_back(message);
    return list;
}

vector<QString> GenerateList(QString message)
{
    vector<string> list;
    string temp;
    for (QString::iterator it=message.begin(); it!=message.end(); ++it)
    {
        if(*it == ',')
        {
            list.push_back(temp);
            temp.clear();
            continue;
        }
        else if (*it == '\n')
        {
            break;
        }
        temp.push_back(*it);
    }
    return list;
}

}
