#include "CShm.h"

const int DEFAULT_SIZE=4096;

CShm::CShm( int id, int flags )
{
    init( id, DEFAULT_SIZE, flags );
}

CShm::CShm( int id, int size, int flags )
{
    if( size<=0 )
        size = DEFAULT_SIZE;
    init( id, size, flags );
}

bool CShm::init( int id, int size, int flags )
{
    mpShmDs=new struct shmid_ds();
    if( -1==id )
    {
        //create a new shm
        if( flags&SHM_OPEN )
        {
            //if the sys need to create a new shm, but the flags is open. set the shmid to -1
            mShmId = -1;
            mShmSize = size;
            mFlags = flags;
            mpShmAddr = 0;
            
            return false;
        }
        else if( flags&SHM_CREATE )
        {
            //the flag is right for the sys to create the shmid
            mShmSize = size;
            mFlags = flags;
            mShmId = shmget( IPC_PRIVATE, mShmSize, IPC_CREAT|IPC_EXCL|0600 );
            if( -1!=mShmId )
                mpShmAddr = shmat( mShmId, 0, 0);
            
            if( mpShmAddr<0 )
                destroy();

            return true;
        }
    }
    else //if the id >0, the default active is open, now doesn't support create with the id>0
    {
        //using the existing shm with the flags
        mShmId = id;
        mShmSize = size;
        mFlags = flags;
        int flag = 0;
        if( (mFlags&SHM_READ) && !(mFlags&SHM_WRITE) )
            flag = SHM_RDONLY;

        if( mFlags&SHM_CREATE )
        {
            mShmId = -1;
            return false;
        }
        else// if( mFlags&SHM_OPEN ) the default is open
        {
            mpShmAddr = shmat( mShmId, 0, flag );
			printf("attach addr is : %d", mpShmAddr );
            if( ((int)mpShmAddr)<0 )
            {
				printf("attach the shm failed!\n");
                mShmId = -1;
                return false;
            }

            return true;
        }
    }

    return false;
}

CShm::~CShm()
{
    if( -1!=mShmId )
        shmdt( mpShmAddr );
}

bool CShm::destroy()
{
    int ret = -1;
    if( -1!=mShmId )
        ret = shmctl( mShmId, IPC_RMID, mpShmDs );
    
    if( 0==ret )
    {
        mShmId = -1;
        return true;
    }
    else if( -1==ret ) 
    {
        return false;
    }

    return false;
}
