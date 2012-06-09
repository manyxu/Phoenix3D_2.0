/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtCollisionMultiSphereShape.hpp
*
* 版本		:	1.0 (2011/03/07)
*
* 作者		：	more
*
*/

#ifndef PX2BTCOLLISIONMULTISPHERESHAPE_HPP
#define PX2BTCOLLISIONMULTISPHERESHAPE_HPP

#include "PX2BtCollisionSphereShape.hpp"

namespace TdBt
{

	class MultiSphereCollisionShape : public CollisionShape
	{
	public:
		MultiSphereCollisionShape (const PX2::Vector3f &inertiaHalfExtents,
			const PX2::Vector3f *positions, const float *radius, 
			int numSpheres);
		virtual ~MultiSphereCollisionShape ();
	};

	typedef PX2::Pointer0<MultiSphereCollisionShape>
		MultiSphereCollisionShapePtr;

}

#endif