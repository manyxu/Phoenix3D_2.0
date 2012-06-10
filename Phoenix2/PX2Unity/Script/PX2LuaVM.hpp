/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2LuaVM.hpp
*
* 版本		:	1.0 (2011/07/10)
*
* 作者		：	more
*
*/

#ifndef PX2LUAVM_HPP
#define PX2LUAVM_HPP

#include "PX2UnityPrerequisites.hpp"

struct lua_State;

namespace PX2
{

	class PX2_CORE_ENTRY ScriptVM
	{
	public:
		ScriptVM ();
		~ScriptVM ();

		bool CallString (const char *str);
		bool CallFile (const char *filename);
		
		bool CallFunction (const char *funName, const char *format, ...);
		void SetUserTypePointer (const char *name, const char *className,
			void *ptr);

		lua_State *GetLuaState ();

	protected:
		lua_State *mState;
	};

#include "PX2LuaVM.inl"

}

#endif