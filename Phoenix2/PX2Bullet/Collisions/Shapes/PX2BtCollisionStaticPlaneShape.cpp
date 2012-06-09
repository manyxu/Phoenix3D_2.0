/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionStaticPlaneShape.cpp
*
*/

#include "PX2BtCollisionStaticPlaneShape.hpp"
using namespace TdBt;
using namespace PX2;

StaticPlaneCollisionShape::StaticPlaneCollisionShape(const PX2::Vector3f normal, 
													 float distance)
{
	mShape = new btStaticPlaneShape(btVector3(normal.X(), normal.Y(), normal.Z()),
		btScalar(distance));
}
//----------------------------------------------------------------------------
StaticPlaneCollisionShape::~StaticPlaneCollisionShape()
{
}
//----------------------------------------------------------------------------
bool StaticPlaneCollisionShape::DrawWireFrame (DebugLines *wire,
											   const APoint &pos,
											   const HQuaternion &quat) const
{
	PX2_UNUSED(wire);
	PX2_UNUSED(pos);
	PX2_UNUSED(quat);

	return false;
}
//----------------------------------------------------------------------------