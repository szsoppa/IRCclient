#ifndef MESSAGE_H
#define MESSAGE_H

#include "headers.h"

using namespace std;

namespace Message
{
namespace Resquest
{
    extern int SIGNUP;
    extern int SIGNIN;
}

namespace Respond
{
    extern int OK;
    extern int DENY;
}

// commands
namespace Command
{
    extern QString CONNECT;
    extern QString HELP;
    extern QString EXIT;
}
// methods
int RecognizeType(QString message);
vector<QString> ParseMessage(QString message);
}

#endif // MESSAGE_H
