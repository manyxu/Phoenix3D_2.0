/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	SystemManager.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2SYSTEMMANAGER_HPP
#define PX2SYSTEMMANAGER_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class SystemManager
	{
	public:
		static bool Initialize ();
		static bool Terminate ();
	};

}

#endif