/*
*
* 文件名称	：	PX2EventSpeed.cpp
*
*/

#include "PX2EventSpeed.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectEvent, ParticleEvent_Speed);
PX2_IMPLEMENT_STREAM(ParticleEvent_Speed);
PX2_IMPLEMENT_FACTORY(ParticleEvent_Speed);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectEvent, ParticleEvent_Speed);

//----------------------------------------------------------------------------
ParticleEvent_Speed::ParticleEvent_Speed ()
{
	mSpeed.Value0 = 0.0f;
	mSpeed.Value1 = 0.0f;
}
//----------------------------------------------------------------------------
ParticleEvent_Speed::~ParticleEvent_Speed ()
{
}
//----------------------------------------------------------------------------
void ParticleEvent_Speed::UpdateParticle (Particle &particle)
{
	if (!IsFadeTo())
	{
		particle.Speed = mSpeed.GetRandomInRange();
		particle.SpeedStep = 0.0f;
	}

	if (NextEvent)
	{
		ParticleEvent_Speed *ent = static_cast<ParticleEvent_Speed*>(
			NextEvent);

		float nextSpeed = ent->GetSpeedRange().GetRandomInRange();

		float timeDelta = ent->GetActivateTime() - GetActivateTime();
		if (timeDelta == 0.0f)
			timeDelta = 1.0f;

		particle.SpeedStep = (nextSpeed - particle.Speed)/timeDelta;
	}
	else
	{
		particle.Speed = mSpeed.GetRandomInRange();
		particle.SpeedStep = 0.0f;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
ParticleEvent_Speed::ParticleEvent_Speed (LoadConstructor value)
:
EffectEvent(value)
{
}
//----------------------------------------------------------------------------
void ParticleEvent_Speed::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectEvent::Load(source);

	source.Read(mSpeed.Value0);
	source.Read(mSpeed.Value1);

	PX2_END_DEBUG_STREAM_LOAD(ParticleEvent_Speed, source);
}
//----------------------------------------------------------------------------
void ParticleEvent_Speed::Link (InStream& source)
{
	EffectEvent::Link(source);
}
//----------------------------------------------------------------------------
void ParticleEvent_Speed::PostLink ()
{
	EffectEvent::PostLink();
}
//----------------------------------------------------------------------------
bool ParticleEvent_Speed::Register (OutStream& target) const
{
	if (EffectEvent::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void ParticleEvent_Speed::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectEvent::Save(target);

	target.Write(mSpeed.Value0);
	target.Write(mSpeed.Value1);

	PX2_END_DEBUG_STREAM_SAVE(ParticleEvent_Speed, target);
}
//----------------------------------------------------------------------------
int ParticleEvent_Speed::GetStreamingSize () const
{
	int size = EffectEvent::GetStreamingSize();
	size += sizeof(mSpeed.Value0)*2;

	return size;
}
//----------------------------------------------------------------------------