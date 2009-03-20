#ifndef _CSOCKETSERVER_H_
#define _CSOCKETSERVER_H_

#include "CTypes.h"
#include "CSocket.h"

class CSocketServer : public CSocket
{
public:
    explicit CSocketServer( short port, int maxConnectCount=20, int STREAMTYPE=TCP_STREAM );
    virtual ~CSocketServer();

    int wait();
    int recvData( int waitRetCode, char* buf, int bufSize );
    int sendData( int waitRetCode, char* buf, int bufSize );

protected:
    virtual bool Init();

private:
    int miMaxConnectCount;
    int miCurConnectCount;
    socklen_t msinSize;
    struct sockaddr_in msServerAddr;
};

#endif
