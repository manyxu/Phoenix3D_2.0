/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2State.hpp
*
* 版本		:	1.0 (2011/04/01)
*
* 作者		：	more
*
*/

#ifndef PX2STATE_HPP
#define PX2STATE_HPP

#include "PX2GamePrerequisites.hpp"

namespace PX2
{

	template <typename T>
	class State
	{
	public:
		virtual ~State () {}

		virtual void Enter (T *) = 0;
		virtual void Execute (T *) = 0;
		virtual void Exit (T *) = 0;

		virtual void OnEvent (T *owner, PX2::Event *event)
		{
			PX2_UNUSED(owner);
			PX2_UNUSED(event); 
		}
	};

}

#endif