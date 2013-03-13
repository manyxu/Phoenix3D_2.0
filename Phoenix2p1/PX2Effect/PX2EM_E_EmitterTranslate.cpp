/*
*
* 文件名称	：	PX2EM_E_EmitterTrans.cpp
*
*/

#include "PX2EM_E_EmitterTranslate.hpp"
#include "PX2ParticleEmitter.hpp"
#include "PX2ParticleEmitterControl.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_E_EmitterTranslate);
PX2_IMPLEMENT_STREAM(EM_E_EmitterTranslate);
PX2_IMPLEMENT_FACTORY(EM_E_EmitterTranslate);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_E_EmitterTranslate);

//----------------------------------------------------------------------------
EM_E_EmitterTranslate::EM_E_EmitterTranslate ()
	:
EffectModule(MT_FLOAT3)
{
	SetName("E_EmitterTranslate");

	mCurveFloat3Min.AddPoint(0.0f, Float3::ZERO, Float3::ZERO, Float3::ZERO,
		ICM_CURVE_AUTO);
	mCurveFloat3Max.AddPoint(0.0f, Float3::ZERO, Float3::ZERO, Float3::ZERO,
		ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_E_EmitterTranslate::~EM_E_EmitterTranslate ()
{
}
//----------------------------------------------------------------------------
void EM_E_EmitterTranslate::UpdateParticleEmitter (
	ParticleEmitterController &ctrl, double ctrlTime)
{
	ParticleEmitter *emitter = DynamicCast<ParticleEmitter>(ctrl.GetObject());
	if (!emitter)
		return;

	if (!mIsRange)
	{
		Float3 trans = mCurveFloat3Min.Eval((float)ctrlTime, Float3::WHITE);
		emitter->LocalTransform.SetTranslate(trans);
	}
	else
	{
		Float3 valMin = mCurveFloat3Min.Eval((float)ctrlTime, Float3::WHITE);
		Float3 valMax = mCurveFloat3Max.Eval((float)ctrlTime, Float3::WHITE);	

		Float3 trans = Float3(
			Mathf::IntervalRandom(valMin[0], valMax[0]),
			Mathf::IntervalRandom(valMin[1], valMax[1]),
			Mathf::IntervalRandom(valMin[2], valMax[2]));

		emitter->LocalTransform.SetTranslate(trans);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_E_EmitterTranslate::EM_E_EmitterTranslate (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_E_EmitterTranslate::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_E_EmitterTranslate, source);
}
//----------------------------------------------------------------------------
void EM_E_EmitterTranslate::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_E_EmitterTranslate::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_E_EmitterTranslate::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_E_EmitterTranslate::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_E_EmitterTranslate, target);
}
//----------------------------------------------------------------------------
int EM_E_EmitterTranslate::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------