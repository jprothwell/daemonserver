#ifndef _CTHREADPOOL_H_
#define _CTHREADPOOL_H_

#include <vector>
#include "CDefine.h"

using namespace std;

typedef vector<ThreadBase *> ThreadStack;

class CThreadPool
{
public:
    virtual ~CThreadPool();
    virtual bool addThread( ThreadBase *pThread );
    virtual bool delThread( ThreadBase *pThread );
    virtual ThreadBase * popThread();
    virtual ThreadBase * findThread( ThreadBase* pThread );
    virtual ThreadBase * getFirstIdleThread();
    
    int size(){ return mThreadPoolStack.size(); }

protected:
    CThreadPool( int nStackSize=10 );
    int getCurStackSize(){ return mThreadPoolStack.size(); }

private:
    ThreadStack mThreadPoolStack;
    unsigned int         mnStackSize;
};

#endif
