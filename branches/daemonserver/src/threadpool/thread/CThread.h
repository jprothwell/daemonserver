#ifndef _CTHREAD_H_
#define _CTHREAD_H_

#include "threadtype.h"
#include <memory>
#include "debug.h"

using namespace std;

class CThreadPrivate;

////////////////////////////////////////////////
// event interface
////////////////////////////////////////////////
enum EventID
{
	BASE_EVENT = 1,
	START_EVENT,
	STOP_EVENT,
	RUN_EVENT,
	CANCEL_EVENT,
	JOBDONE_EVENT,
	IDLE_EVENT
};

class Event
{
public:
	Event(){ setEventID(BASE_EVENT); }
	~Event(){}

	bool isEvent( int eventID ) const { return ID==eventID; }

#ifdef DEBUG_THREAD
	int getEvent() const { return ID; }
#endif

protected:
	void setEventID( int eventID ){ ID=eventID; }

private:
	int ID;
};

class StartEvent : public Event
{
public:
	StartEvent(){ setEventID(START_EVENT); }
	~StartEvent(){}
};

class StopEvent : public Event
{
public:
	StopEvent(){ setEventID(STOP_EVENT); }
	~StopEvent(){}
};

class RunEvent : public Event
{
public:
	RunEvent(){ setEventID(RUN_EVENT); }
	~RunEvent(){}
};

class CancelEvent : public Event
{
public:
	CancelEvent(){ setEventID(CANCEL_EVENT); }
	~CancelEvent(){}
};

class IdleEvent : public Event
{
public:
	IdleEvent(){ setEventID(IDLE_EVENT); }
	~IdleEvent(){}
};

class JobDoneEvent : public Event
{
public:
	JobDoneEvent(){ setEventID(JOBDONE_EVENT); }
	~JobDoneEvent(){}
};

////////////////////////////////////////////

////////////////////////////////////////////
// state interface
// /////////////////////////////////////////
enum ThreadState
{
	NG = 1, 
	IDLE = 2,
	READY,
	RUNNING,
	STOPED,
	CANCEL,
	JOBDONE = 2
};

typedef int StateFlags;

class StateEvent
{
	friend class CThread;
public:
	StateEvent(){}
	~StateEvent(){}
	
	bool isState( StateFlags s ) const { return s==State; }

private:
	void setState( StateFlags s ){ State=s; }
	StateFlags State;
};
///////////////////////////////////////////

class CThread
{
    friend class CThreadPrivate;
public:
    explicit CThread( TFlags f=THREAD_DEATCH|THREAD_CREATE_IDLE );
    virtual ~CThread();

	bool dispatchEvent( const Event &event );
	StateEvent getState();

protected:
    virtual void run() = 0;
    static void sleep( unsigned long secs );
    static void msleep( unsigned long msecs );

public:
    bool start();
    bool resume();
    bool stop();
    bool cancel();
    bool jobDone();
    //bool wait();

private:
	//CThreadPrivate *mpThreadPrivate;
	auto_ptr<CThreadPrivate> mpThreadPrivate;
    TFlags          mThreadFlags;
	StateFlags      mCurState;

private:
    CThread( const CThread &s );
    CThread& operator =( const CThread &s );
};

#endif
