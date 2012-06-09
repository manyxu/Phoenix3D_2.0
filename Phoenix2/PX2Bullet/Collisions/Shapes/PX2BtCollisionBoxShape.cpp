/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionBoxShape.cpp
*
*/

#include "PX2BtCollisionBoxShape.hpp"
#include "PX2BtConverter.hpp"
using namespace TdBt;
using namespace PX2;

BoxCollisionShape::BoxCollisionShape (const PX2::Vector3f &boxBounds)
{
	mShape = new btBoxShape(Converter::ConvertFrom(boxBounds));
}
//----------------------------------------------------------------------------
BoxCollisionShape::~BoxCollisionShape()
{
}
//----------------------------------------------------------------------------