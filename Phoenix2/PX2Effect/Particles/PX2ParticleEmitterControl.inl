/*
*
* ÎÄ¼şÃû³Æ	£º	PX2ParticleEmitterControl.inl
*
*/

//----------------------------------------------------------------------------
inline int ParticleEmitterController::GetMaxQuantity () const
{
	return mMaxQuantity;
}
//----------------------------------------------------------------------------
inline void ParticleEmitterController::SetEmitRate (float rate)
{
	mEmitRate = rate;
}
//----------------------------------------------------------------------------
inline float ParticleEmitterController::GetEmitRate ()
{
	return mEmitRate;
}
//----------------------------------------------------------------------------
inline void ParticleEmitterController::SetEmitRateStep (float step)
{
	mEmitRateStep = step;
}
//----------------------------------------------------------------------------
inline float ParticleEmitterController::GetEmitRateStep ()
{
	return mEmitRateStep;
}
//----------------------------------------------------------------------------
inline TRecyclingArray<Particle>* &ParticleEmitterController::GetArray ()
{
	return mParticleArray;
}
//----------------------------------------------------------------------------