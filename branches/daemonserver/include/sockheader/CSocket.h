#ifndef _CSOCKET_H_
#define _CSOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

using namespace std;

class CSocket
{
public:
    CSocket( short port, int STREAMTYPE=SOCK_STREAM );
    virtual ~CSocket();

protected:
    virtual bool Init();
    int getSocketFD(){ return miSocketFD; }
    int getStreamType(){ return miStreamType; }
    short getPort(){ return msPort; }

    typedef vector<int> SOCK_LIST;
    SOCK_LIST mSockList;
    
private:
    int miStreamType;
    int miSocketFD; 
    short msPort;
};

#endif
