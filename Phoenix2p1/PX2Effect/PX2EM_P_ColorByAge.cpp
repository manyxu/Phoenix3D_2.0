/*
*
* 文件名称	：	PX2EM_P_ColorByAge.cpp
*
*/

#include "PX2EM_P_ColorByAge.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_ColorByAge);
PX2_IMPLEMENT_STREAM(EM_P_ColorByAge);
PX2_IMPLEMENT_FACTORY(EM_P_ColorByAge);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_ColorByAge);

//----------------------------------------------------------------------------
EM_P_ColorByAge::EM_P_ColorByAge ()
	:
EffectModule(MT_FLOAT3)
{
	SetName("P_ColorByAge");

	mCurveFloat3Min.AddPoint(0.0f, Float3::WHITE, Float3::ZERO, Float3::ZERO,
		ICM_CURVE_AUTO);
	mCurveFloat3Max.AddPoint(0.0f, Float3::WHITE, Float3::ZERO, Float3::ZERO,
		ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_ColorByAge::~EM_P_ColorByAge ()
{
}
//----------------------------------------------------------------------------
void EM_P_ColorByAge::UpdateParticle (Particle &particle,
	double ctrlTime)
{
	if (!mIsRange)
	{
		particle.Color = mCurveFloat3Min.Eval((float)ctrlTime, Float3::WHITE);
	}
	else
	{
		Float3 valMin = mCurveFloat3Min.Eval((float)ctrlTime, Float3::WHITE);
		Float3 valMax = mCurveFloat3Max.Eval((float)ctrlTime, Float3::WHITE);

		particle.Color = Float3(
			Mathf::IntervalRandom(valMin[0], valMax[0]),
			Mathf::IntervalRandom(valMin[1], valMax[1]),
			Mathf::IntervalRandom(valMin[2], valMax[2]));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_ColorByAge::EM_P_ColorByAge (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_ColorByAge::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_ColorByAge, source);
}
//----------------------------------------------------------------------------
void EM_P_ColorByAge::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_ColorByAge::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_ColorByAge::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_ColorByAge::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_ColorByAge, target);
}
//----------------------------------------------------------------------------
int EM_P_ColorByAge::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------