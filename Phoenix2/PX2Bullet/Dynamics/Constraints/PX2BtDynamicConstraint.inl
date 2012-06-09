/*
*
* ÎÄ¼þÃû³Æ	£º	PX2BtDynamicConstraint.inl
*
*/

//----------------------------------------------------------------------------
inline btTypedConstraint *TypedConstraint::GetBulletTypedConstraint () const
{
	return mConstraint;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ActionInterface
//----------------------------------------------------------------------------
inline btActionInterface* ActionInterface::GetBulletActionInterface() const
{
	return mActionInterface;
}
//----------------------------------------------------------------------------