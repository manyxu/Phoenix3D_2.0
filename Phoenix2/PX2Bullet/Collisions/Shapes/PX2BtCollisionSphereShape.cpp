/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionSphereShape.cpp
*
*/

#include "PX2BtCollisionSphereShape.hpp"
using namespace TdBt;
using namespace PX2;

SphereCollisionShape::SphereCollisionShape(const float radius)
:
CollisionShape()
{
	mShape = new btSphereShape(radius);
}
//----------------------------------------------------------------------------
SphereCollisionShape::~SphereCollisionShape()
{
}
//----------------------------------------------------------------------------