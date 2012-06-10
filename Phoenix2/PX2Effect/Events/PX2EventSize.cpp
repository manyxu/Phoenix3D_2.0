/*
*
* 文件名称	：	PX2EventSize.cpp
*
*/

#include "PX2EventSize.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectEvent, ParticleEvent_Size);
PX2_IMPLEMENT_STREAM(ParticleEvent_Size);
PX2_IMPLEMENT_FACTORY(ParticleEvent_Size);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectEvent, ParticleEvent_Size);

//----------------------------------------------------------------------------
ParticleEvent_Size::ParticleEvent_Size ()
{
	mSizeURange.Value0 = 0.1f;
	mSizeURange.Value1 = 0.1f;
	mSizeRRange.Value0 = 0.1f;
	mSizeRRange.Value1 = 0.1f;
}
//----------------------------------------------------------------------------
ParticleEvent_Size::~ParticleEvent_Size ()
{
}
//----------------------------------------------------------------------------
void ParticleEvent_Size::UpdateParticle (Particle &particle)
{
	if (!IsFadeTo())
	{
		particle.SizeU = mSizeURange.GetRandomInRange();
		particle.SizeR = mSizeRRange.GetRandomInRange();
		particle.SizeUStep = 0.0f;
		particle.SizeRStep = 0.0f;
	}

	if (NextEvent)
	{
		ParticleEvent_Size *ent = static_cast<ParticleEvent_Size*>(NextEvent);

		float nextSizeU = ent->GetSizeURange().GetRandomInRange();
		float nextSizeR = ent->GetSizeRRange().GetRandomInRange();

		float timeDelta = ent->GetActivateTime() - GetActivateTime();
		if (timeDelta == 0.0f)
			timeDelta = 1.0f;

		particle.SizeUStep = (nextSizeU - particle.SizeU)/timeDelta;
		particle.SizeRStep = (nextSizeR - particle.SizeR)/timeDelta;
	}
	else
	{
		particle.SizeU = mSizeURange.GetRandomInRange();
		particle.SizeR = mSizeRRange.GetRandomInRange();
		particle.SizeUStep = 0.0f;
		particle.SizeRStep = 0.0f;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
ParticleEvent_Size::ParticleEvent_Size (LoadConstructor value)
:
EffectEvent(value)
{
}
//----------------------------------------------------------------------------
void ParticleEvent_Size::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectEvent::Load(source);

	source.Read(mSizeURange.Value0);
	source.Read(mSizeURange.Value1);
	source.Read(mSizeRRange.Value0);
	source.Read(mSizeRRange.Value1);

	PX2_END_DEBUG_STREAM_LOAD(ParticleEvent_Size, source);
}
//----------------------------------------------------------------------------
void ParticleEvent_Size::Link (InStream& source)
{
	EffectEvent::Link(source);

}
//----------------------------------------------------------------------------
void ParticleEvent_Size::PostLink ()
{
	EffectEvent::PostLink();
}
//----------------------------------------------------------------------------
bool ParticleEvent_Size::Register (OutStream& target) const
{
	if (EffectEvent::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void ParticleEvent_Size::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectEvent::Save(target);

	target.Write(mSizeURange.Value0);
	target.Write(mSizeURange.Value1);
	target.Write(mSizeRRange.Value0);
	target.Write(mSizeRRange.Value1);

	PX2_END_DEBUG_STREAM_SAVE(ParticleEvent_Size, target);
}
//----------------------------------------------------------------------------
int ParticleEvent_Size::GetStreamingSize () const
{
	int size = EffectEvent::GetStreamingSize();
	size += sizeof(mSizeURange.Value0)*4;

	return size;
}
//----------------------------------------------------------------------------