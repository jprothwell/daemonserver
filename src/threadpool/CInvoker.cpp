#include "CInvoker.h"
#include "CLog.h"

CInvoker::CInvoker( CCommand *pCmd )
    : mpCommand( pCmd )
{
    LOG("create the Involer");
}

CInvoker::~CInvoker()
{
    delete mpCommand;
}

int CInvoker::startJob( CJob *pJob )
{
    if( NULL!=pJob )
        return mpCommand->excute( pJob );
    return JOB_ERROR;
}
 
int CInvoker::cancelJob( CJob *pJob )
{
    if( NULL!=pJob )
        return mpCommand->cancel( pJob );
    return JOB_ERROR;
}

int CInvoker::stopJob( CJob *pJob )
{
    if( NULL!=pJob )
        return mpCommand->stop( pJob );
    return JOB_ERROR;
}

int CInvoker::resumeJob( CJob *pJob )
{
    if( NULL!=pJob )
        return mpCommand->resume( pJob );
    return JOB_ERROR;
}

int CInvoker::getJobStatus( CJob *pJob )
{
    if( NULL!=pJob )
        return mpCommand->status( pJob );
    return JOB_NOT_EXIST;
}
