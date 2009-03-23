#include "xml_op.h"
#include "tinyxml.h"
#include <fstream>
#include <iostream>

using namespace std;

//#define DEBUG_XML

#ifdef DEBUG_XML
#define LOGXML(msg) do{ cout<<msg<<endl; }while(0)
#else
#define LOGXML(msg)
#endif

typedef TiXmlNode Node;
typedef TiXmlElement Element;
typedef TiXmlDocument Document;
typedef TiXmlText Text;

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

/*
XML_op::XML_op( const char* input )
    : pDoc( new TiXmlDocument() )
{
    mStatus = PARSE_FAILED;
    if( NULL!=pDoc->Parse(input) )
    {
        mStatus = PARSE_DONE;
    }    
}
*/

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
        mStatus = ELEMENT_NOT_EXIST;
		LOGXML("getAttrValue::get node failed");
        return false;
    }
    
    Element *pElm = pNode->ToElement();
    if( NULL==pElm )
    {
        mStatus = ELEMENT_NOT_EXIST;
		LOGXML("getAttrValue::to element failed");
        return false;
    }

    int res = pElm->QueryIntAttribute( attr.c_str(), &value );
    if( TIXML_SUCCESS!=res )
    {
        mStatus = ATTR_NOT_EXIST;
		LOGXML("getAttrValue::get int attr failed");
        return false;
    }
	mStatus = ATTR_OK;

    return true;
}

bool XML_op::getAttrValue( const string &elm, const string &attr, double &value )
{
    Node *pNode = pDoc->FirstChild( elm );
    if( NULL==pNode )
    {
        mStatus = ELEMENT_NOT_EXIST;
        return false;
    }
    
    Element *pElm = pNode->ToElement();
    if( NULL==pElm )
    {
        mStatus = ELEMENT_NOT_EXIST;
        return false;
    }

    int res = pElm->QueryDoubleAttribute( attr.c_str(), &value );
    if( TIXML_SUCCESS!=res )
    {
        mStatus = ATTR_NOT_EXIST;
        return false;
    }
	mStatus = ATTR_OK;

    return true;
}

bool XML_op::addElm( const string &elm )
{
	if( NULL!=pDoc->FirstChild(elm) )
	{
		mStatus = ELEMENT_OK;
		return true;
	}

    Element Elm( elm );
    Node *pNode = pDoc->FirstChild();
    if( NULL==pNode )
    {
        mStatus = ELEMENT_NOT_EXIST;
        return false;
    }

    pDoc->InsertAfterChild( pNode, Elm );
	mStatus = ELEMENT_OK;

	return true;
}

bool XML_op::addAttr( const string &elm, const string &attr, const int &value )
{
	Node *pNode = pDoc->FirstChild( elm );
	if( NULL!=pNode )
	{
		//the element is exist
		Element *pElm = pNode->ToElement();
		if( NULL!=pElm )
		{
			pElm->SetAttribute( attr.c_str(), value );
			mStatus = ATTR_ADD_OK;
			return true;
		}
		else
		{
			mStatus = ATTR_ADD_FAILED;
		}
	}
	else
	{
		bool ret = addElm( elm );
		if( true==ret )
		{
			return addAttr( elm, attr, value );
		}
		else
		{
			mStatus = ATTR_ADD_FAILED;
		}
	}

	return false;
}

bool XML_op::addAttr( const string &elm, const string &attr, const double &value )
{
	Node *pNode = pDoc->FirstChild( elm );
	if( NULL!=pNode )
	{
		//the element is exist
		Element *pElm = pNode->ToElement();
		if( NULL!=pElm )
		{
			pElm->SetDoubleAttribute( attr.c_str(), value );
			mStatus = ATTR_ADD_OK;
			return true;
		}
		else
		{
			mStatus = ATTR_ADD_FAILED;
		}
	}
	else
	{
		bool ret = addElm( elm );
		if( true==ret )
		{
			return addAttr( elm, attr, value );
		}
		else
		{
			mStatus = ATTR_ADD_FAILED;
		}
	}

	return false;
}

bool XML_op::addText( const string &elm, const string &text )
{
	if( true==addElm(elm) )
	{
		Node *pNode = pDoc->FirstChild( elm );
		if( NULL!=pNode )
		{
			Element *pElm = pNode->ToElement();
			Text textInfo( text );
			pElm->InsertEndChild( textInfo );
			mStatus = ADD_TEXT_OK;

			return true;
		}
	}

	mStatus = ADD_TEXT_FAILED;

	return false;

}

bool XML_op::dumpXML( char* outPut, int Size )
{
	FILE *pFile = fopen( "./tmpfile", "w" );
	if( NULL==pFile )
	{
		return false;
	}

	pDoc->Print( pFile, 0 );
	fclose( pFile );
	fstream fopen( "./tmpfile", fstream::in );
	fopen.seekg( 0, ios::end );
	int length = fopen.tellg();
	fopen.seekg( 0, ios::beg );

	if( length>Size )
	{
		return false;
	}

	fopen.read( outPut, length );

	return true;
}
