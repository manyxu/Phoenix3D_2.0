/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtDynamicableRigidBody.inl
*
*/

//----------------------------------------------------------------------------
inline btRigidBody *RigidBody::GetBulletRigidBody() const 
{
	return (btRigidBody*)((btCollisionObject*)mBtCollisionObject);
};
//----------------------------------------------------------------------------
inline btDynamicsWorld *RigidBody::GetBulletDynamicWorld() const 
{ 
	return (btDynamicsWorld*)(mWorld->GetBulletCollisionWorld());
};
//----------------------------------------------------------------------------
inline DynamicWorld *RigidBody::GetDynamicWorld() 
{ 
	return (DynamicWorld*)mWorld;
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// WheeledRigidBody
//----------------------------------------------------------------------------
inline void WheeledRigidBody::SetVehicle (RaycastVehicle *vehicle)
{
	mVehicle = vehicle;
}
//----------------------------------------------------------------------------