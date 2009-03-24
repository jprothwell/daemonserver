#include "CCommandJob.h"
#include "CThreadManager.h"
#include "CLog.h"

CCommandJob::CCommandJob( CThreadManager *pThreadManager )
    :   CCommand() ,
        mpThreadManager( pThreadManager )
{
    LOG("Create the Command Job object");
}

CCommandJob::~CCommandJob()
{
    LOG("Destory the Command Job");
    JobMap::iterator it;
    for( it=mJobMap.begin(); it!=mJobMap.end(); ++it )
    {
        delete (*it).second;
    }

    mJobMap.clear();
}

int CCommandJob::excute( CJob *pJob )
{
    if( NULL==mpThreadManager )
        return JOB_ERROR;

    InterJobInfo* jobInfo = mJobMap[pJob];
    if( jobInfo>0 )
    {
        LOG("The job is exist!");
        return JOB_EXIST;
    }
    else
    {
        INTERJOB jobId = mpThreadManager->newWork( pJob->workProcess, pJob->workParm );
        //LOG("CCommandJob::start the work success="<<jobInfo->jobID);
        if( jobId>0 )
        {
            mJobMap[pJob] = new InterJobInfo();
            mJobMap[pJob]->jobID = jobId;
            mJobMap[pJob]->jobStatus = JOB_READY;
        }
        else
        {
            mJobMap.erase( pJob );
            return JOB_ERROR;
        }
    }

    return JOB_READY;
}
  
int CCommandJob::cancel( CJob *pJob )
{
    if( NULL==mpThreadManager )
        return JOB_ERROR;

    InterJobInfo* jobInfo = mJobMap[pJob];
    bool ret = false;
    if( jobInfo>0 )
    {
        LOG("cancel the job");
        ret = mpThreadManager->cancelWork( jobInfo->jobID );
    }

    if( true==ret )
    {
        delete mJobMap[pJob];
        mJobMap.erase( pJob );
    }

    return true==ret?JOB_DONE:JOB_ERROR;
}

int CCommandJob::stop( CJob *pJob )
{
    if( NULL==mpThreadManager )
        return JOB_ERROR;

    InterJobInfo* jobInfo = mJobMap[pJob];
    LOG("CommandJob::stop the job : "<<jobInfo->jobID);
    bool ret = false;
    if( jobInfo>0 )
        ret = mpThreadManager->stopWork( jobInfo->jobID );

    if( true==ret )
        jobInfo->jobStatus = JOB_STOP;
    else
        jobInfo->jobStatus = JOB_ERROR;

    return true==ret?JOB_STOP:JOB_ERROR;
}

int CCommandJob::resume( CJob *pJob )
{
    if( NULL==mpThreadManager )
        return JOB_ERROR;

    InterJobInfo* jobInfo = mJobMap[pJob];
    bool ret = false;
    if( jobInfo>0 )
        ret = mpThreadManager->resumeWork( jobInfo->jobID );

    if( true==ret )
        jobInfo->jobStatus = JOB_RUNNING;
    else
        jobInfo->jobStatus = JOB_ERROR;

    return true==ret?JOB_RUNNING:JOB_ERROR;
}

int CCommandJob::status( CJob *pJob )
{
    if( NULL==mpThreadManager )
        return JOB_NOT_EXIST;
    
    return NULL!=mJobMap[pJob]?mJobMap[pJob]->jobStatus:JOB_NOT_EXIST;
}
