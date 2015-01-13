#ifndef THREAD_H
#define THREAD_H

#include <headers.h>

class Thread : public QThread
{
public:
    Thread();
    ~Thread();

    void run();
};

#endif // THREAD_H
