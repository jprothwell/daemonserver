#include "CThreadPoolIdle.h"
#include "MyThread.h"
#include "CLog.h"

CThreadPoolIdle::CThreadPoolIdle()
{
}

CThreadPoolIdle::CThreadPoolIdle( int nPoolSize )
    : CThreadPool( nPoolSize )
{
    for( int i=0; i<nPoolSize; i++ )
        addThread( new ThreadBase() );
}

CThreadPoolIdle::~CThreadPoolIdle()
{
    for( int i=0; i<getCurStackSize(); i++ )
        popThread();
}

ThreadBase* CThreadPoolIdle::popThread()
{
    LOG("pop a thread from the idel pool");
    return CThreadPool::popThread();
}
