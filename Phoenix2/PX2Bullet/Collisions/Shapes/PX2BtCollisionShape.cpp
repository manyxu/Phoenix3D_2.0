/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionShape.cpp
*
*/

#include "PX2BtCollisionShape.hpp"
#include "PX2BtConverter.hpp"
#include "PX2BtCollisionDebugLines.hpp"
using namespace TdBt;
using namespace PX2;

CollisionShape::CollisionShape()
:	
mShape(0)
{
}
//----------------------------------------------------------------------------
CollisionShape::~CollisionShape()
{
	if (mShape)
		delete mShape;
}
//----------------------------------------------------------------------------