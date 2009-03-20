#ifndef _CMUTEXTPRIVATE_H_
#define _CMUTEXTPRIVATE_H_

#include "sysinclude.h"

class CCondPrivate;

class CMutexPrivate
{
    friend class CCondPrivate;
public:
    CMutexPrivate();
    ~CMutexPrivate();
    
    void lock();
    void unlock();

private:
    pthread_mutex_t mMutex;
};

#endif
