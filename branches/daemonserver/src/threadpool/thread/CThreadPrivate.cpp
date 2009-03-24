#include "CThread.h"
#include "CThreadPrivate.h"

extern "C" { static void* start_thread( void* t ); }

CThreadPrivate::CThreadPrivate()
{
    mpMutex = new CMutexPrivate();
    mpCond = new CCondPrivate( mpMutex );
    mThreadID = 0;
    mbRunning = false;
    mbFinish = false;
    mbWaiting = false;
    mpThread = NULL;
    mbExist = false;
}

CThreadPrivate::~CThreadPrivate()
{
    //delete mpThread;
    delete mpMutex;
    delete mpCond;
}

bool CThreadPrivate::init( CThread* that )
{
    if( true==mbExist )
        return true;

    mpThread = that;
    pthread_attr_t attr;
    pthread_attr_init( &attr );
    pthread_attr_setdetachstate(  &attr, PTHREAD_CREATE_DETACHED );

    int err = pthread_create( &mThreadID, &attr, start_thread, (void*)this );

    pthread_attr_destroy( &attr );

    if( 0!=err )
    {
        perror("Create Thread failure\n");
        return false;
    }
    mbExist = true;
	
	IdleEvent event;
	mpThread->dispatchEvent( event );

    return true;
}

bool CThreadPrivate::wakeUp()
{
    if( false==mbExist )
        return false;

    if( false==mbWaiting ) 
        return true;

    LOG_T("CThreadPrivate::wakeUp()");
    mpMutex->lock();
    mpCond->wakeUp();
    mpMutex->unlock();

    return true;
}

bool CThreadPrivate::exit()
{
    if( true==mbExist )
        pthread_cancel( mThreadID );

    mbExist = false;
    return true;
}

bool CThreadPrivate::forceWait()
{
    LOG_T("CThreadPrivate::forceWait()");
    if( false==mbExist )
        return false;

    if( true==mbWaiting )
        return true;

   int ret = pthread_kill( mThreadID, SIGUSR1 ); 

   if( 0==ret )
        return true;
   else
        return false;
}

bool CThreadPrivate::dispatchEvent( Event &event )
{
	mpThread->dispatchEvent( event );
}

static pthread_once_t once_ctrl;
static pthread_key_t mutex_key;
static pthread_key_t cond_key;
static pthread_key_t waiting_key;

extern "C"
{
    static void initKey()
    {
        pthread_key_create( &mutex_key, NULL );
        pthread_key_create( &cond_key, NULL );
        pthread_key_create( &waiting_key, NULL );
    }
}

extern "C"
{
    static void thread_suspend( int a )
    {
        LOG_T(" thread_suspend");
        CMutexPrivate *pMutex = static_cast<CMutexPrivate*>(pthread_getspecific( mutex_key ));
        CCondPrivate *pCond = static_cast<CCondPrivate*>(pthread_getspecific( cond_key ));
        bool *pWaiting = static_cast<bool*>(pthread_getspecific( waiting_key ));
        pMutex->lock();
        *pWaiting = true;
        pCond->wait();
        *pWaiting = false;
        pMutex->unlock();
    }
}

bool CThreadPrivate::internalRun( CThreadPrivate* t )
{
    pthread_once( &once_ctrl, initKey );
    pthread_setspecific( mutex_key, static_cast<void*>(t->mpMutex) );
    pthread_setspecific( cond_key, static_cast<void*>(t->mpCond) );
    pthread_setspecific( waiting_key, static_cast<void*>(&(t->mbWaiting)));

    signal( SIGUSR1, thread_suspend );

    if( THREAD_CREATE_IDLE & t->mpThread->mThreadFlags )
    {
        while( 1 )
        {
            LOG_T("internal thread before wait");
            t->mpMutex->lock();
            t->mbWaiting = true;
            t->mpCond->wait();
            t->mpMutex->unlock();
        
            t->mbFinish = false;
            t->mbWaiting = false;
            t->mbRunning = true;
            t->mpThread->run();
            t->mbRunning = false;
            t->mbFinish = true;
			JobDoneEvent event;
			t->dispatchEvent( event );
        }
    }
    else if( THREAD_CREATE_RUN & t->mpThread->mThreadFlags )
    {
        t->mbFinish = false;
        t->mbRunning = true;
        t->mpThread->run();
        t->mbRunning = false;
        t->mbFinish = true;
    }
    
    LOG_T("thread exit finish : "<<t->mbFinish);
    t->mbExist = false;
	CancelEvent event;
	t->dispatchEvent( event );

    return true;
}


extern "C"
{
    static void* start_thread( void* t )
    {
        CThreadPrivate::internalRun( (CThreadPrivate*)t );
        return 0;
    }
}







