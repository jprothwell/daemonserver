#ifndef _SYSCOM_H_
#define _SYSCOM_H_

const char* GET_SM = "get share memory";
const char* CONNECT_SM_SUCCESS = "connect share memory sucess";
const char* CONNECT_SM_FAILED = "connect share memory failed";
const char* REQURE_WRITE_DATA = "want to write data in sm";
const char* WRITE_DONE = "write data in sm done";
const char* REQURE_READ_DATA = "want to read data in sm";
const char* READ_DONE = "read data in sm done";

const char* SHM_ID = "ID";
const char* SHM_ID_ELEMENT = "shareID";

const int ADD_ELEMENT_FAILED = 1;
const int ADD_ELEMENT_SUCCESS = 2;
const int ADD_ATTR_SUCCESS = 3;
const int ADD_ATTR_FAILED = 4;

#endif
