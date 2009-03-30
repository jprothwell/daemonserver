#ifndef _CSHM_H_
#define _CSHM_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <memory>

using namespace std;

enum SHM_FLAGS
{
   	SHM_CREATE = 0x01,
   	SHM_OPEN   = 0x02,
   	SHM_READ   = 0x04,
   	SHM_WRITE  = 0x08
};

enum SHM_STATUS_FLAGS
{
	SHM_OK = 0x10,
	SHM_ERROR = 0x20
};
typedef SHM_STATUS_FLAGS SHM_STATUS;

class CShm
{
public:
    CShm( int id=-1, int flags=SHM_CREATE|SHM_READ|SHM_WRITE );
    CShm( int id, int size, int flag );
    ~CShm();

    bool destroy();

    int getID() const { return mShmId; }
    void* getAddr() const { return mpShmAddr; }
    int getSize() const { return mShmSize; }
	SHM_STATUS shmStatus() const 
	{ 
		if( (mShmId>0)&&(((int)mpShmAddr)>0) )
			return SHM_OK;
		else
			return SHM_ERROR;
	}

	const CShm& operator <<( const char* str ) const
	{
		if( NULL!=mpShmAddr )
			strcpy( (char*)mpShmAddr, str );
		return *this;
	}
	const CShm& operator >>( char *input ) const
	{
		if( NULL!=mpShmAddr )
			strcpy( input, (char*)this->getAddr() );
		return *this;
	}

private:
    bool init( int id, int size, int flags );

private:
    int     mShmId;
    void*   mpShmAddr;
    int     mShmSize;
	int 	mShmStatus;

    //auto_ptr<shmid_ds> mpShmDs;
    shmid_ds* mpShmDs;
    int mFlags;
};



#endif
