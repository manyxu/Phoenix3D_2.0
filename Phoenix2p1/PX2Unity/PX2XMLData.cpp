/*
*
* ÎÄ¼þÃû³Æ	£º	PX2XMLData.cpp
*
*/

#include "PX2XMLData.hpp"
#include "tinyxml.h"
using namespace PX2;
using namespace std;

XMLData::XMLData() 
:
mDocument(0)
{
}
//----------------------------------------------------------------------------
XMLData::~XMLData()
{
	if (mDocument)
	{
		delete0(mDocument);
		mDocument = 0;
	}
}
//----------------------------------------------------------------------------
bool XMLData::LoadFile (const string &fileName)
{
	mDocument = new0 TiXmlDocument;

	if (!mDocument)
		return false;

	return mDocument->LoadFile(fileName.c_str());
}
//----------------------------------------------------------------------------
bool XMLData::LoadBuffer (const char *buffer, int size)
{
	mDocument = new0 TiXmlDocument;

	if (!mDocument)
		return false;

	return mDocument->LoadBuffer(buffer, size);
}
//----------------------------------------------------------------------------
bool XMLData::SaveFile (const string &fileName)
{
	if (!mDocument)
		return false;

	return mDocument->SaveFile(fileName.c_str());
}
//----------------------------------------------------------------------------
void XMLData::Create ()
{
	mDocument = new0 TiXmlDocument;
}
//----------------------------------------------------------------------------
XMLNode XMLData::GetRootNode ()
{
	return XMLNode(mDocument->RootElement());
}
//----------------------------------------------------------------------------
XMLNode XMLData::GetNodeByPath (const char *path)
{
	char name[256];
	const char *pcur = path;

	XMLNode node = GetRootNode();
	while (pcur!=0 && pcur!=0)
	{
		const char *pdot = strchr(pcur, '.');
		if (pdot)
		{
			size_t len = pdot - pcur;
			memcpy(name, pcur, len);
			name[len] = 0;
			pcur = pdot + 1;
		}
		else
		{
			strcpy(name, pcur);
			pcur = 0;
		}

		node = node.GetChild(name);
		if (node.IsNull())
			return node;
	}

	return node;
}
//----------------------------------------------------------------------------
void XMLData::LinkEndChild (XMLNode node)
{
	if (node.mElement)
	{
		mDocument->LinkEndChild(node.mElement);
	}
}
//----------------------------------------------------------------------------