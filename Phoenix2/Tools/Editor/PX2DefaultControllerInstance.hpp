/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2DefaultControllerInstance.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2DEFAULTCONTROLLERINSTANCE_HPP
#define PX2DEFAULTCONTROLLERINSTANCE_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2ControllerInstance.hpp"

namespace PX2Editor
{

	class DefaultControllerInstance : public ControllerInstance
	{
	public:
		DefaultControllerInstance ();
		~DefaultControllerInstance ();

		virtual void Activate();
		virtual void DeActivate();

		virtual void NotifySelection (const Selection &selection);
	};

}

#endif