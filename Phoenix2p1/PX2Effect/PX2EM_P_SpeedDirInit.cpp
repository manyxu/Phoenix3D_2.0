/*
*
* 文件名称	：	PX2EM_E_EmitDir.cpp
*
*/

#include "PX2EM_P_SpeedDirInit.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_SpeedDirInit);
PX2_IMPLEMENT_STREAM(EM_P_SpeedDirInit);
PX2_IMPLEMENT_FACTORY(EM_P_SpeedDirInit);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_SpeedDirInit);

//----------------------------------------------------------------------------
EM_P_SpeedDirInit::EM_P_SpeedDirInit ()
	:
EffectModule(MT_FLOAT3)
{
	SetName("P_SpeedDirInit");

	mCurveFloat3Min.AddPoint(0.0f, Float3(0.0f, 0.0f, 1.0f), Float3::ZERO,
		Float3::ZERO, ICM_CURVE_AUTO);
	mCurveFloat3Max.AddPoint(0.0f, Float3(0.0f, 0.0f, 1.0f),  Float3::ZERO,
		Float3::ZERO, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_SpeedDirInit::~EM_P_SpeedDirInit ()
{
}
//----------------------------------------------------------------------------
void EM_P_SpeedDirInit::UpdateParticle (Particle &particle, double ctrlTime)
{
	if (0.0f == particle.Age)
	{
		if (!mIsRange)
		{
			AVector val = mCurveFloat3Min.Eval((float)ctrlTime, Float3::ZERO);
			val.Normalize();
			particle.SpeedDirInit = val;
			particle.SpeedDir = val;
		}
		else
		{
			Float3 valMin = mCurveFloat3Min.Eval((float)ctrlTime, Float3::ZERO);
			Float3 valMax = mCurveFloat3Max.Eval((float)ctrlTime, Float3::ZERO);

			Float3 val = Float3(Mathf::IntervalRandom(valMin[0], valMax[0]),
				Mathf::IntervalRandom(valMin[1], valMax[1]),
				Mathf::IntervalRandom(valMin[2], valMax[2]));

			AVector dir(val);
			dir.Normalize();

			particle.SpeedDirInit = dir;
			particle.SpeedDir = dir;
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_SpeedDirInit::EM_P_SpeedDirInit (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_SpeedDirInit::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_SpeedDirInit, source);
}
//----------------------------------------------------------------------------
void EM_P_SpeedDirInit::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_SpeedDirInit::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_SpeedDirInit::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_SpeedDirInit::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_SpeedDirInit, target);
}
//----------------------------------------------------------------------------
int EM_P_SpeedDirInit::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------------