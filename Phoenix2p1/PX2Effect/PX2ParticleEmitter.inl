/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ParticleEmitter.inl
*
*/

//----------------------------------------------------------------------------
inline EffectPlayType ParticleEmitter::GetEffectPlayType ()
{
	return mEffectPlayType;
}
//----------------------------------------------------------------------------
inline float ParticleEmitter::GetEffectPlayLife ()
{
	return mEffectPlayLife;
}
//----------------------------------------------------------------------------
inline bool ParticleEmitter::IsPlaying ()
{
	return mIsPlaying;
}
//----------------------------------------------------------------------------
inline bool ParticleEmitter::IsFixedBound ()
{
	return mIsFixedBound;
}
//----------------------------------------------------------------------------
inline APoint ParticleEmitter::GetFixedBoundCenter ()
{
	return mFixedCenter;
}
//----------------------------------------------------------------------------
inline float ParticleEmitter::GetFixedBoundRadius ()
{
	return mFixedBoundRadius;
}
//----------------------------------------------------------------------------
inline bool ParticleEmitter::IsLocal ()
{
	return mIsLocal;
}
//----------------------------------------------------------------------------
inline ParticleEmitter::FaceType ParticleEmitter::GetFaceType ()
{
	return mFaceType;
}
//----------------------------------------------------------------------------
inline ParticleEmitter::RotateAxisType ParticleEmitter::GetRotateAxisType ()
{
	return mRotateAxisType;
}
//----------------------------------------------------------------------------
inline int ParticleEmitter::GetBlendMode ()
{
	return mBlendMode;
}
//----------------------------------------------------------------------------
inline ParticleEmitterController *ParticleEmitter::GetParticleEmitterControl ()
{
	return mEmitterControl;
}
//----------------------------------------------------------------------------
inline Texture2D *ParticleEmitter::GetTexture ()
{
	return mTexture;
}
//----------------------------------------------------------------------------