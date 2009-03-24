#include "CThread.h"
#include "CThreadPrivate.h"

typedef EventID EVENT_ID;
typedef struct
{
	StateFlags curState;
	EVENT_ID   eventID;
	StateFlags nextState;
	bool (CThread::*fun)();
}State_Trans;

enum State_Trans_Index
{
	BEGIN = 0,
	IDLE_TO_RUN = 0,
	RUN_TO_STOP,
	STOP_TO_RUN,
	RUN_TO_CANCLE,
	RUN_TO_JOBDONE,
	NG_TO_IDLE,
	END
};

State_Trans state_trans_table[] = 
{
	{IDLE, START_EVENT, RUNNING, NULL},
	{RUNNING, STOP_EVENT, STOPED, NULL},
	{STOPED, RUN_EVENT, RUNNING, NULL},
	{RUNNING, CANCEL_EVENT, CANCEL, NULL},
	{RUNNING, JOBDONE_EVENT, JOBDONE, NULL},
	{NG, IDLE_EVENT, IDLE, NULL}
};

#define State_Count (sizeof(state_trans_table)/sizeof(state_trans_table[0]))

CThread::CThread( TFlags f )
	: mpThreadPrivate( new CThreadPrivate() )
{
    mThreadFlags = f;
	mCurState = NG;
	state_trans_table[IDLE_TO_RUN].fun = &CThread::start;
	state_trans_table[RUN_TO_STOP].fun = &CThread::stop;
	state_trans_table[STOP_TO_RUN].fun = &CThread::resume;
	state_trans_table[RUN_TO_CANCLE].fun = &CThread::cancel;
	state_trans_table[RUN_TO_JOBDONE].fun = &CThread::jobDone;
	state_trans_table[NG_TO_IDLE].fun = NULL;


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

bool CThread::dispatchEvent( const Event &event )
{
	LOG_T("receive the event"<<event.getEvent());
	for( int i=0; i<State_Count; i++ )
	{
        LOG_T("====CThread::compare the event====");
		if( (state_trans_table[i].curState==mCurState)&&(event.isEvent(state_trans_table[i].eventID)) )
		{

			bool fun_op = false;
			if( NULL!=state_trans_table[i].fun )	
			{
				LOG_T("invoke the event fun");
				bool (CThread::*p)() = state_trans_table[i].fun;
				fun_op = (this->*p)();
			}
            else
            {
                fun_op = true;
            }

			if( true==fun_op )
			{
				mCurState = state_trans_table[i].nextState;
				return true;
			}
		}

		continue;
	}
    LOG_T("+++ the event is not handle by the state machine ++++++");

	return false;
}

StateEvent CThread::getState()
{
	StateEvent event;
	event.setState( mCurState );

	return event;
}

/////////////////////////////////////////////////////////
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
    //if( NULL!=mpThreadPrivate.get() )
    //    return mpThreadPrivate->isFinish();
	mCurState = JOBDONE;

    return true;
}

void CThread::sleep( unsigned long secs )
{
    ::sleep( secs );
}

void CThread::msleep( unsigned long msecs )
{
    CThread::sleep( msecs*1000 );
}
