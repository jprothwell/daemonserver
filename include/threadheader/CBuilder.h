#ifndef _CBUILDER_H_
#define _CBUILDER_H_

#include "CInvoker.h"
#include "CCommand.h"
#include "CCommandJob.h"
#include "CThreadManager.h"
#include "CDefine.h"

class CBuilder
{
public:
    CBuilder();
    virtual ~CBuilder();

    bool createProduct();
    CInvoker* getProduct(){ return mpInvoker; }

private:
    CInvoker *mpInvoker;
    CCommand *mpCommand;
    CThreadManager *mpThreadManager;
};

#endif
