#ifndef _XML_OP_H_
#define _XML_OP_H_

#include <memory>

class TiXmlDocument;

enum XML_Status
{
    PARSE_DONE = 0x01,
    PARSE_FAILED = 0x02,
    ELEMENT_OK = 0x04,
    ELEMENT_NOT_EXIST = 0x08,
    ATTR_OK = 0x10,
    ATTR_NOT_EXIST = 0x20
};

class XML_op
{
public:
    explicit XML_op( const string &filename );
    explicit XML_op( const char* input );
    XML_op();
    ~XML_op();

    bool getAttrValue( const string &elm, const string &attr, int &value );
    bool getAttrValue( const string &elm, const string &attr, double &value );
    //bool getAttrValue( const string &elm, const string &attr, string &value );

    bool addElm( const string &elm );
    bool addAttr( const string &elm, const string &attr, const int &value );
    bool addAttr( const string &elm, const string &attr, const double &value );
    bool addAttr( const string &elm, const string &attr, const string &value );

    bool addText( const string &elm, const string &text );

    bool dumpXMl( char* outPut, int Size=0 );

private:
    auto_ptr<TiXmlDocument> pDoc;
    int mStatus;
};

#endif
