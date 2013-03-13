/*
*
* ÎÄ¼þÃû³Æ	£º	PX2LuaManager.cpp
*
*/

#include "PX2LuaManager.hpp"
#include "PX2ResourceManager.hpp"
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "tolua++.h"
using namespace PX2;

//----------------------------------------------------------------------------
// LuaStackBackup
//----------------------------------------------------------------------------
LuaStackBackup::LuaStackBackup (lua_State *luaState)
	:
mState(luaState)
{
	mTop = lua_gettop(mState);
}
//----------------------------------------------------------------------------
LuaStackBackup::~LuaStackBackup ()
{
	lua_settop(mState, mTop);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
static int GetGlobal (lua_State *ls)
{
	if (lua_isstring(ls,1) == false)
	{
		lua_pushnil(ls);
	}
	else 
	{
		lua_getglobal(ls, lua_tostring(ls,1));
	}

	return 1;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// LuaManager
//----------------------------------------------------------------------------
LuaManager::LuaManager ()
	:
mState(0)
{
	mType = ST_LUA;

	mState = lua_open();
	luaL_openlibs(mState);
	lua_register(mState, "GetGlobal", GetGlobal);
}
//----------------------------------------------------------------------------
LuaManager::~LuaManager ()
{
	if(mState) 
	{
		lua_close(mState);
	}
}
//----------------------------------------------------------------------------
void LuaManager::SetLuaState (lua_State *state)
{
	mState = state;
	lua_register(mState, "GetGlobal", GetGlobal);
}
//----------------------------------------------------------------------------
bool LuaManager::CallString (const char *str)
{
	LuaStackBackup stackbackup(mState);

	int status = luaL_dostring(mState, str);

	if (status != 0)
	{
		const char *err = lua_tostring(mState, -1);

#if defined(_WIN32) || defined(WIN32)
		::MessageBox(0, err, "CallString::luaL_dostring error.\n", MB_OK);
#endif
		PX2_LOG_ERROR("CallString::luaL_dostring error:%s.\n", err);

		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
bool LuaManager::CallFile (const char *filename)
{
	bool ret = false;

	int bufferSize = 0;
	char *buffer = 0;
	if (ResourceManager::GetSingleton().GetBuffer(filename, bufferSize,
		buffer))
	{
		ret = CallBuffer(buffer, (unsigned long)bufferSize);

		delete1(buffer);
		bufferSize = 0;
	}

	return ret;

//	if (luaL_loadfile(mState, filename) != 0)
//	{
//		const char *err = lua_tostring(mState, -1);
//
//#if defined(_WIN32) || defined(WIN32)
//		::MessageBox(0, err, "CallFile::luaL_loadfile error.\n", MB_OK);
//#endif
//		PX2_LOG_ERROR("CallFile::luaL_loadfile error: %s.\n", err);
//
//		return false;
//	}
//
//	if (lua_pcall(mState, 0, 0, 0) != 0)
//	{
//		const char *err = lua_tostring(mState, -1);
//
//#if defined(_WIN32) || defined(WIN32)
//		::MessageBox(0, err, "CallFile::lua_pcall error.\n", MB_OK);
//#endif
//		PX2_LOG_ERROR("CallFile::lua_pcall error:%s.\n", err);
//
//		return false;
//	}
//
//	return true;
}
//----------------------------------------------------------------------------
bool LuaManager::CallBuffer (const char *buffer, unsigned long size)
{
	if (luaL_loadbuffer(
		mState, buffer, (size_t)size, lua_tostring(mState, -1)) != 0)
	{
		const char *err = lua_tostring(mState, -1);

#if defined(_WIN32) || defined(WIN32)
		::MessageBox(0, err, "CallBuffer::luaL_loadbuffer error.\n", MB_OK);
#endif
		PX2_LOG_ERROR("CallBuffer::luaL_loadbuffer error:%s.\n", err);

		return false;
	}

	if (lua_pcall(mState, 0, 0, 0) != 0)
	{
		const char *err = lua_tostring(mState, -1);

#if defined(_WIN32) || defined(WIN32)
		::MessageBox(0, err, "CallBuffer::lua_pcall error.\n", MB_OK);
#endif
		PX2_LOG_ERROR("CallBuffer::lua_pcall error:%s.\n", err);

		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
void LuaManager::SetUserTypePointer (const char *luaName, 
	const char *className, void *ptr)
{
	LuaStackBackup stackbackup(mState);

	tolua_pushusertype(mState, ptr, className);

	lua_setglobal(mState, luaName);
}
//----------------------------------------------------------------------------