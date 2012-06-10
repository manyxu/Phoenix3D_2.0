/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TransformController.inl
*
*/

//----------------------------------------------------------------------------
inline void TransformController::SetTransform (
	const Transform& localTransform)
{
	mLocalTransform = localTransform;
}
//----------------------------------------------------------------------------
inline const Transform& TransformController::GetTransform () const
{
	return mLocalTransform;
}
//----------------------------------------------------------------------------