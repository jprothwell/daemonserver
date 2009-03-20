#include "CThreadPoolWork.h"

CThreadPoolWork::CThreadPoolWork()
{
}

CThreadPoolWork::CThreadPoolWork( int nPoolSize )
    : CThreadPool( nPoolSize )
{
}

CThreadPoolWork::~CThreadPoolWork()
{
}

ThreadBase* CThreadPoolWork::findThread( ThreadBase *pThread )
{
    return CThreadPool::findThread( pThread );
}
