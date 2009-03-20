#include "CInvoker.h"
#include "CBuilder.h""

#include "CLog.h"
//#include "CThread.h"

#include "CSocketClient.h"
#include "CSocketServer.h"

#include "CShm.h"

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

CSocketClient* getSockServer( short port )
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
    
    int id = atoi(argc[1]);
    LOGMAIN("id = "<<id);

    CShm *p = new CShm( id, 0 );
    LOGMAIN("open the shm "<< p->getID());
    char* data = (char*)p->getAddr();

    
    //for(int i=0; i<1024; i++)
      //  data[i] = 1;
    //    printf(" p[%d]:%d ", i, data[i]);
        
     
    while(1)
        ;
/*
    LOGMAIN("Begin the client test");
    set_new_handler( my_new_handler );

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

    short port = serverPort( CONFIG_FILE );
    CSocketClient *pClient = getSockServer( port );
    
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
    
    //char *buf = "client send test";
    char* buf = new char[100];
    memset( buf, 0, 100 );
    sprintf( buf, "client send test pid:%d", getpid());

    while(1)
    {
        sleep(5);
        int sendsize = pClient->sendData( buf, 100 );
        if( -1!=sendsize )
        {
            LOGMAIN("client send data success");
        }
        else
        {
            LOGMAIN("client send data failed");
        }

    }
*/  
    return 1;
}
