/*
*
* ÎÄ¼þÃû³Æ	£º	PX2XMLNode.cpp
*
*/

#include "PX2XMLNode.hpp"
#include "PX2Assert.hpp"
#include "tinyxml.h"
using namespace std;
using namespace PX2;

XMLNode::XMLNode (std::string name)
:
mElement(0),
mName(name)
{
}
//----------------------------------------------------------------------------
XMLNode::XMLNode(TiXmlElement *element)
: 
mElement(element)
{
	if (mElement)
		mName = mElement->Value();
}
//----------------------------------------------------------------------------
XMLNode::~XMLNode ()
{
}
//----------------------------------------------------------------------------
bool XMLNode::IsNull ()
{
	return (mElement == 0);
}
//----------------------------------------------------------------------------
void XMLNode::Create ()
{
	mElement = new TiXmlElement(mName.c_str());
}
//----------------------------------------------------------------------------
void XMLNode::LinkEndChild (XMLNode node)
{
	if (node.mElement && mElement)
	{
		mElement->LinkEndChild(node.mElement);
	}
}
//----------------------------------------------------------------------------
const char *XMLNode::GetName ()
{
	return mElement->Value();
}
//----------------------------------------------------------------------------
char *XMLNode::GetFullName (char *buffer, size_t maxBuffer)
{
	list<string> strs;
	string str;

	TiXmlNode *pCurElement = mElement;
	while (pCurElement)
	{
		str = pCurElement->Value();
		strs.push_front(str);

		pCurElement = pCurElement->Parent();
	}

	str = "";
	list<string>::iterator iter = strs.begin();
	for (; iter!=strs.end(); iter++)
	{
		if (!str.empty())
			str += ".";

		str += *iter;
	}

	strncpy(buffer, str.c_str(), maxBuffer);
	buffer[maxBuffer-1] = 0;

	return buffer;
}
//----------------------------------------------------------------------------
const char *XMLNode::GetText ()
{
	const TiXmlNode *child = mElement->FirstChild();

	while (child)
	{
		const TiXmlText *childText = child->ToText();

		if (childText)
			return childText->Value();

		child = child->NextSibling();
	}

	return NULL;
}
//----------------------------------------------------------------------------
bool XMLNode::HasChild (const char *name)
{
	return (mElement->FirstChildElement(name) != 0);
}
//----------------------------------------------------------------------------
XMLNode XMLNode::GetChild (const char *name)
{
	return XMLNode(mElement->FirstChildElement(name));
}
//----------------------------------------------------------------------------
XMLNode XMLNode::IterateChild ()
{
	return XMLNode(mElement->FirstChildElement());
}
//----------------------------------------------------------------------------
XMLNode XMLNode::IterateChild (XMLNode previous)
{
	if (previous.IsNull())
	{
		return XMLNode();
	}
	else
	{
		return XMLNode(previous.mElement->NextSiblingElement());
	}
}
//----------------------------------------------------------------------------
bool XMLNode::HasAttribute (const char *name)
{
	return (mElement->Attribute(name) != 0);
}
//----------------------------------------------------------------------------
int XMLNode::AttributeToInt (const char *name)
{
	int value = 0;

	if (mElement->QueryIntAttribute(name, &value) != TIXML_SUCCESS)
	{
		assertion(false, "int attribute %s doesn't exist.", name);
	}

	return value;
}
//----------------------------------------------------------------------------
float XMLNode::AttributeToFloat (const char *name)
{
	float value = 0.0f;

	if (mElement->QueryFloatAttribute(name, &value) != TIXML_SUCCESS)
	{
		assertion(false, "float attribute %s doesn't exist.", name);
	}

	return value;
}
//----------------------------------------------------------------------------
bool XMLNode::AttributeToBool (const char *name)
{
	const char *pstr = AttributeToString(name);

	if (0 == pstr)
	{
		return false;
	}
	else
	{
		return (strncmp(pstr, "true", 4) == 0)
			||(strncmp(pstr, "TRUE", 4) == 0);
	}
}
//----------------------------------------------------------------------------
const char *XMLNode::AttributeToString (const char *name)
{
	return mElement->Attribute(name);
}
//----------------------------------------------------------------------------
bool XMLNode::AttribToInt (const char *name, int &value)
{
	if(mElement->QueryIntAttribute(name, &value) != TIXML_SUCCESS)
	{
		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
bool XMLNode::AttribToFloat (const char *name, float &value)
{
	if(mElement->QueryFloatAttribute(name, &value) != TIXML_SUCCESS)
	{
		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
void XMLNode::SetAttributeInt (const char *name, int value)
{
	mElement->SetAttribute(name, value);
}
//----------------------------------------------------------------------------
void XMLNode::SetAttributeFloat (const char *name, float value)
{
	char buffer[256];
	sprintf(buffer, "%f", value);
	mElement->SetAttribute(name, buffer);
}
//----------------------------------------------------------------------------
void XMLNode::SetAttributeBool (const char *name, bool value)
{
	mElement->SetAttribute(name, value?"true":"false");
}
//----------------------------------------------------------------------------
void XMLNode::SetAttributeString (const char *name, const char *string)
{
	mElement->SetAttribute(name, string);
}
//----------------------------------------------------------------------------