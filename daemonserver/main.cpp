//
//this is the test for the daemon server using the thread pool, socket and run as the daemon
//
#include "CInvoker.h"
#include "CBuilder.h"

#include "CSocketServer.h"

#include "CShm.h"
#include "syscom.h"

#include <iostream>
#include <memory>
#include <string>
using namespace std;

#define DEBUG_MAIN

#ifdef DEBUG_MAIN
#define LOGMAIN(msg) cout<<msg<<endl;
#else
#define LOGMAIN(msg)
#endif

#include "tinyxml.h"
#define CONFIG_FILE "./config/set.xml"
#define DEFAULT_PORT 9000

CShm* getShm();

static char XML[1024];
void createXML()
{
	memset( XML, 0, 1024 );
	strcpy( XML, "<?xml version=\"1.0\" standalone=\"no\" ?>\n" );
}

void addAttr( const string elm, const string attr, const int value )
{
	TiXmlDocument doc;
	doc.Parse( XML );
	TiXmlNode *pNode = doc.FirstChild( elm );
	TiXmlElement *pElm = pNode->ToElement();
	if( NULL!=pElm )
	{
		pElm->SetAttribute( attr, value );
	}
#ifdef DEBUG_MAIN
	doc.Print();
#endif

}

void addElement( const string elm )
{
	TiXmlDocument doc;
	doc.Parse( XML );
	TiXmlElement addElm( elm );
#ifdef DEBUG_MAIN
	doc.Print();
#endif
}

void writeXML_To_Shm()
{
	CShm* pShm = getShm();
	if( NULL!=pShm && -1!=pShm->getID() && NULL!=pShm->getAddr() )
		strcpy( (char*)pShm->getAddr(), XML );
}

struct recvJobStruct
{
    CSocketServer *pServer;
    int fd;
    char* buf;
    int size;
};

void doCommand( struct recvJobStruct* pJob ) 
{
	CShm* pShm = getShm();
	const string str( pJob->buf );
	if( GET_SM==str )
	{
		createXML();
		addElement( SHM_ID_ELEMENT );
		if( NULL==pShm )
			addAttr( SHM_ID_ELEMENT, SHM_ID, -1 );
		else
			addAttr( SHM_ID_ELEMENT, SHM_ID, pShm->getID() );
		
		writeXML_To_Shm();

		char sendBuf[50];
		memset( sendBuf, 0, 50 );
		strcpy( sendBuf, WRITE_DONE );
		int send = pJob->pServer->sendData( pJob->fd, sendBuf, 50 );
		if( send>0 )
		{
			LOGMAIN("send data from sock done");
		}
		else
		{
			LOGMAIN("send data from sock failed");
		}
		
	}
	else if( CONNECT_SM_SUCCESS==str )
	{
	}
	else if( CONNECT_SM_FAILED==str )
	{
	}
	else if( REQURE_WRITE_DATA==str )
	{
	}
	else if( WRITE_DONE==str )
	{
	}
	else if( REQURE_READ_DATA==str )
	{
	}
	else if( READ_DONE==str )
	{
	}
}


//this is the real job for the server to recv the data
void* recvjob( void *param )
{
    LOGMAIN("begin do the job\n");
    struct recvJobStruct* pRecvJob = (struct recvJobStruct*)param;
	char* buf = pRecvJob->buf;
    int recvsize = -1;
    int bRet = false;
    while(1)
    {
        recvsize = pRecvJob->pServer->recvData( pRecvJob->fd, buf, pRecvJob->size );
        
        switch(recvsize)
        {
        case -1:
            LOGMAIN("recv clinet data failed\n");
            bRet = true;
            break;
        case 0:
            LOGMAIN("client closed \n");
            bRet = true;
            break;
		default://recevie the client info
        	LOGMAIN("after get the data form client data=<<"<< buf );
			doCommand( pRecvJob );
        }
        if( true==bRet )
            break;
    }

    return NULL;
}

void my_new_handler()
{
    cout<<"there is not enough memory"<<endl;
    exit( EXIT_FAILURE );
}

CSocketServer* getSockServer( short port )
{
    static CSocketServer* gServer = NULL;
    if( NULL==gServer )
        gServer = new CSocketServer( port );
    
    return gServer;
}

CShm* getShm()
{
// create the share memory for the client and the server to communication
	static CShm *gShm = NULL;
	if( NULL==gShm )
    	CShm* gShm = new CShm();

    if( -1==gShm->getID() )
    {
        LOGMAIN("create shm failed");
		delete gShm;
    }
    else
	{
        LOGMAIN("shm id = "<<gShm->getID());
    	//char* p = (char*)(pShm->getAddr());
    	//LOGMAIN("The attchment address is :" << p);
	}

	return gShm;
// end of the share memory init
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

int main( int argv, char** argc )
{
    std::set_new_handler( my_new_handler );

	// begin the socket server init
    LOGMAIN("Begin create the ThreadPool for the server to use");
    CBuilder builder;
    bool ret = builder.createProduct();
    if( false==ret )
    {
        cout<<"Create ThreadPool Failed"<<endl;
        exit( EXIT_FAILURE );
    }
    auto_ptr<CInvoker> pInvoker( builder.getProduct() );
    LOGMAIN("End create the ThreadPool");

    LOGMAIN("Begin Create the sock server for use");
    short port = serverPort( CONFIG_FILE );
    if( -1==port )
    {
        LOGMAIN("get the server port error");
        exit( EXIT_FAILURE );
    }
    auto_ptr<CSocketServer> pSockServer( getSockServer( port ) );
    LOGMAIN("End Create the sock server");
	// end of the scoket server init

    int i = 0;
    while(1)
    {
       LOGMAIN("wait on the server");
       int ret = pSockServer->wait(); 
       if( -1!=ret )
       {
            LOGMAIN("There is a clinet connect the ser fd = "<<ret );
            struct recvJobStruct* p = new recvJobStruct();
            char* buf = new char[4096];
            p->pServer = pSockServer.get();
            p->fd = ret;
            p->buf = buf;
            p->size = 4096;

            CJob *pJob = new CJob();
            pJob->setJobID( i );
            pJob->setWork( recvjob );
            pJob->setWorkParm( (void*)p );
            i++;
            bool bStart = pInvoker->startJob( pJob );
            if( false==bStart )
            {
                perror("start the recv job failed\n");
            }
       }
    }

	return 1;
}

