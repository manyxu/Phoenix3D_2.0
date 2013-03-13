/*
*
* 文件名称	：	PX2EffectModuleEmitterRate.cpp
*
*/

#include "PX2EM_E_EmitRate.hpp"
#include "PX2ParticleEmitterControl.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_E_EmitRate);
PX2_IMPLEMENT_STREAM(EM_E_EmitRate);
PX2_IMPLEMENT_FACTORY(EM_E_EmitRate);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_E_EmitRate);

//----------------------------------------------------------------------------
EM_E_EmitRate::EM_E_EmitRate ()
	:
EffectModule(MT_FLOAT)
{
	SetName("E_EmitRate");

	mCurveFloatMin.AddPoint(0.0f, 25.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
	mCurveFloatMax.AddPoint(0.0f, 25.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_E_EmitRate::~EM_E_EmitRate ()
{
}
//----------------------------------------------------------------------------
void EM_E_EmitRate::UpdateParticleEmitter (
	ParticleEmitterController &ctrl, double ctrlTime)
{
	if (!mIsRange)
	{
		ctrl.SetCurEmitRate(mCurveFloatMin.Eval((float)ctrlTime, 0.0f));
	}
	else
	{
		ctrl.SetCurEmitRate(Mathf::IntervalRandom(
			mCurveFloatMin.Eval((float)ctrlTime, 0.0f), 
			mCurveFloatMax.Eval((float)ctrlTime, 0.0f)));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_E_EmitRate::EM_E_EmitRate (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_E_EmitRate::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_E_EmitRate, source);
}
//----------------------------------------------------------------------------
void EM_E_EmitRate::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_E_EmitRate::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_E_EmitRate::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_E_EmitRate::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_E_EmitRate, target);
}
//----------------------------------------------------------------------------
int EM_E_EmitRate::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------------