#ifndef _CTHREADPOOLWORK_H_
#define _CTHREADPOOLWORK_H_

#include "CThreadPool.h"

class CThreadPoolWork : public CThreadPool
{
public:
    CThreadPoolWork();
    CThreadPoolWork( int nPoolSize );
    virtual ~CThreadPoolWork();

    virtual ThreadBase * findThread( ThreadBase *pThread );
};

#endif
