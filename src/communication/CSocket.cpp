#include "CSocket.h"

CSocket::CSocket( short port, int STREAMTYPE )
{
    miStreamType = STREAMTYPE;
    miSocketFD = socket( AF_INET, miStreamType, 0 );

    if( -1==miSocketFD)
        exit(1);

    mSockList.push_back( miSocketFD );
    msPort = port;
}

CSocket::~CSocket()
{
    close( miSocketFD );
}

bool CSocket::Init()
{
    return false;
}

