#include "CMutexPrivate.h"

CMutexPrivate::CMutexPrivate()
{
    pthread_mutex_init( &mMutex, NULL );
}

CMutexPrivate::~CMutexPrivate()
{
    pthread_mutex_destroy( &mMutex );
}

void CMutexPrivate::lock()
{
    pthread_mutex_lock( &mMutex );
    return;
}

void CMutexPrivate::unlock()
{
    pthread_mutex_unlock( &mMutex );
    return;
}
