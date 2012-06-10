/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EventSize.inl
*
*/

//----------------------------------------------------------------------------
inline void ParticleEvent_Size::SetSizeURange (TRange<float> range)
{
	mSizeURange = range;
}
//----------------------------------------------------------------------------
inline TRange<float> ParticleEvent_Size::GetSizeURange () const
{
	return mSizeURange;
}
//----------------------------------------------------------------------------
inline void ParticleEvent_Size::SetSizeRRange (TRange<float> range)
{
	mSizeRRange = range;
}
//----------------------------------------------------------------------------
inline TRange<float> ParticleEvent_Size::GetSizeRRange () const
{
	return mSizeRRange;
}
//----------------------------------------------------------------------------
inline bool ParticleEvent_Size::FadeAllowed ()
{
	return true;
}
//----------------------------------------------------------------------------