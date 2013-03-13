/*
*
* 文件名称	：	PX2EM_P_RotateSpeedInit.cpp
*
*/

#include "PX2EM_P_RotateSpeedInit.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_RotateSpeedInit);
PX2_IMPLEMENT_STREAM(EM_P_RotateSpeedInit);
PX2_IMPLEMENT_FACTORY(EM_P_RotateSpeedInit);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_RotateSpeedInit);

//----------------------------------------------------------------------------
EM_P_RotateSpeedInit::EM_P_RotateSpeedInit ()
	:
EffectModule(MT_FLOAT)
{
	SetName("P_RotateSpeedInit");

	mCurveFloatMin.AddPoint(0.0f, 4.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
	mCurveFloatMax.AddPoint(0.0f, 4.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_RotateSpeedInit::~EM_P_RotateSpeedInit ()
{
}
//----------------------------------------------------------------------------
void EM_P_RotateSpeedInit::UpdateParticle (Particle &particle,
	double ctrlTime)
{
	if (0.0f == particle.Age)
	{
		if (!mIsRange)
		{
			particle.RotSpeedInit = mCurveFloatMin.Eval((float)ctrlTime, 0.0f);
			particle.RotSpeed = particle.RotSpeedInit;
		}
		else
		{
			particle.RotSpeedInit = Mathf::IntervalRandom(
				mCurveFloatMin.Eval((float)ctrlTime, 0.0f),
				mCurveFloatMax.Eval((float)ctrlTime, 0.0f));
			particle.RotSpeed = particle.RotSpeedInit;
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_RotateSpeedInit::EM_P_RotateSpeedInit (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_RotateSpeedInit::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_RotateSpeedInit, source);
}
//----------------------------------------------------------------------------
void EM_P_RotateSpeedInit::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_RotateSpeedInit::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_RotateSpeedInit::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_RotateSpeedInit::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_RotateSpeedInit, target);
}
//----------------------------------------------------------------------------
int EM_P_RotateSpeedInit::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------