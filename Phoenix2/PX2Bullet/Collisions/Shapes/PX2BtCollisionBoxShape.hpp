/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtCollisionBoxShape.hpp
*
* 版本		:	1.0 (2011/03/07)
*
* 作者		：	more
*
*/

#ifndef PX2BTCOLLISIONBOXSHAPE_HPP
#define PX2BTCOLLISIONBOXSHAPE_HPP

#include "PX2BtCollisionShape.hpp"

namespace TdBt
{

	// 盒装碰撞体
	class BoxCollisionShape : public CollisionShape
	{
	public:
		BoxCollisionShape (const PX2::Vector3f &boxBounds);
		virtual ~BoxCollisionShape();
	};

	typedef PX2::Pointer0<BoxCollisionShape> BoxCollisionShapePtr;

}

#endif