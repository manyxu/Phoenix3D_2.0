/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EventSpeed.inl
*
*/

//----------------------------------------------------------------------------
inline void ParticleEvent_Speed::SetSpeedRange (const TRange<float> range)
{
	mSpeed = range;
}
//----------------------------------------------------------------------------
inline TRange<float> ParticleEvent_Speed::GetSpeedRange () const
{
	return mSpeed;
}
//----------------------------------------------------------------------------
inline bool ParticleEvent_Speed::FadeAllowed ()
{
	return true;
}
//----------------------------------------------------------------------------