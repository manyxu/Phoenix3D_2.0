/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ParticleEmitterControl.inl
*
*/

//----------------------------------------------------------------------------
inline ParticleEmitterController::PlacerType ParticleEmitterController
	::GetPlacerType ()
{
	return mPlacerType;
}
//----------------------------------------------------------------------------
inline float ParticleEmitterController::GetPlacerInLength ()
{
	return mPlacerInLength;
}
//----------------------------------------------------------------------------
inline float ParticleEmitterController::GetPlacerOutLength ()
{
	return mPlacerOutLength;
}
//----------------------------------------------------------------------------
inline float ParticleEmitterController::GetPlacerInWidth ()
{
	return mPlacerInWidth;
}
//----------------------------------------------------------------------------
inline float ParticleEmitterController::GetPlacerOutWidth ()
{
	return mPlacerOutWidth;
}
//----------------------------------------------------------------------------
inline float ParticleEmitterController::GetPlacerInHeight ()
{
	return mPlacerInHeight;
}
//----------------------------------------------------------------------------
inline float ParticleEmitterController::GetPlacerOutHeight ()
{
	return mPlacerOutHeight;
}
//----------------------------------------------------------------------------
inline int ParticleEmitterController::GetMaxNumParticles () const
{
	return mMaxNumParticles;
}
//----------------------------------------------------------------------------
inline void ParticleEmitterController::SetCurEmitRate (float rate)
{
	mCurEmitRate = rate;
}
//----------------------------------------------------------------------------
inline float ParticleEmitterController::GetCurEmitRate ()
{
	return mCurEmitRate;
}
//----------------------------------------------------------------------------
inline TRecyclingArray<Particle>* &ParticleEmitterController::GetArray ()
{
	return mParticleArray;
}
//----------------------------------------------------------------------------