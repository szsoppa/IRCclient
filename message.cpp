#include "message.h"

namespace Message
{
namespace Request
{
    int SIGNUP = 0; // to inform that user want to register
    int SIGNIN = 1; // to infrom that user want to log in
}

namespace Respond
{
    int OK = 0;
    int DENY = 1;
    int NICK_TAKEN = 2;
    int WRONG_SIGN_IN_DATA = 3;
    int WRONG_SIGN_UP_DATA = 4;
}

namespace Data
{
    int WRONG_DATA = -1;
}

// commands
namespace Command
{
    QString CONNECT = "connect";
    QString HELP = "help";
    QString EXIT = "exit";
}


// methods
int RecognizeType(QString message)
{
    if (message.compare(Command::CONNECT) == 0)
        return 0;
    else if (message.compare(Command::HELP) == 0)
        return 1;
    else if (message.compare(Command::EXIT) == 0)
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

}
