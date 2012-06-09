/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionShape.cpp
*
*/

#include "PX2BtCollisionCylinderShape.hpp"
#include "PX2BtConverter.hpp"
using namespace TdBt;
using namespace PX2;

CylinderCollisionShape::CylinderCollisionShape(const PX2::Vector3f &halfExtents,
											   const PX2::Vector3f &axe)
{
	if (axe == Vector3f::UNIT_X)
		mShape = new btCylinderShapeX(Converter::ConvertFrom(halfExtents));
	else if (axe == Vector3f::UNIT_Y)
		mShape = new btCylinderShape (Converter::ConvertFrom(halfExtents));
	else if (axe == Vector3f::UNIT_Z)
		mShape = new btCylinderShapeZ(Converter::ConvertFrom(halfExtents));
}
//----------------------------------------------------------------------------
CylinderCollisionShape::~CylinderCollisionShape ()
{
}
//----------------------------------------------------------------------------