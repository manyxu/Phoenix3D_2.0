/*
*
* 文件名称	：	PX2EM_P_AccelerateDir.cpp
*
*/

#include "PX2EM_P_AccelerateDir.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_AccelerateDir);
PX2_IMPLEMENT_STREAM(EM_P_AccelerateDir);
PX2_IMPLEMENT_FACTORY(EM_P_AccelerateDir);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_AccelerateDir);

//----------------------------------------------------------------------------
EM_P_AccelerateDir::EM_P_AccelerateDir ()
	:
EffectModule(MT_FLOAT3)
{
	SetName("P_AccelerateDir");

	mCurveFloat3Min.AddPoint(0.0f, Float3(0.0f, 0.0f, -1.0f), Float3::ZERO,
		Float3::ZERO, ICM_CURVE_AUTO);
	mCurveFloat3Max.AddPoint(0.0f, Float3(0.0f, 0.0f, -1.0f), Float3::ZERO,
		Float3::ZERO, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_AccelerateDir::~EM_P_AccelerateDir ()
{
}
//----------------------------------------------------------------------------
void EM_P_AccelerateDir::UpdateParticle (Particle &particle,
	double ctrlTime)
{
	if (!mIsRange)
	{
		AVector dir = mCurveFloat3Min.Eval((float)ctrlTime, Float3::ZERO);
		dir.Normalize();
		particle.AccelerateDir = dir;
	}
	else
	{
		Float3 dirMin = mCurveFloat3Min.Eval((float)ctrlTime, Float3::ZERO);
		Float3 dirMax = mCurveFloat3Min.Eval((float)ctrlTime, Float3::ZERO);
		AVector dir = AVector(Mathf::IntervalRandom(dirMin[0], dirMax[0]),
			Mathf::IntervalRandom(dirMin[1], dirMax[1]),
			Mathf::IntervalRandom(dirMin[2], dirMax[2]));
		dir.Normalize();
		particle.AccelerateDir = dir;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_AccelerateDir::EM_P_AccelerateDir (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_AccelerateDir::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_AccelerateDir, source);
}
//----------------------------------------------------------------------------
void EM_P_AccelerateDir::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_AccelerateDir::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_AccelerateDir::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_AccelerateDir::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_AccelerateDir, target);
}
//----------------------------------------------------------------------------
int EM_P_AccelerateDir::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------