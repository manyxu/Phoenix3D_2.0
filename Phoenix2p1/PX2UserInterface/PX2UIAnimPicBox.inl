/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIAnimPicBox.inl
*
*/

//----------------------------------------------------------------------------
inline int UIAnimPicBox::GetNumFrames ()
{
	return (int)mElements.size();
}
//----------------------------------------------------------------------------
inline int UIAnimPicBox::GetActiveIndex ()
{
	return mActiveIndex;
}
//----------------------------------------------------------------------------
inline UIAnimPicBoxControl *UIAnimPicBox::GetAPBCtrl ()
{
	return mAPBCtrl;
}
//----------------------------------------------------------------------------
inline const std::string &UIAnimPicBox::GetFrameTexPack () const
{
	return mFrameTexPack;
}
//----------------------------------------------------------------------------
inline float UIAnimPicBox::GetIntervalTime ()
{
	return mIntervalTime;
}
//----------------------------------------------------------------------------
inline Movable *UIAnimPicBox::GetAsMovable ()
{
	return this;
}
//----------------------------------------------------------------------------