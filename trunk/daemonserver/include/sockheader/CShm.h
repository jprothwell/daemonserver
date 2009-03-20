#ifndef _CSHM_H_
#define _CSHM_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

enum SHM_FLAGS
{
    SHM_CREATE = 0x01,
    SHM_OPEN   = 0x02,
    SHM_READ   = 0x04,
    SHM_WRITE  = 0x08
};

class CShm
{
public:
    CShm( int id=-1, int flags=SHM_CREATE|SHM_READ|SHM_WRITE );
    CShm( int id, int size, int flag );
    ~CShm();

    bool destroy();

    int getID(){ return mShmId; }
    void* getAddr(){ return mpShmAddr; }
    int getSize(){ return mShmSize; }

private:
    bool init( int id, int size, int flags );

private:
    int     mShmId;
    void*   mpShmAddr;
    int     mShmSize;

    shmid_ds* mpShmDs;
    int mFlags;
};


#endif
