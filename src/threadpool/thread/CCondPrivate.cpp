#include "CCondPrivate.h"
#include "CMutexPrivate.h"

CCondPrivate::CCondPrivate( CMutexPrivate* pMutex )
{
    pthread_cond_init( &mCond, NULL );
    mpMutex = pMutex;
}

CCondPrivate::~CCondPrivate()
{
    pthread_cond_destroy( &mCond );
}

bool CCondPrivate::wait()
{
    pthread_cond_wait( &mCond, &(mpMutex->mMutex) );
    return true;
}

bool CCondPrivate::wakeUp()
{
    pthread_cond_signal( &mCond );
    return true;
}
