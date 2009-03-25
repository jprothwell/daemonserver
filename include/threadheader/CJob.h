#ifndef  _CJOB_H_
#define _CJOB_H_

#include "tptypes.h"

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

class CJob
{
public:
    CJob();
    ~CJob();

    void setJobID( int jobID ){ mbJobID=jobID; }
    int  getJobID(){ return mbJobID; }
    void setWork( WORK pwork ){ workProcess=pwork; }
    void setWorkParm( WORKPARM pworkParm ){ workParm=pworkParm; }

public:
    WORK workProcess;
    WORKPARM workParm;

private:
    int mbJobID;
    
};

#endif
