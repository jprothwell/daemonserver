#include "xml_op.h"
#include "tinyxml.h"

typedef TiXmlNode Node;
typedef TiXmlElement Element;
typedef TiXmlDocument Document;

const char* XML_TITAL = "<?xml version=\"1.0\" standalone=\"no\" ?>\n";

XML_op::XML_op()
    : pDoc( new TiXmlDocument() )
{
    mStatus = PARSE_FAILED;
    if( NULL!=pDoc->Parse(XML_TITAL) )
    {
        mStatus = PARSE_DONE;
    }
}

XML_op::XML_op( const char* input )
    : pDoc( new TiXmlDocument() )
{
    mStatus = PARSE_FAILED;
    if( NULL!=pDoc->Parse(input) )
    {
        mStatus = PARSE_DONE;
    }    
}

XML_op::XML_op( const string &filename )
    : pDoc( new TiXmlDocument(filename) )   
{
    mStatus = PARSE_FAILED;
    if( true==pDoc->LoadFile() )
    {
        mStatus = PARSE_DONE;
    }
    
}

XML_op::~XML_op()
{
}

bool XML_op::getAttrValue( const string &elm, const string &attr, int &value )
{
    Node *pNode = pDoc->FirstChild( elm );
    if( NULL==pNode )
    {
        mStatus |= ELEMENT_NOT_EXIST;
        return false;
    }
    
    Element *pElm = pNode->ToElement();
    if( NULL==pElm )
    {
        mStatus |= ELEMENT_NOT_EXIST;
        return false;
    }

    int res = pElm->QueryIntAttribute( attr.c_str(), &value );
    if( TIXML_SUCCESS!=res )
    {
        mStatus |= ATTR_NOT_EXIST;
        return false;
    }

    return true;
}

bool XML_op::getAttrValue( const string &elm, const string &attr, double &value )
{
    Node *pNode = pDoc->FirstChild( elm );
    if( NULL==pNode )
    {
        mStatus |= ELEMENT_NOT_EXIST;
        return false;
    }
    
    Element *pElm = pNode->ToElement();
    if( NULL==pElm )
    {
        mStatus |= ELEMENT_NOT_EXIST;
        return false;
    }

    int res = pElm->QueryDoubleAttribute( attr.c_str(), &value );
    if( TIXML_SUCCESS!=res )
    {
        mStatus |= ATTR_NOT_EXIST;
        return false;
    }

    return true;
}

bool XML_op::addElm( const string &elm )
{
    Element Elm( elm );
    Node *pNode = pDoc->FirstChild();
    if( NULL==pNode )
    {
        mStatus |= ELEMENT_NOT_EXIST;
        return false;
    }

    pDoc->InsertAfterChild( pNode, Elm );
}
