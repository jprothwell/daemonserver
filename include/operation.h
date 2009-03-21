#ifndef _OPERATION_H_
#define _OPERATION_H_

CShm* getShm();

void createXML();
int addAttr( const string elm, const string attr, const int value );
int addElement( const string elm );
void writeXML_File( );

bool GetInfoFromXml( const string &file, const string &elm, const string &attr, int &value );
bool GetInfoFromXml( const string &file, const string &elm, const string &attr, double &value );
bool GetInfoFromXml( const string &file, const string &elm, const string &attr, string &value );

#endif
