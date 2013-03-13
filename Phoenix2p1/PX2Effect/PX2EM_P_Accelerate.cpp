/*
*
* 文件名称	：	PX2EM_P_Accelerate.cpp
*
*/

#include "PX2EM_P_Accelerate.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_Accelerate);
PX2_IMPLEMENT_STREAM(EM_P_Accelerate);
PX2_IMPLEMENT_FACTORY(EM_P_Accelerate);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_Accelerate);

//----------------------------------------------------------------------------
EM_P_Accelerate::EM_P_Accelerate ()
	:
EffectModule(MT_FLOAT)
{
	SetName("P_Accelerate");

	mCurveFloatMin.AddPoint(0.0f, 1.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
	mCurveFloatMax.AddPoint(0.0f, 1.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_Accelerate::~EM_P_Accelerate ()
{
}
//----------------------------------------------------------------------------
void EM_P_Accelerate::UpdateParticle (Particle &particle,
	double ctrlTime)
{
	if (!mIsRange)
	{
		particle.Accelerate = mCurveFloatMin.Eval((float)ctrlTime, 0.0f);
	}
	else
	{
		particle.Accelerate = Mathf::IntervalRandom(
			mCurveFloatMin.Eval((float)ctrlTime, 0.0f),
			mCurveFloatMax.Eval((float)ctrlTime, 0.0f));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_Accelerate::EM_P_Accelerate (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_Accelerate::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_Accelerate, source);
}
//----------------------------------------------------------------------------
void EM_P_Accelerate::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_Accelerate::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_Accelerate::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_Accelerate::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_Accelerate, target);
}
//----------------------------------------------------------------------------
int EM_P_Accelerate::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------