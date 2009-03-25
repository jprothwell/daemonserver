#include "CBuilder.h"
#include "CCommandJob.h"
#include "CInvoker.h"
#include "CThreadManager.h"

CBuilder::CBuilder()
{
    mpInvoker = NULL;
    mpCommand = NULL;
    mpThreadManager = NULL;
}

CBuilder::~CBuilder()
{
    delete mpInvoker;
    delete mpCommand;
    delete mpThreadManager;
}

bool CBuilder::createProduct()
{
    mpThreadManager = new CThreadManager();
    mpCommand = new CCommandJob( mpThreadManager );
    mpInvoker = new CInvoker( mpCommand );

    return true;
}


