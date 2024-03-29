#ifndef _MYTHREAD_H_
#define _MYTHREAD_H_

#include "CThread.h"
#include "CDefine.h"

class MyThread : public CThread
{
public:
    MyThread()
    {
        mpThreadWork = NULL;
        mpThreadParm = NULL;
    }
    MyThread( WORK pWork, WORKPARM pWorkParm )
    {
        mpThreadWork = pWork;
        mpThreadParm = pWorkParm;
    }
    virtual ~MyThread()
    {
    }

    bool startThread()
    {
        return CThread::start();
    }
    bool stopThread()
    {
        return CThread::stop();
    }
    bool resumeThread()
    {
        return CThread::resume();
    }
    bool closeThread()
    {
        return CThread::cancel();
    }

    void setThreadWork( WORK pWork ){ mpThreadWork = pWork; }
    void setThreadParm( void *pThreadParm ){ mpThreadParm = pThreadParm; }

protected:
    virtual void run()
    {
        mpThreadWork( mpThreadParm );
    }


private:
    WORK        mpThreadWork;
    WORKPARM    mpThreadParm;
    
};

#endif
