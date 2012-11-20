/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Actor.inl
*
*/

//----------------------------------------------------------------------------
inline PX2::Scene *Actor::GetScene ()
{
	return mScene;
}
//----------------------------------------------------------------------------
inline APoint Actor::GetPosition ()
{
	return mPosition;
}
//----------------------------------------------------------------------------
inline APoint Actor::GetScale ()
{
	return mScale;
}
//----------------------------------------------------------------------------
inline APoint Actor::GetRotation ()
{
	return mRotation;
}
//----------------------------------------------------------------------------
inline bool Actor::IsVisible ()
{
	return mVisible;
}
//----------------------------------------------------------------------------
inline float Actor::GetTransparent ()
{
	return mTransAlpha;
}
//----------------------------------------------------------------------------
inline Movable *Actor::GetMovable ()
{
	return mMovable;
}
//----------------------------------------------------------------------------
inline Movable *Actor::GetHelpMovable ()
{
	return mHelpMovable;
}
//----------------------------------------------------------------------------
inline bool Actor::IsHelpMovableShow ()
{
	return mShowHelpMovable;
}
//----------------------------------------------------------------------------