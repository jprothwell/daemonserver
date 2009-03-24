#ifndef _CTHREADPRIVATE_H_
#define _CTHREADPRIVATE_H_

#include "sysinclude.h"
#include "CMutexPrivate.h"
#include "CCondPrivate.h"
#include "threadtype.h"

class CThread;
class Event;

class CThreadPrivate
{
public:
    CThreadPrivate();
    ~CThreadPrivate();

    bool init( CThread* that );
    bool wakeUp();
    bool exit();
    bool forceWait();

    bool isRunning(){ return mbRunning; }
    bool isFinish(){ return mbFinish; }
    bool isWaiting(){ return mbWaiting; }

    static bool internalRun( CThreadPrivate* t );
	bool dispatchEvent( Event &event );

private:
    CMutexPrivate* mpMutex;
    CCondPrivate*  mpCond;
    
private:
    pthread_t     mThreadID;
    bool          mbRunning;
    bool          mbFinish;
    bool          mbWaiting;
    bool          mbExist;

private:
    CThread *mpThread;
};

#endif
