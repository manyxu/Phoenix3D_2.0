/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionRay.cpp
*
*/

#include "PX2BtCollisionRay.hpp"
#include "PX2BtCollisionWorld.hpp"
#include "PX2BtConverter.hpp"
#include "PX2BtCollisionable.hpp"
using namespace TdBt;
using namespace PX2;

//----------------------------------------------------------------------------
C_RayResultCallback::C_RayResultCallback(const PX2::Ray3f &ray,
									 CollisionWorld *world,
									 float maxDistance)
									 :
mRayResultCallback(0),
mWorld(world),
mRay(ray),
mMaxDistance(maxDistance)
{
}
//----------------------------------------------------------------------------
C_RayResultCallback::~C_RayResultCallback()
{
	if (mRayResultCallback)
	{
		delete mRayResultCallback;
		mRayResultCallback = 0;
	}
}
//----------------------------------------------------------------------------
bool C_RayResultCallback::IsCollide () const
{
	return mRayResultCallback->hasHit();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// C_ClosestRayResultCallback
//----------------------------------------------------------------------------
C_ClosestRayResultCallback::C_ClosestRayResultCallback(
	const PX2::Ray3f &ray,
	CollisionWorld *world, float maxDistance)
	:
C_RayResultCallback(ray, world, maxDistance)
{
	mRayResultCallback = new btCollisionWorld::ClosestRayResultCallback (
		Converter::ConvertFrom(GetRayStartPoint()), 
		Converter::ConvertFrom(GetRayEndPoint()));
}
//----------------------------------------------------------------------------
C_ClosestRayResultCallback::~C_ClosestRayResultCallback ()
{
}
//----------------------------------------------------------------------------
Collisionable *C_ClosestRayResultCallback::GetCollisionable () const
{
	return mWorld->Find(((btCollisionWorld::ClosestRayResultCallback *)mRayResultCallback)
		->m_collisionObject);
}
//----------------------------------------------------------------------------
Vector3f C_ClosestRayResultCallback::GetCollisionPoint () const
{
	return Converter::Vector3fConvertFrom(GetBulletClosestRayResultCallback()
		->m_hitPointWorld);
}
//----------------------------------------------------------------------------
Vector3f C_ClosestRayResultCallback::GetCollisionNormal () const
{
	return Converter::Vector3fConvertFrom(GetBulletClosestRayResultCallback()
		->m_hitNormalWorld);
}
//----------------------------------------------------------------------------