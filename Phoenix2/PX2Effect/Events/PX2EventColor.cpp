/*
*
* 文件名称	：	PX2EventColor.cpp
*
*/

#include "PX2EventColor.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectEvent, ParticleEvent_Color);
PX2_IMPLEMENT_STREAM(ParticleEvent_Color);
PX2_IMPLEMENT_FACTORY(ParticleEvent_Color);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectEvent, ParticleEvent_Color);

//----------------------------------------------------------------------------
ParticleEvent_Color::ParticleEvent_Color ()
{
	mColor.Value0 = Float3(1.0f, 1.0f, 1.0f);
	mColor.Value1 = Float3(1.0f, 1.0f, 1.0f);
}
//----------------------------------------------------------------------------
ParticleEvent_Color::~ParticleEvent_Color ()
{
}
//----------------------------------------------------------------------------
void ParticleEvent_Color::UpdateParticle (Particle &particle)
{
	if (!IsFadeTo())
	{
		particle.Color = mColor.GetRandomInRange();
		particle.ColorStep = Float3(0.0f, 0.0f, 0.0f);
	}

	if (NextEvent)
	{
		ParticleEvent_Color *ent = static_cast<ParticleEvent_Color*>(NextEvent);

		Float3 nextColor = ent->GetColorRange().GetRandomInRange();

		float timeDelta = ent->GetActivateTime() - GetActivateTime();
		if (timeDelta == 0.0f)
			timeDelta = 1.0f;

		Float3 colorStep((nextColor[0]-particle.Color[0])/timeDelta,
			(nextColor[1]-particle.Color[1])/timeDelta,
			(nextColor[2] - particle.Color[2])/timeDelta);

		particle.ColorStep = colorStep;
	}
	else
	{
		particle.Color = mColor.GetRandomInRange();
		particle.ColorStep = Float3(0.0f, 0.0f, 0.0f);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
ParticleEvent_Color::ParticleEvent_Color (LoadConstructor value)
:
EffectEvent(value)
{
}
//----------------------------------------------------------------------------
void ParticleEvent_Color::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectEvent::Load(source);

	source.ReadAggregate(mColor.Value0);
	source.ReadAggregate(mColor.Value1);

	PX2_END_DEBUG_STREAM_LOAD(ParticleEvent_Color, source);
}
//----------------------------------------------------------------------------
void ParticleEvent_Color::Link (InStream& source)
{
	EffectEvent::Link(source);
}
//----------------------------------------------------------------------------
void ParticleEvent_Color::PostLink ()
{
	EffectEvent::PostLink();
}
//----------------------------------------------------------------------------
bool ParticleEvent_Color::Register (OutStream& target) const
{
	if (EffectEvent::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void ParticleEvent_Color::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectEvent::Save(target);

	target.WriteAggregate(mColor.Value0);
	target.WriteAggregate(mColor.Value1);

	PX2_END_DEBUG_STREAM_SAVE(ParticleEvent_Color, target);
}
//----------------------------------------------------------------------------
int ParticleEvent_Color::GetStreamingSize () const
{
	int size = EffectEvent::GetStreamingSize();
	size += sizeof(mColor.Value0)*2;

	return size;
}
//----------------------------------------------------------------------------