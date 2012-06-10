/*
*
* 文件名称	：	PX2EventAlpha.cpp
*
*/

#include "PX2EventAlpha.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectEvent, ParticleEvent_Alpha);
PX2_IMPLEMENT_STREAM(ParticleEvent_Alpha);
PX2_IMPLEMENT_FACTORY(ParticleEvent_Alpha);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectEvent, ParticleEvent_Alpha);

//----------------------------------------------------------------------------
ParticleEvent_Alpha::ParticleEvent_Alpha ()
{
	mAlpha.Value0 = 1.0f;
	mAlpha.Value1 = 1.0f;
}
//----------------------------------------------------------------------------
ParticleEvent_Alpha::~ParticleEvent_Alpha ()
{
}
//----------------------------------------------------------------------------
void ParticleEvent_Alpha::UpdateParticle (Particle &particle)
{
	if (!IsFadeTo())
	{
		particle.Alpha = mAlpha.GetRandomInRange();
		particle.AlphaStep = 0.0f;
	}

	if (NextEvent)
	{
		ParticleEvent_Alpha *ent = static_cast<ParticleEvent_Alpha*>(NextEvent);

		float nextAlpha = ent->GetAlphaRange().GetRandomInRange();

		float timeDelta = ent->GetActivateTime() - GetActivateTime();
		if (timeDelta == 0.0f)
			timeDelta = 1.0f;

		particle.Alpha = (nextAlpha - particle.Alpha)/timeDelta;;
	}
	else
	{
		particle.Alpha = mAlpha.GetRandomInRange();
		particle.AlphaStep = 0.0f;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
ParticleEvent_Alpha::ParticleEvent_Alpha (LoadConstructor value)
:
EffectEvent(value)
{
}
//----------------------------------------------------------------------------
void ParticleEvent_Alpha::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectEvent::Load(source);

	source.Read(mAlpha.Value0);
	source.Read(mAlpha.Value1);

	PX2_END_DEBUG_STREAM_LOAD(ParticleEvent_Alpha, source);
}
//----------------------------------------------------------------------------
void ParticleEvent_Alpha::Link (InStream& source)
{
	EffectEvent::Link(source);
}
//----------------------------------------------------------------------------
void ParticleEvent_Alpha::PostLink ()
{
	EffectEvent::PostLink();
}
//----------------------------------------------------------------------------
bool ParticleEvent_Alpha::Register (OutStream& target) const
{
	if (EffectEvent::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void ParticleEvent_Alpha::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectEvent::Save(target);

	target.Write(mAlpha.Value0);
	target.Write(mAlpha.Value1);

	PX2_END_DEBUG_STREAM_SAVE(ParticleEvent_Alpha, target);
}
//----------------------------------------------------------------------------
int ParticleEvent_Alpha::GetStreamingSize () const
{
	int size = EffectEvent::GetStreamingSize();
	size += sizeof(mAlpha.Value0)*2;

	return size;
}
//----------------------------------------------------------------------------