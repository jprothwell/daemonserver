#include "CSocketServer.h"
#include <stdio.h>
#include <sys/time.h>
#include <map>
#include <vector>

using namespace std;

typedef map<int, struct sockaddr_in *> SOCK_MAP;
static SOCK_MAP g_sockMap;

CSocketServer::CSocketServer( short port, int maxConnectCount, int STREAMTYPE )
    : CSocket( port, STREAMTYPE )
{
    miMaxConnectCount = maxConnectCount;
    miCurConnectCount = 0;
    
    if( false==Init() )
        exit(1);
}

CSocketServer::~CSocketServer()
{
}

bool CSocketServer::Init()
{
    int sockFD = getSocketFD();
    
    msServerAddr.sin_family = AF_INET;
    msServerAddr.sin_port = htons( getPort() );
    msServerAddr.sin_addr.s_addr = INADDR_ANY;
    bzero( &(msServerAddr.sin_zero), 8 );

    if( -1==bind(sockFD, (struct sockaddr *)&msServerAddr, sizeof(struct sockaddr)) )
    {
        perror("Server::bind socket error");
        return false;
    }

    if( -1==listen(sockFD, miMaxConnectCount) )
    {
        printf("Server::listen on the socket error\n");
        return false;
    }

    return true;
}

int CSocketServer::wait()
{
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    while( 1 )
    {
        fd_set rdfd;
        FD_ZERO( &rdfd );
        SOCK_LIST::iterator it;
        int iMaxSock = *(mSockList.begin());
        for( it=mSockList.begin(); it<mSockList.end(); it++ )
        {
            FD_SET( (*it), &rdfd );
            if( iMaxSock<=(*it) )
                iMaxSock = (*it);
        }

        int selectRet = select( iMaxSock+1, &rdfd, NULL, NULL, &timeout );

        switch( selectRet )
        {
        case -1:
            perror("select error");
            break;
        case 0:
            return -1;
            break;
        default:
            if( FD_ISSET(mSockList[0], &rdfd) )
            {
                struct sockaddr_in *clientAddr = new struct sockaddr_in();
                msinSize = sizeof(struct sockaddr_in);
                int ret = -1;
                if( -1==(ret=accept(getSocketFD(), (struct sockaddr*)clientAddr, &msinSize)) )
                    exit( EXIT_FAILURE );
                g_sockMap[ret] = clientAddr;
                miCurConnectCount++;
                mSockList.push_back( ret );
            }
            else
            {
                SOCK_LIST::iterator it;
                for( it=mSockList.begin(), it++; it<mSockList.end(); it++ )
                {
                    if( FD_ISSET((*it), &rdfd) )
                    {
                        int activeFD = (*it);
                        mSockList.erase( it );
                        return  activeFD;
                    }
                }
            }
        }//end of switch
    }

    return -1;
}

int CSocketServer::recvData( int waitRetCode, char* buf, int bufsize )
{
    int recvSize = -1;    
    if( -1==(recvSize=recv( waitRetCode, buf, bufsize, 0)))
    {
        printf("Server::recv data error\n");
        return -1;
    }

    return recvSize;
}

int CSocketServer::sendData( int waitRetCode, char* buf, int bufSize )
{
    int sendSize = -1 ;
    if( -1==(sendSize=send( waitRetCode, buf, bufSize, 0)))
    {
        printf("Server::send data error\n");
        return -1;
    }

    return sendSize;
}







