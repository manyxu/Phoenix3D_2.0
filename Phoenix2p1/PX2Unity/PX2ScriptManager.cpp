/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ScriptManager.cpp
*
*/

#include "PX2ScriptManager.hpp"
#include "PX2LuaManager.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
ScriptManager::ScriptManager ()
	:
mType(ST_MAX_TYPE)
{
}
//----------------------------------------------------------------------------
ScriptManager::~ScriptManager ()
{
}
//----------------------------------------------------------------------------
ScriptManager *ScriptManager::Create (ScriptType type)
{
	ScriptManager *sm = 0;

	if (type == ST_LUA)
	{
		sm = new0 LuaManager();
	}

	return sm;
}
//----------------------------------------------------------------------------