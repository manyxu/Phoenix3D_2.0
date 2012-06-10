/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EventSpeedDir.inl
*
*/

//----------------------------------------------------------------------------
inline void ParticleEvent_SpeedDir::SetSpeedDirRange (const TRange<AVector>
													  range)
{
	mSpeedDir = range;
}
//----------------------------------------------------------------------------
inline TRange<AVector> ParticleEvent_SpeedDir::GetSpeedDirRange () const
{
	return mSpeedDir;
}
//----------------------------------------------------------------------------
inline bool ParticleEvent_SpeedDir::FadeAllowed ()
{
	return true;
}
//----------------------------------------------------------------------------