#ifndef  _CTHREADMANAGER_H_
#define _CTHREADMANAGER_H_

#include "tptypes.h"

class CThreadPool;

class CThreadManager
{
public:
    CThreadManager();
    CThreadManager( int nPoolSize );
    virtual ~CThreadManager();

    INTERJOB newWork( WORK pWork, WORKPARM pWorkParm );
    bool     stopWork( INTERJOB jobID );
    bool     resumeWork( INTERJOB jobID );
    bool     cancelWork( INTERJOB jobID );

    void     dump();

private:
    INTERJOB excuteWork( ThreadBase* pThread, WORK pWork, WORKPARM pWorkParm );

private:
    CThreadPool *mpIdlePool;
    CThreadPool *mpWorkPool;
};

#endif
