#ifndef _CTHREAD_H_
#define _CTHREAD_H_

#include "threadtype.h"
#include <memory>

class CThreadPrivate;

class CThread
{
    friend class CThreadPrivate;
public:
    explicit CThread( TFlags f=THREAD_DEATCH|THREAD_CREATE_IDLE );
    virtual ~CThread();

    bool start();
    bool resume();
    bool stop();
    bool cancel();

//status fun
public:
    bool jobDone();

    //bool wait();

protected:
    virtual void run() = 0;
    static void sleep( unsigned long secs );
    static void msleep( unsigned long msecs );

private:
	//CThreadPrivate *mpThreadPrivate;
	auto_ptr<CThreadPrivate> mpThreadPrivate;
    TFlags          mThreadFlags;

private:
    CThread( const CThread &s );
    CThread& operator =( const CThread &s );
};

#endif
