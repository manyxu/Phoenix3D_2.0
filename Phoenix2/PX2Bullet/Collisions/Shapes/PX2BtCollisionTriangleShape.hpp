/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtCollisionTriangleShape.hpp
*
* 版本		:	1.0 (2011/03/07)
*
* 作者		：	more
*
*/

#ifndef PX2BTCOLLISIONTRIANGLESHAPE_HPP
#define PX2BTCOLLISIONTRIANGLESHAPE_HPP

#include "PX2BtCollisionShape.hpp"

namespace TdBt
{

	class TriangleCollisionShape : public CollisionShape
	{
	public:
		TriangleCollisionShape (const PX2::Vector3f &p0, const PX2::Vector3f &p1,
			const PX2::Vector3f &p2);
		TriangleCollisionShape (
			float p0X, float p0Y, float p0Z,
			float p1X, float p1Y, float p1Z,
			float p2X, float p2Y, float p2Z);
		virtual ~TriangleCollisionShape ();
	};

	typedef PX2::Pointer0<TriangleCollisionShape> TriangleCollisionShapePtr;

}

#endif