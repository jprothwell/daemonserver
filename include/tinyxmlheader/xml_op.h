#ifndef _XML_OP_H_
#define _XML_OP_H_

#include <memory>
#include <string>

using namespace std;

class TiXmlDocument;

enum XML_Status
{
    PARSE_DONE = 0x0001,
    PARSE_FAILED = 0x0002,
    ELEMENT_OK = 0x0004,
    ELEMENT_NOT_EXIST = 0x0008,
    ATTR_OK = 0x0010,
    ATTR_NOT_EXIST = 0x0020,
	ATTR_ADD_OK = 0x0040,
	ATTR_ADD_FAILED = 0x0080,
	ADD_TEXT_OK = 0x0100,
	ADD_TEXT_FAILED = 0x0200
};

class XML_op
{
public:
    explicit XML_op( const string &filename );
    //explicit XML_op( const char* input );
    XML_op();
    ~XML_op();

    bool getAttrValue( const string &elm, const string &attr, int &value );
    bool getAttrValue( const string &elm, const string &attr, double &value );
    //bool getAttrValue( const string &elm, const string &attr, string &value );

    bool addElm( const string &elm );
    bool addAttr( const string &elm, const string &attr, const int &value );
    bool addAttr( const string &elm, const string &attr, const double &value );
    //bool addAttr( const string &elm, const string &attr, const string &value );

    bool addText( const string &elm, const string &text );

    bool dumpXML( char* outPut, int Size=0 );

private:
    auto_ptr<TiXmlDocument> pDoc;
    int mStatus;
};

#endif
