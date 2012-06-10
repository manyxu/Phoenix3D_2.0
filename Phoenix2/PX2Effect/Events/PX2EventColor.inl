/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EventColor.inl
*
*/

//----------------------------------------------------------------------------
inline void ParticleEvent_Color::SetColorRange (const TRange<Float3> range)
{
	mColor = range;
}
//----------------------------------------------------------------------------
inline TRange<Float3> ParticleEvent_Color::GetColorRange () const
{
	return mColor;
}
//----------------------------------------------------------------------------
inline bool ParticleEvent_Color::FadeAllowed ()
{
	return true;
}
//----------------------------------------------------------------------------