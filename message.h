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
    extern const int DENY;
    extern const int OK;
    extern const int NICK_TAKEN;
    extern const int WRONG_SIGN_IN_DATA;
    extern const int WRONG_SIGN_UP_DATA;
}

namespace ChannelRespond
{
    extern const int ACCEPT;
    extern const int DENY;
    extern const int HELP;
    extern const int EXIT;
    extern const int LIST;
    extern const int MESSAGE;
}

// commands
namespace Command
{
    extern const int CONNECT;
    extern const int HELP;
    extern const int EXIT;
    extern const int CHANNEL;
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
