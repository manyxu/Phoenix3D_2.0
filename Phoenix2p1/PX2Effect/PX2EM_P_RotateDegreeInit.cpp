/*
*
* 文件名称	：	PX2EM_P_RotateDegreeInit.cpp
*
*/

#include "PX2EM_P_RotateDegreeInit.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_RotateDegreeInit);
PX2_IMPLEMENT_STREAM(EM_P_RotateDegreeInit);
PX2_IMPLEMENT_FACTORY(EM_P_RotateDegreeInit);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_RotateDegreeInit);

//----------------------------------------------------------------------------
EM_P_RotateDegreeInit::EM_P_RotateDegreeInit ()
	:
EffectModule(MT_FLOAT)
{
	SetName("P_RotateDegreeInit");

	mCurveFloatMin.AddPoint(0.0f, 4.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
	mCurveFloatMax.AddPoint(0.0f, 4.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_RotateDegreeInit::~EM_P_RotateDegreeInit ()
{
}
//----------------------------------------------------------------------------
void EM_P_RotateDegreeInit::UpdateParticle (Particle &particle,
	double ctrlTime)
{
	if (0.0f == particle.Age)
	{
		if (!mIsRange)
		{
			particle.RotDegreeInit = mCurveFloatMin.Eval((float)ctrlTime, 0.0f);
			particle.RotDegree = particle.RotDegreeInit;
		}
		else
		{
			particle.RotDegreeInit = Mathf::IntervalRandom(
				mCurveFloatMin.Eval((float)ctrlTime, 0.0f),
				mCurveFloatMax.Eval((float)ctrlTime, 0.0f));
			particle.RotDegree = particle.RotDegreeInit;
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_RotateDegreeInit::EM_P_RotateDegreeInit (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_RotateDegreeInit::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_RotateDegreeInit, source);
}
//----------------------------------------------------------------------------
void EM_P_RotateDegreeInit::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_RotateDegreeInit::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_RotateDegreeInit::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_RotateDegreeInit::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_RotateDegreeInit, target);
}
//----------------------------------------------------------------------------
int EM_P_RotateDegreeInit::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------