/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionConvexHullShape.cpp
*
*/

#include "PX2BtCollisionConvexHullShape.hpp"
using namespace TdBt;
using namespace PX2;

ConvexHullCollisionShape::ConvexHullCollisionShape (const float *points,
													int numPoints, int stride)
{
	mShape = new btConvexHullShape((btScalar*)points, numPoints, stride);
}
//----------------------------------------------------------------------------
ConvexHullCollisionShape::ConvexHullCollisionShape ()
{
	mShape = new btConvexHullShape();
}
//----------------------------------------------------------------------------
ConvexHullCollisionShape::ConvexHullCollisionShape (btConvexHullShape *shape)
{
	mShape = shape;
}
//----------------------------------------------------------------------------
ConvexHullCollisionShape::~ConvexHullCollisionShape ()
{
}
//----------------------------------------------------------------------------