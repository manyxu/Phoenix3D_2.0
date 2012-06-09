/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionRay.inl
*
*/

//----------------------------------------------------------------------------
inline btCollisionWorld::RayResultCallback *
C_RayResultCallback::GetBulletRayResultCallback () const
{
	return mRayResultCallback;
}
//----------------------------------------------------------------------------
inline const PX2::Ray3f &C_RayResultCallback::GetRay () const
{
	return mRay;
}
//----------------------------------------------------------------------------
inline PX2::Vector3f C_RayResultCallback::GetRayStartPoint() const
{
	return mRay.Origin;
}
//----------------------------------------------------------------------------
inline PX2::Vector3f C_RayResultCallback::GetRayEndPoint() const
{
	return mRay.Origin + mMaxDistance*mRay.Direction;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// C_ClosestRayResultCallback
//----------------------------------------------------------------------------
inline btCollisionWorld::ClosestRayResultCallback *
C_ClosestRayResultCallback::GetBulletClosestRayResultCallback() const 
{
	return (btCollisionWorld::ClosestRayResultCallback*)
		mRayResultCallback;
}
//----------------------------------------------------------------------------