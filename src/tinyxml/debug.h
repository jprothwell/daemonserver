#ifndef _DEBUG_H_
#define _DEBUG_H_

//#define DEBUG_XML

#ifdef DEBUG_XML
	#include <iostream>
	using namespace std;

	#define LOG_XML(msg) do{ cout<<"XML LOG :: "<<msg<<endl; }while(0)
#else
	#define LOG_XML(msg) do{}while(0)
#endif

#endif
