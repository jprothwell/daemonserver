#ifndef  _CJOB_H_
#define _CJOB_H_

#include "CDefine.h"

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
