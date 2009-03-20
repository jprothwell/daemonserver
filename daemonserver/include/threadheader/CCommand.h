#ifndef  _CCOMMAND_H_
#define _CCOMMAND_H_

class CJob;

class CCommand
{
public:
    CCommand();
    virtual ~CCommand();

    virtual int excute( CJob *pJob );
    virtual int cancel( CJob *pJob );

    virtual int stop( CJob *pJob );
    virtual int resume( CJob *pJob );

    virtual int status( CJob *pJob );

private:

};

#endif
