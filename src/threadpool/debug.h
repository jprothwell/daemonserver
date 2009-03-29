#ifndef _DEBUG_THREAD_POOL_H_
#define _DEBUG_THREAD_POOL_H_

//#define DEBUG_THREAD_POOL

#ifdef DEBUG_THREAD_POOL
	#include <iostream>
	using namespace std;

	#define LOG_TP(msg) do{ cout<<"Thread Pool Log :: "<<msg<<endl; }while(0)
#else
	#define LOG_TP(msg) do{}while(0)
#endif

#endif
