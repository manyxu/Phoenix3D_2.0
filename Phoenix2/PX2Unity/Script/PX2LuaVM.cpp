/*
*
* 文件名称	：	PX2LuaVM.cpp
*
*/

#include "PX2LuaVM.hpp"
using namespace PX2;

extern "C"
{
#include "lua/src/lua.h"
#include "lua/src/lauxlib.h"
#include "lua/src/lualib.h"
}

#include "tolua++.h"

class LuaStackBackup
{
public:
	LuaStackBackup (lua_State *ls2)
		:
	ls(ls2)
	{
		top = lua_gettop(ls);
	}

	~LuaStackBackup ()
	{
		lua_settop(ls, top);
	}

private:
	lua_State *ls;
	int	top;
};

static int GetGlobal (lua_State *ls)
{
	if (lua_isstring(ls,1) == false)
	{
		lua_pushnil(ls);
	}
	else 
		lua_getglobal(ls, lua_tostring(ls,1));

	return 1;
}
//----------------------------------------------------------------------------
ScriptVM::ScriptVM ()
{
	mState = lua_open();
	luaL_openlibs(mState);
	lua_register(mState, "GetGlobal", GetGlobal);
}
//----------------------------------------------------------------------------
ScriptVM::~ScriptVM ()
{
	if (mState) 
		lua_close(mState);
}
//----------------------------------------------------------------------------
bool ScriptVM::CallString (const char *str)
{
	LuaStackBackup stackbackup(mState);

	int status = luaL_dostring(mState, str);

	if (status != 0)
	{
		const char *err = lua_tostring(mState, -1);
		
		assertion (false, "Script CallString error:%s", err);
		PX2_UNUSED(err);

		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
bool ScriptVM::CallFile (const char *filename)
{	
	if (luaL_loadfile(mState, filename) != 0)
	{
		const char *err = lua_tostring(mState, -1);

		assertion(false, "script load failed: %s, error: %s", filename, err);
		PX2_UNUSED(err);

		return false;
	}

	if(lua_pcall(mState, 0, 0, 0) != 0)
	{
		const char *err = lua_tostring(mState, -1);

		assertion(false, "script call failed: %s, error: %s", filename, err);
		PX2_UNUSED(err);

		return false;
	}

	return true;
}
//----------------------------------------------------------------------------
bool ScriptVM::CallFunction (const char *funName, const char *format, ...)
{
	LuaStackBackup stackbackup(mState);

	lua_getglobal(mState, funName);
	if(!lua_isfunction(mState, -1))
	{
		assertion(false, "%s is not a function.", funName);
		return false;
	}

	va_list vl;
	va_start(vl, format);

	const char *sig = format;
	if(format == NULL) 
		sig = "";

	int narg = 0;

	while (*sig)
	{
		switch (*sig)
		{
		case 'd': // double
			lua_pushnumber(mState, va_arg(vl, double));
			break;
		case 'f': // float
			lua_pushnumber(mState, va_arg(vl, float));
			break;
		case 'i': // int
			lua_pushnumber(mState, va_arg(vl, int));
			break;
		case 's': // string
			lua_pushstring(mState, va_arg(vl, char *));
			break;
		case 'b': // bool
			lua_pushboolean(mState, va_arg(vl, bool));
			break;
		case 'u': // user data
			{
				char classname[256];
				sig++;
				assertion(sig[0] == '[', "");
				const char *pend = strchr(sig, ']');
				assertion(pend != 0, "");
				size_t len = pend-sig-1;
				memcpy(classname, sig+1, len);
				classname[len] = 0;

				tolua_pushusertype(mState, va_arg(vl, void *), classname);
				sig = pend;
			}
			break;
		case '>':
			sig++;
			goto endwhile;
		default:
			assertion(false, "");
			return false;
		}
		sig++;
		narg++;
		luaL_checkstack(mState, 1, "too many arguments");
	}

endwhile:
	int nres = (int)strlen(sig); // 期望的返回值数量

	// 调用
	if (lua_pcall(mState, narg, nres, 0) != 0)
	{
		assertion(false, "lua_pcall error: %s", lua_tostring(mState, -1));
		return false;
	}

	// 获得返回值
	nres = -nres; /* stack index of	first result */
	while(*sig)
	{
		switch (*sig++)
		{
		case 'd': // double
			assertion(lua_isnumber(mState, nres)>0, "param must be a number.");
			*va_arg(vl,	double *) =	lua_tonumber(mState, nres);
			break;
		case 'f': // float
			assertion(lua_isnumber(mState, nres)>0, "param must be a number.");
			*va_arg(vl, float*) = (float)lua_tonumber(mState, nres);
			break;
		case 'i': /* int result	*/
			assertion(lua_isnumber(mState, nres)>0, "param must be a number.");
			*va_arg(vl,	int	*) = (int)lua_tonumber(mState, nres);
			break;
		case 's': // string
			assertion(lua_isstring(mState, nres)>0, "param must be a string.");
			strcpy(va_arg(vl,char *), lua_tostring(mState, nres));
			break;
		case 'b': /* boolean argument */
			assertion(lua_isboolean(mState, nres), "param must be a number.");
			*va_arg(vl,	bool *) = (0!=lua_toboolean(mState, nres));
			break;
		case 'u': /* light user data */
			assertion(lua_isuserdata(mState, nres)>0, "");
			*va_arg(vl,	void **) = tolua_tousertype(mState, nres, NULL);
			break;
		default:
			assertion(false, "");
			break;
		}
		nres++;
	}
	return true;
}
//----------------------------------------------------------------------------
void ScriptVM::SetUserTypePointer (const char *name,
								   const char *className, void *ptr)
{
	LuaStackBackup stackbackup(mState);

	tolua_pushusertype(mState, ptr, className);

	lua_setglobal(mState, name);
}
//----------------------------------------------------------------------------