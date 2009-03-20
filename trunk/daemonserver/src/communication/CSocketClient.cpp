#include "CSocketClient.h"
#include <stdio.h>

CSocketClient::CSocketClient( short port, int STREAMTYPE )
    : CSocket( port, STREAMTYPE )
{
}

CSocketClient::~CSocketClient()
{
}

bool CSocketClient::connectToServer()
{
    msServerAddr.sin_family = AF_INET;
    msServerAddr.sin_port = htons( getPort() );
    inet_aton( "127.0.0.1", &msServerAddr.sin_addr );
    bzero( &(msServerAddr.sin_zero), 8 );

    if( -1==connect(getSocketFD(), (struct sockaddr*)&msServerAddr, sizeof(struct sockaddr)) )
    {
        printf("Clinet::connect server error\n");
        return false;
    }

    return true;
}

int CSocketClient::sendData( char* buf, int bufSize )
{
    if( NULL==buf )
    {
        return 0;
    }

    int ret = -1;
    if( -1==(ret=send(getSocketFD(), buf, bufSize, 0)) )
    {
        printf("Client::send the data error\n");
        return -1;
    }

    return ret;
}
