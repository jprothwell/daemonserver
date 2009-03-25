#include "CCommand.h"
#include "tptypes.h"
#include "CJob.h"

class CJob;

CCommand::CCommand()
{
}

CCommand::~CCommand()
{
}

int CCommand::excute( CJob *pJob )
{
    return JOB_ERROR;
}

int CCommand::cancel( CJob *pJob )
{
    return JOB_ERROR;
}

int CCommand::stop( CJob *pJob )
{
    return JOB_ERROR;
}

int CCommand::resume( CJob *pJob )
{
    return JOB_ERROR;
}

int CCommand::status( CJob *pJob )
{
    return JOB_ERROR;
}
