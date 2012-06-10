/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectEvent.inl
*
*/

inline TRange<float> EffectEvent::GetTimeRange () const
{
	return mTimeRange;
}
//----------------------------------------------------------------------------
inline void EffectEvent::SetTimeRange (const TRange<float> range)
{
	mTimeRange = range;
}
//----------------------------------------------------------------------------
inline float EffectEvent::GetActivateTime() const
{
	return mActivateTime;
}
//----------------------------------------------------------------------------
inline void EffectEvent::SetActivateTime(float actTime)
{
	mActivateTime = actTime; 
}
//----------------------------------------------------------------------------
inline bool EffectEvent::IsFadeTo () const
{
	return mIsFadeTo;
}
//----------------------------------------------------------------------------
inline void EffectEvent::SetBeFadeTo (bool fade)
{
	mIsFadeTo = fade;
}
//----------------------------------------------------------------------------