#ifndef  _CDEFINE_H_
#define  _CDEFINE_H_

typedef void* (*WORK)(void *parm);
typedef void*  WORKPARM;

class MyThread;

typedef MyThread ThreadBase;
typedef ThreadBase* INTERJOB;

enum Job_status
{
    JOB_ERROR = 1,
    JOB_READY,
    JOB_EXIST,
    JOB_NOT_EXIST,
    JOB_RUNNING,
    JOB_STOP,
    JOB_DONE
};

#endif
