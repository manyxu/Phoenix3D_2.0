/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2TRange.hpp
*
* 版本		:	1.0 (2011/12/17)
*
* 作者		：	more
*
*/

#ifndef PX2TRANGE_HPP
#define PX2TRANGE_HPP

#include "PX2EffectPrerequisites.hpp"

namespace PX2
{

	/// 范围类
	/**
	* 输入两个值，通过GetRandomInRange获得两值范围内的一个随机值。
	*/
	template <class T>
	class TRange
	{
	public:
		TRange ();
		TRange (T value0, T value1);
		~TRange ();

		T GetRandomInRange();
		T GetRange ();

		T Value0;
		T Value1;
	};

	int RandomNumber (int value0, int value1);
	float RandomNumber (float value0, float value1);
	Float2 RandomNumber (Float2 value0, Float2 value1);
	Float3 RandomNumber (Float3 value0, Float3 value1);
	Float4 RandomNumber (Float4 value0, Float4 value1);

#include "PX2TRange.inl"

}
#endif