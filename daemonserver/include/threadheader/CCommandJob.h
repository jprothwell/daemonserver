#ifndef  _CCOMMANDJOB_H_
#define _CCOMMANDJOB_H_

#include <map>
#include "CCommand.h"
#include "CThreadManager.h"
#include "CJob.h"
#include "CDefine.h"

using namespace std;

class CThreadManager;

class CCommandJob : public CCommand
{
public:
    CCommandJob( CThreadManager *pThreadManager );
    virtual ~CCommandJob();

    virtual int excute( CJob *pJob );
    virtual int cancel( CJob *pJob );
    
    virtual int stop( CJob *pJob );
    virtual int resume( CJob *pJob );

    virtual int status( CJob *pJob );
private:
    CThreadManager *mpThreadManager;

    struct InterJobInfo
    {
        INTERJOB   jobID;
        int        jobStatus;
    };

    typedef map<CJob*, InterJobInfo*> JobMap;
    JobMap         mJobMap;
};


#endif
