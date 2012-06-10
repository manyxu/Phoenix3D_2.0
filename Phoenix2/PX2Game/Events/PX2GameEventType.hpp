/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2GameEventType.hpp
*
* 版本		:	1.0 (2011/04/03)
*
* 作者		：	more
*
*/

#ifndef PX2GAMEEVENTTYPE_HPP
#define PX2GAMEEVENTTYPE_HPP

#include "PX2GamePrerequisites.hpp"

namespace PX2
{

	/// Game事件空间
	PX2_DECLARE_EVENT_BEGIN(GameEventSpace)
	PX2_EVENT(MAINPLAYER_TRANS)
	PX2_DECLARE_EVENT_END(GameEventSpace)

}

#endif