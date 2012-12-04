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
	if (data.LoadFile(filename))
	{
		data.GetNodeByPath("Config.var").AttribToInt("width", mBoostWidth);
		data.GetNodeByPath("Config.var").AttribToInt("height", mBoostHeight);
		mMapName = data.GetNodeByPath("Play.var").AttributeToString("mapName");

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------