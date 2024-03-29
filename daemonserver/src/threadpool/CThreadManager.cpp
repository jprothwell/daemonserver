#include "CThreadManager.h"
#include "CThreadPoolIdle.h"
#include "CThreadPoolWork.h"
#include "MyThread.h"
#include "CLog.h"

CThreadManager::CThreadManager()
{
    mpIdlePool = new CThreadPoolIdle( 20 );
    mpWorkPool = new CThreadPoolWork( 20 );
}

CThreadManager::CThreadManager( int nPoolSize )
{
    mpIdlePool = new CThreadPoolIdle( nPoolSize );
    mpWorkPool = new CThreadPoolWork( nPoolSize );
}

CThreadManager::~CThreadManager()
{
    delete mpIdlePool;
    delete mpWorkPool;
}

INTERJOB CThreadManager::newWork( WORK pWork, WORKPARM pWorkParm )
{
    ThreadBase *pThread = mpIdlePool->popThread();
    INTERJOB retJobID = 0;
    if( NULL!=pThread )
    {
        retJobID = excuteWork( pThread, pWork, pWorkParm );
    }
    else
    {
        while( (pThread=mpWorkPool->getFirstIdleThread())!=NULL )
        {
            mpWorkPool->delThread( pThread );
            mpIdlePool->addThread( pThread );
        }
        pThread = mpIdlePool->popThread();
        if( NULL!=pThread )
        {
            retJobID = excuteWork( pThread, pWork, pWorkParm);
        }
    }

    return retJobID;
}

bool CThreadManager::stopWork( INTERJOB jobID )
{
    ThreadBase *pThread = mpWorkPool->findThread( jobID );
    LOG("CThreadManger::stopWork get the thread from pool, thread:"<<pThread);
    if( NULL!=pThread )
        pThread->stopThread();    

    return true;
}

bool CThreadManager::resumeWork( INTERJOB jobID )
{
    ThreadBase *pThread = mpWorkPool->findThread( jobID );
    if( NULL!=pThread )
        pThread->resumeThread();    

    return false;
}

bool CThreadManager::cancelWork( INTERJOB jobID )
{
    ThreadBase *pThread = mpWorkPool->findThread( jobID );
    if( NULL!=pThread )
    {
        bool bClose = pThread->closeThread();
        if( true==bClose )
        {
            mpWorkPool->delThread( pThread );
            mpIdlePool->addThread( pThread );
            return true;
        }
    }

    return false;
}

INTERJOB CThreadManager::excuteWork( ThreadBase* pThread, WORK pWork, WORKPARM pWorkParm )
{
    INTERJOB retJobID = 0;
    LOG("CThreadManager::pWork : "<<pWork);
    pThread->setThreadWork( pWork );
    pThread->setThreadParm( pWorkParm );
    bool bStart = pThread->startThread();
    if( true==bStart )
    {
        mpIdlePool->delThread( pThread );
        mpWorkPool->addThread( pThread );
        retJobID = pThread;
        LOG("CThreadManager::retJobID="<<retJobID);
    }

    return retJobID;
}

void CThreadManager::dump()
{
    printf("######## Begin CThreadManager::dump() #######\n");

    printf("The Thread in Idel pool is : %d\n", mpIdlePool->size());
    printf("The Thread in work pool is : %d\n", mpWorkPool->size());

    printf("######## end CThreadManager::dump() #######\n");

}

