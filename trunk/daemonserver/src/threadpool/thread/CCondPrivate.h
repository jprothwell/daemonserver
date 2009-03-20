#ifndef _CCONDPRIVATE_H_
#define _CCONDPRIVATE_H_

#include "sysinclude.h"

class CMutexPrivate;

class CCondPrivate
{
public:
    explicit CCondPrivate( CMutexPrivate* pMutex );
    ~CCondPrivate();

    bool wait();
    bool wakeUp();
    
private:
    pthread_cond_t mCond;
    CMutexPrivate* mpMutex;
};

#endif
