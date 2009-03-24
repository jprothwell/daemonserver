#ifndef   _CLOG_H_
#define  _CLOG_H_

#include <iostream>

using namespace std;

#define DEBUG

#ifdef DEBUG
#define LOG(msg) cout<<msg<<endl;
#else
#define LOG(msg)
#endif

#endif
