/*
*
* 文件名称	：	PX2EM_P_Speed.cpp
*
*/

#include "PX2EM_P_SpeedInit.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_SpeedInit);
PX2_IMPLEMENT_STREAM(EM_P_SpeedInit);
PX2_IMPLEMENT_FACTORY(EM_P_SpeedInit);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_SpeedInit);

//----------------------------------------------------------------------------
EM_P_SpeedInit::EM_P_SpeedInit ()
	:
EffectModule(MT_FLOAT)
{
	SetName("P_SpeedInit");

	mCurveFloatMin.AddPoint(0.0f, 4.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
	mCurveFloatMax.AddPoint(0.0f, 4.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_SpeedInit::~EM_P_SpeedInit ()
{
}
//----------------------------------------------------------------------------
void EM_P_SpeedInit::UpdateParticle (Particle &particle,
	double ctrlTime)
{
	if (0.0f == particle.Age)
	{
		if (!mIsRange)
		{
			particle.SpeedInit = mCurveFloatMin.Eval((float)ctrlTime, 0.0f);
			particle.Speed = particle.SpeedInit;
		}
		else
		{
			particle.SpeedInit = Mathf::IntervalRandom(
				mCurveFloatMin.Eval((float)ctrlTime, 0.0f),
				mCurveFloatMax.Eval((float)ctrlTime, 0.0f));
			particle.Speed = particle.SpeedInit;
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_SpeedInit::EM_P_SpeedInit (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_SpeedInit::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_SpeedInit, source);
}
//----------------------------------------------------------------------------
void EM_P_SpeedInit::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_SpeedInit::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_SpeedInit::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_SpeedInit::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_SpeedInit, target);
}
//----------------------------------------------------------------------------
int EM_P_SpeedInit::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------