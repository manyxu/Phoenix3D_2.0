/*
*
* 文件名称	：	PX2EffectEvent.cpp
*
*/

#include "PX2EffectEvent.hpp"
#include "PX2ParticleEmitterControl.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, EffectEvent);
PX2_IMPLEMENT_STREAM(EffectEvent);
PX2_IMPLEMENT_ABSTRACT_FACTORY(EffectEvent);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, EffectEvent);

//----------------------------------------------------------------------------
EffectEvent::EffectEvent ()
:
mActivateTime(0.0f),
mIsFadeTo(true),
NextEvent(0)
{
}
//----------------------------------------------------------------------------
EffectEvent::~EffectEvent ()
{
}
//----------------------------------------------------------------------------
void EffectEvent::UpdateParticleEmitter (ParticleEmitterController &ctrl)
{
	PX2_UNUSED(ctrl);
}
//----------------------------------------------------------------------------
void EffectEvent::UpdateParticle (Particle &particle)
{
	PX2_UNUSED(particle);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EffectEvent::EffectEvent (LoadConstructor value)
:
Object(value),
mActivateTime(0.0f),
mIsFadeTo(false),
NextEvent(0)
{
}
//----------------------------------------------------------------------------
void EffectEvent::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);

	source.Read(mTimeRange.Value0);
	source.Read(mTimeRange.Value1);
	source.ReadBool(mIsFadeTo);

	PX2_END_DEBUG_STREAM_LOAD(EffectEvent, source);
}
//----------------------------------------------------------------------------
void EffectEvent::Link (InStream& source)
{
	Object::Link(source);
}
//----------------------------------------------------------------------------
void EffectEvent::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool EffectEvent::Register (OutStream& target) const
{
	return Object::Register(target);
}
//----------------------------------------------------------------------------
void EffectEvent::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);

	target.Write(mTimeRange.Value0);
	target.Write(mTimeRange.Value1);
	target.WriteBool(mIsFadeTo);

	// mActivateTime 由事件队列建立，不需要保存
	// NextEvent 由事件队列建立，不需要保存

	PX2_END_DEBUG_STREAM_SAVE(EffectEvent, target);
}
//----------------------------------------------------------------------------
int EffectEvent::GetStreamingSize () const
{
	int size = Object::GetStreamingSize();
	size += sizeof(mTimeRange.Value0)*2 + // mTimeRange
		PX2_BOOLSIZE(mIsFadeTo); // mIsFadeTo

	return size;
}
//----------------------------------------------------------------------------