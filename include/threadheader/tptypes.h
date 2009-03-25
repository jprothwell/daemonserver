#ifndef _TPTYPES_H_
#define _TPTYPES_H_

class MyThread;

typedef MyThread ThreadBase;
typedef ThreadBase* INTERJOB;

typedef void* (*WORK)(void *parm);
typedef void*  WORKPARM;

#endif
