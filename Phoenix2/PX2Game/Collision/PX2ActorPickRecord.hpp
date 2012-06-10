/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ActorPickRecord.hpp
*
* 版本		:	1.0 (2011/06/05)
*
* 作者		：	more
*
*/

#ifndef PX2ACTORPICKRECORD_HPP
#define PX2ACTORPICKRECORD_HPP

#include "PX2GamePrerequisites.hpp"
#include "PX2Actor.hpp"

namespace PX2
{

	class ActorPickRecord
	{
	public:
		ActorPickRecord ()
		{
			T = 0.0f;
		}

		~ActorPickRecord ()
		{
		}

		ActorPtr Intersected;

		// 射线P + t*D中的线性元素量。T是其中t的表示。
		float T;
	};

}

#endif