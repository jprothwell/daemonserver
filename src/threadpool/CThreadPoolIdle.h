#ifndef  _CTHREADPOOLIDLE_H_
#define _CTHREADPOOLIDLE_H_

#include "CThreadPool.h"

class CThreadPoolIdle : public CThreadPool
{
public:
    CThreadPoolIdle();
    CThreadPoolIdle( int nPoolSize );
    virtual ~CThreadPoolIdle();

    virtual ThreadBase* popThread();
};

#endif
