#include "CThreadPool.h"
#include "MyThread.h"
#include "CLog.h"

CThreadPool::CThreadPool( int nStackSize )
    : mnStackSize( nStackSize )
{
}

CThreadPool::~CThreadPool()
{
    
}

bool CThreadPool::addThread( ThreadBase *pThread )
{
    LOG("add a thread");
    if( mThreadPoolStack.size()<mnStackSize )
    {
        mThreadPoolStack.push_back( pThread );
        return true;
    }
    
    return false;
}

bool CThreadPool::delThread( ThreadBase *pThread )
{
    LOG("delete a thread");
    if( mThreadPoolStack.size()>0 )
    {
        ThreadStack::iterator it;
        for(it=mThreadPoolStack.begin(); it<mThreadPoolStack.end(); it++)
        {
            if( (*it)==pThread )
            {
                mThreadPoolStack.erase( it );
                return true;
            }
        }
        
    }

    return false;
}

ThreadBase* CThreadPool::popThread()
{
    if( mThreadPoolStack.size()>0 )
    {
        ThreadBase *pRet = mThreadPoolStack[mThreadPoolStack.size()-1];
        //mThreadPoolStack.pop_back();

        return pRet;
    }

    return NULL;
}

ThreadBase* CThreadPool::findThread( ThreadBase *pThread )
{
    ThreadStack::iterator it;
    for( it=mThreadPoolStack.begin(); it<mThreadPoolStack.end(); it++ )
    {
        if( pThread==(*it) )
            return *(it);
    }

    return NULL;
}

ThreadBase* CThreadPool::getFirstIdleThread()
{
    ThreadStack::iterator it;
    for( it=mThreadPoolStack.begin(); it<mThreadPoolStack.end(); it++ )
    {
        if( true==(*it)->jobDone() )
            return (*it);
    }

    return NULL;
}
