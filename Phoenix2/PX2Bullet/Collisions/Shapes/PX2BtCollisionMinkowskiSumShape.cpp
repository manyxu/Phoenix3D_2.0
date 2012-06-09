/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionMinkowskiSumShape.cpp
*
*/

#include "PX2BtCollisionMinkowskiSumShape.hpp"
using namespace TdBt;
using namespace PX2;

MinkowskiSumCollisionShape::MinkowskiSumCollisionShape(CollisionShape* shapeA,
													   CollisionShape* shapeB)
{
	mShape = new btMinkowskiSumShape(
		(btConvexShape*)shapeA->GetBulletShape(),
		(btConvexShape*)shapeB->GetBulletShape());
}
//----------------------------------------------------------------------------
MinkowskiSumCollisionShape::~MinkowskiSumCollisionShape()
{
}
//----------------------------------------------------------------------------