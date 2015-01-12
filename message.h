#ifndef MESSAGE_H
#define MESSAGE_H

enum Message_type
{
    SIGNUP = 0,
    SIGNIN = 1
};

enum Message_respond
{
    OK = 0,
    DENY = 1,
    NICK_TAKEN = 2,
    WRONG_SIGN_IN_DATA = 3,
    WRONG_SIGN_UP_DATA = 4
};

#endif // MESSAGE_H
