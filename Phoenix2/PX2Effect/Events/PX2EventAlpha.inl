/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EventAlpha.inl
*
*/

//----------------------------------------------------------------------------
inline void ParticleEvent_Alpha::SetAlphaRange (const TRange<float> range)
{
	mAlpha = range;
}
//----------------------------------------------------------------------------
inline TRange<float> ParticleEvent_Alpha::GetAlphaRange () const
{
	return mAlpha;
}
//----------------------------------------------------------------------------
inline bool ParticleEvent_Alpha::FadeAllowed ()
{
	return true;
}
//----------------------------------------------------------------------------