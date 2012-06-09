/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2BtCollisionConvexHullShape.hpp
*
* 版本		:	1.0 (2011/03/16)
*
* 作者		：	more
*
*/

#ifndef PX2BTCOLLISIONCONVEXHULLSHAPE_HPP
#define PX2BTCOLLISIONCONVEXHULLSHAPE_HPP

#include "PX2BtCollisionShape.hpp"

namespace TdBt
{

	class ConvexHullCollisionShape : public CollisionShape
	{
	public:
		ConvexHullCollisionShape (const float *points, int numPoints, int stride);
		ConvexHullCollisionShape ();
		ConvexHullCollisionShape (btConvexHullShape *shape);
		virtual ~ConvexHullCollisionShape ();
	};

	typedef PX2::Pointer0<ConvexHullCollisionShape> ConvexHullCollisionShapePtr;

}

#endif