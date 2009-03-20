#include "CThread.h"
#include "CThreadPrivate.h"


CThread::CThread( TFlags f )
	: mpThreadPrivate( new CThreadPrivate() )
{
    mThreadFlags = f;
    if( THREAD_CREATE_IDLE & f )
        mpThreadPrivate->init( this );
}

CThread::~CThread()
{
    if( true==mpThreadPrivate->isRunning() || true==mpThreadPrivate->isWaiting() )
    {
        LOG_T("CThread::thread exit");
        mpThreadPrivate->exit();
    }
    LOG_T("delete data");
}

bool CThread::start()
{
    if( NULL==mpThreadPrivate.get() )
        return false;

    if( THREAD_CREATE_RUN & mThreadFlags )
    {
        LOG_T("init the thread");
        return mpThreadPrivate->init( this );
    }
    else if( THREAD_CREATE_IDLE & mThreadFlags )
    {
        LOG_T("wakeup the thread");
        return mpThreadPrivate->wakeUp();
    }
    
    return false;
}

bool CThread::stop()
{
    if( NULL==mpThreadPrivate.get() )
        return false;
    
    if( mpThreadPrivate->isWaiting() && mpThreadPrivate->isRunning() )
        return true;

    if( mpThreadPrivate->isWaiting() && mpThreadPrivate->isFinish() )
        return false;

    return mpThreadPrivate->forceWait();
}

bool CThread::resume()
{
    if( NULL==mpThreadPrivate.get() )
        return false;
    
    if( mpThreadPrivate->isFinish() )
        return false;

    if( false==mpThreadPrivate->isWaiting() )
        return true;

    return mpThreadPrivate->wakeUp();
}

bool CThread::cancel()
{
    if( NULL==mpThreadPrivate.get()  )
        return false;

    if( mpThreadPrivate->isRunning() || mpThreadPrivate->isWaiting() )
    {
        mpThreadPrivate->exit();
        mpThreadPrivate.reset( 0 );

        return true;
    }

    return false;
}

bool CThread::jobDone()
{
    if( NULL!=mpThreadPrivate.get() )
        return mpThreadPrivate->isFinish();

    return false;
}

void CThread::sleep( unsigned long secs )
{
    ::sleep( secs );
}

void CThread::msleep( unsigned long msecs )
{
    CThread::sleep( msecs*1000 );
}
