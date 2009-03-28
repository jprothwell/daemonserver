#ifndef _DEBUG_THREAD_H_
#define _DEBUG_THREAD_H_

//#define DEBUG_THREAD
#ifdef DEBUG_THREAD
    #include <iostream>
    using namespace std;
    #define LOG_THREAD(msg)  do{ cout<<"Internal Thread LOG :: "<<msg<<endl; }while(0)
#else
    #define LOG_THREAD(msg)  do{}while(0)
#endif

#endif
