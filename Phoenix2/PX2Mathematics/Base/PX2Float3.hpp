/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Float3.hpp
*
* 版本		:	1.0 (2011/01/30)
*
* 作者		：	more
*
*/

#ifndef PX2FLOAT3_HPP
#define PX2FLOAT3_HPP

#include "PX2MathematicsPrerequisites.hpp"
#include "PX2Tuple.hpp"

namespace PX2
{

	class PX2_MATHEMATICS_ENTRY Float3 : public Tuple<3,float>
	{
	public:
		Float3 ();   //< 未初始化
		~Float3 ();  // hides ~Tuple<3,float>
		Float3 (float f0, float f1, float f2);
		Float3 (const Float3& tuple);

		// 赋值
		Float3& operator= (const Float3& tuple);
	};

}

#endif