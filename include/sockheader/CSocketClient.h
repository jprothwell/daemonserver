#ifndef _CSOCKETCLIENT_H_
#define _CSOCKETCLIENT_H_

#include "CTypes.h"
#include "CSocket.h"

class CSocketClient : public CSocket
{
public:
    CSocketClient( short port, int STREAMTYPE=TCP_STREAM );
    virtual ~CSocketClient();

    bool connectToServer();
    int recvData( char* buf, int bufszie );
    int sendData( char* buf, int bufSize );

private:
    struct sockaddr_in msServerAddr;
};

#endif
