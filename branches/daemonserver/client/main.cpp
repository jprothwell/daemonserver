#include "CInvoker.h"
#include "CBuilder.h""

#include "CLog.h"
//#include "CThread.h"

#include "CSocketClient.h"
#include "CSocketServer.h"

#include "CShm.h"
#include "syscom.h"

#include <iostream>
using namespace std;

#define DEBUG_MAIN

#ifdef DEBUG_MAIN
#define LOGMAIN(msg) cout<<msg<<endl;
#else
#define LOGMAIN(msg)
#endif

#include "tinyxml.h"
#include "tinystr.h"
#define CONFIG_FILE "../config/set.xml"
#define DEFAULT_PORT 9000

void my_new_handler()
{
    cout<<"there is not enough memory"<<endl;
    exit( EXIT_FAILURE );
}

CSocketClient* getSockClient( short port )
{
    static CSocketClient* gClient = NULL;
    if( NULL==gClient )
        gClient = new CSocketClient( port );
    
    return gClient;
}

short serverPort( const char* filePath )
{

    TiXmlDocument config( filePath );
    if( false==config.LoadFile())
    {
        LOGMAIN("load setting file failed");
        return DEFAULT_PORT;
    }

    TiXmlNode *pNode = config.FirstChild( "ServerSetting" );
    if( NULL==pNode )
        return -1;
    TiXmlElement *pElm = pNode->ToElement();
    if( NULL==pElm )
        return -1;

    int ret = -1;
    if( TIXML_SUCCESS==pElm->QueryIntAttribute("port", &ret) )
    {
        return static_cast<short>(ret);
    }

    return -1;
}

void* p(void* parm)
{
    while(1)
    {
        sleep(1);
        printf("======= in the really job =========\n");
    }
}

void* p2(void* param)
{
    while(1)
    {
        sleep(1);
        printf("######### in the really job 2 ###########\n");
    }
}


int main( int argv, char** argc )
{
    LOGMAIN("Begin the client test");
    set_new_handler( my_new_handler );

/*
    LOGMAIN("Begin create the ThreadPool for the server to use");
    CBuilder builder;
    bool ret = builder.createProduct();
    if( false==ret )
    {
        cout<<"Create ThreadPool Failed"<<endl;
        exit( EXIT_FAILURE );
    }
    CInvoker *pInvoker = builder.getProduct();
    LOGMAIN("End create the ThreadPool");
*/
    short port = serverPort( CONFIG_FILE );
    CSocketClient *pClient = getSockClient( port );
    
    LOGMAIN("client::before connect");
    bool con = pClient->connectToServer();
    if( true==con )
    {
        LOGMAIN("CONNECT server success");
    }
    else
    {
        LOGMAIN("CONNECT server failed");
    }
    
    //while(1)
    //{
        
        sleep(5);
        char sendbuf[50];
        memset(sendbuf, 0, 50);
        strcpy( sendbuf, GET_SM );
        int sendsize = pClient->sendData( sendbuf, 50 );
        if( -1!=sendsize )
        {
            LOGMAIN("client send data success");
        }
        else
        {
            LOGMAIN("client send data failed");
        }

    //}
    char recvBuf[50];
    memset(recvBuf, 0, 50);
    int recved = pClient->recvData( recvBuf, 50 );
    if( recved >0 )
    {
        LOGMAIN("recv the data from server ok"<<recvBuf);
    }

    int shareID = atoi( recvBuf );
    CShm* pShm = new CShm( shareID, 0 );
    if( NULL!=pShm )
    {
        char* addr = (char*)pShm->getAddr();
        if( NULL!=addr )
        {
            printf("shared Info : %s\n", addr );
        }
    }
    else
    {
        printf("new shm failed\n");
    }
    while(1)
        ;
    

    return 1;

}
