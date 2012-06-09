/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionMultiSphereShape.cpp
*
*/

#include "PX2BtCollisionMultiSphereShape.hpp"
#include "PX2BtConverter.hpp"
using namespace TdBt;
using namespace PX2;

MultiSphereCollisionShape::MultiSphereCollisionShape (
	const PX2::Vector3f &inertiaHalfExtents,	const PX2::Vector3f *positions,
	const float *radius, int numSpheres)
{
	PX2_UNUSED(inertiaHalfExtents);

	btVector3 * btPositions = new btVector3[numSpheres];
	{
		unsigned int currNum = numSpheres;
		while (currNum-- > 0)
		{
			btPositions[currNum] = Converter::ConvertFrom(positions[currNum]);
		}
	}

	mShape = new btMultiSphereShape(
		(btVector3 *) btPositions,
		(const btScalar *)radius,
		numSpheres);

	delete [] btPositions;
}
//----------------------------------------------------------------------------
MultiSphereCollisionShape::~MultiSphereCollisionShape ()
{
}
//----------------------------------------------------------------------------