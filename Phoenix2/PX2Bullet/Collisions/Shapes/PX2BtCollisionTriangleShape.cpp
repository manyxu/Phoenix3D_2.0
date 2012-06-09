/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionTriangleShape.cpp
*
*/

#include "PX2BtCollisionTriangleShape.hpp"
#include "PX2BtConverter.hpp"
using namespace TdBt;
using namespace PX2;

TriangleCollisionShape::TriangleCollisionShape (const PX2::Vector3f &p0,
												const PX2::Vector3f &p1,
												const PX2::Vector3f &p2)
{
	mShape = new btTriangleShape(Converter::ConvertFrom(p0),
		Converter::ConvertFrom(p1), Converter::ConvertFrom(p2));
}
//----------------------------------------------------------------------------
TriangleCollisionShape::TriangleCollisionShape(float p0X, float p0Y, float p0Z,
											   float p1X, float p1Y, float p1Z,
											   float p2X, float p2Y, float p2Z)
{
	mShape = new btTriangleShape(btVector3(p0X, p0Y, p0Z), 
		btVector3(p1X, p1Y, p1Z), btVector3(p2X, p2Y, p2Z));
}
//----------------------------------------------------------------------------
TriangleCollisionShape::~TriangleCollisionShape ()
{
}
//----------------------------------------------------------------------------