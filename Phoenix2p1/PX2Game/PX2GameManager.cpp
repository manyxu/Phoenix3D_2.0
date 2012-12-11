/*
*
* ÎÄ¼þÃû³Æ	£º	PX2GameManager.cpp
*
*/

#include "PX2GameManager.hpp"
#include "PX2XMLData.hpp"
#include "PX2ResourceManager.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
GameManager::GameManager ()
	:
mBoostWidth(0),
mBoostHeight(0)
{
}
//----------------------------------------------------------------------------
GameManager::~GameManager ()
{
}
//----------------------------------------------------------------------------
bool GameManager::LoadBoost (const char *filename)
{
	XMLData data;

	int bufferSize = 0;
	char *buffer = 0;
	ResourceManager::GetSingleton().GetBuffer(filename, bufferSize, buffer);

	if (!buffer || bufferSize==0)
		return false;

	if (data.LoadBuffer(buffer, bufferSize))
	{
		delete1<char>(buffer);

		data.GetNodeByPath("Config.var").AttribToInt("width", mBoostWidth);
		data.GetNodeByPath("Config.var").AttribToInt("height", mBoostHeight);
		mMapName = data.GetNodeByPath("Play.var").AttributeToString("mapName");

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------