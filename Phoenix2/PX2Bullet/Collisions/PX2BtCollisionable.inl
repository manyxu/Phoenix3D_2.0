/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtCollisionable.inl
*
*/

//----------------------------------------------------------------------------
inline btCollisionObject* Collisionable::GetBulletObject() const
{
	return mBtCollisionObject;
}
//----------------------------------------------------------------------------
inline PX2::Movable *Collisionable::GetMovable ()
{
	return mMovable;
}
//----------------------------------------------------------------------------
inline CollisionShape *Collisionable::GetShape () const
{
	return mShape;
}
//----------------------------------------------------------------------------
inline CollisionWorld* Collisionable::GetCollisionWorld() const
{
	return mWorld;
}
//----------------------------------------------------------------------------