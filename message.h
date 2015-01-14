#ifndef MESSAGE_H
#define MESSAGE_H

#include "headers.h"

using namespace std;

namespace Message
{
namespace Request
{
    extern int SIGNUP;
    extern int SIGNIN;
    extern int COMMAND;
}

namespace Respond
{
    extern int DENY;
    extern int OK;
    extern int NICK_TAKEN;
    extern int WRONG_SIGN_IN_DATA;
    extern int WRONG_SIGN_UP_DATA;
}

// commands
namespace Command
{
    extern QString CONNECT;
    extern QString HELP;
    extern QString EXIT;
}

namespace Data
{
    extern int WRONG_DATA;
}
// methods
int RecognizeType(QString message);
vector<QString> ParseMessage(QString message);
}

#endif // MESSAGE_H
