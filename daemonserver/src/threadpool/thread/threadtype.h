#ifndef _THREADTYPE_H_
#define _THREADTYPE_H_

enum ThreadCreateAttr
{
    THREAD_DEATCH = 0x01,
    THREAD_JOINABLE = 0x02,
    THREAD_CREATE_IDLE = 0x04,
    THREAD_CREATE_RUN = 0x08
};

typedef unsigned int TFlags;

#define DEBUG_THREAD
#ifdef DEBUG_THREAD
    #include <iostream>
    using namespace std;
    #define LOG_T(msg)  cout<<msg<<endl;
#else
    #define LOG_T(msg)
#endif

#endif
