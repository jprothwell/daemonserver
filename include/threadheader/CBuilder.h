#ifndef _CBUILDER_H_
#define _CBUILDER_H_

class CInvoker;
class CCommand;
class CThreadManager;

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
