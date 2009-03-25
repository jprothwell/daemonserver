#ifndef  _INVOKER_H_
#define _INVOKER_H_

class CCommand;
class CJob;

class CInvoker
{
public:
    CInvoker( CCommand *pCmd );
    virtual ~CInvoker();
    
    int startJob( CJob *pJob );
    int cancelJob( CJob *pJob );

    int stopJob( CJob *pJob );
    int resumeJob( CJob *pJob );
    
    int getJobStatus( CJob *pJob );

private:
    CCommand *mpCommand;
};

#endif
