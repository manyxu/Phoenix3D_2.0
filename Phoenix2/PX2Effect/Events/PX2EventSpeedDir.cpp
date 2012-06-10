/*
*
* 文件名称	：	PX2EventSpeedDir.cpp
*
*/

#include "PX2EventSpeedDir.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectEvent, ParticleEvent_SpeedDir);
PX2_IMPLEMENT_STREAM(ParticleEvent_SpeedDir);
PX2_IMPLEMENT_FACTORY(ParticleEvent_SpeedDir);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectEvent, ParticleEvent_SpeedDir);

//----------------------------------------------------------------------------
ParticleEvent_SpeedDir::ParticleEvent_SpeedDir ()
{
	mSpeedDir.Value0 = AVector::UNIT_Z;
	mSpeedDir.Value1 = AVector::UNIT_Z;
}
//----------------------------------------------------------------------------
ParticleEvent_SpeedDir::~ParticleEvent_SpeedDir ()
{
}
//----------------------------------------------------------------------------
void ParticleEvent_SpeedDir::UpdateParticle (Particle &particle)
{
	if (!IsFadeTo())
	{
		particle.SpeedDir = mSpeedDir.GetRandomInRange();
		particle.SpeedDir.Normalize();
		particle.SpeedDirStep = AVector::ZERO;
	}

	if (NextEvent)
	{
		ParticleEvent_SpeedDir *ent = static_cast<ParticleEvent_SpeedDir*>(
			NextEvent);

		AVector nextSpeedDir = ent->GetSpeedDirRange().GetRandomInRange();
		nextSpeedDir.Normalize();

		float timeDelta = ent->GetActivateTime() - GetActivateTime();
		if (timeDelta == 0.0f)
			timeDelta = 1.0f;

		particle.SpeedDirStep = (nextSpeedDir - particle.SpeedDir)/timeDelta;
	}
	else
	{
		particle.SpeedDir = mSpeedDir.GetRandomInRange();
		particle.SpeedDir.Normalize();
		particle.SpeedDirStep = AVector::ZERO;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
ParticleEvent_SpeedDir::ParticleEvent_SpeedDir (LoadConstructor value)
:
EffectEvent(value)
{
}
//----------------------------------------------------------------------------
void ParticleEvent_SpeedDir::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectEvent::Load(source);

	source.ReadAggregate(mSpeedDir.Value0);
	source.ReadAggregate(mSpeedDir.Value1);

	PX2_END_DEBUG_STREAM_LOAD(ParticleEvent_SpeedDir, source);
}
//----------------------------------------------------------------------------
void ParticleEvent_SpeedDir::Link (InStream& source)
{
	EffectEvent::Link(source);
}
//----------------------------------------------------------------------------
void ParticleEvent_SpeedDir::PostLink ()
{
	EffectEvent::PostLink();
}
//----------------------------------------------------------------------------
bool ParticleEvent_SpeedDir::Register (OutStream& target) const
{
	if (EffectEvent::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void ParticleEvent_SpeedDir::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectEvent::Save(target);

	target.WriteAggregate(mSpeedDir.Value0);
	target.WriteAggregate(mSpeedDir.Value1);

	PX2_END_DEBUG_STREAM_SAVE(ParticleEvent_SpeedDir, target);
}
//----------------------------------------------------------------------------
int ParticleEvent_SpeedDir::GetStreamingSize () const
{
	int size = EffectEvent::GetStreamingSize();
	size += sizeof(mSpeedDir.Value0)*2;

	return size;
}
//----------------------------------------------------------------------------