/*
*
* 文件名称	：	PX2EM_P_AlphaByAge.cpp
*
*/

#include "PX2EM_P_AlphaByAge.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_AlphaByAge);
PX2_IMPLEMENT_STREAM(EM_P_AlphaByAge);
PX2_IMPLEMENT_FACTORY(EM_P_AlphaByAge);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_AlphaByAge);

//----------------------------------------------------------------------------
EM_P_AlphaByAge::EM_P_AlphaByAge ()
	:
EffectModule(MT_FLOAT)
{
	SetName("P_AlphaByAge");

	mCurveFloatMin.AddPoint(0.0f, 1.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
	mCurveFloatMax.AddPoint(0.0f, 1.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_AlphaByAge::~EM_P_AlphaByAge ()
{
}
//----------------------------------------------------------------------------
void EM_P_AlphaByAge::UpdateParticle (Particle &particle,
	double ctrlTime)
{
	if (0.0f == particle.Age)
		return;

	if (!mIsRange)
	{
		float val = mCurveFloatMin.Eval(particle.Age, 0.0f);
		particle.Alpha = particle.AlphaInit * val;
	}
	else
	{
		float valMin = mCurveFloatMin.Eval(particle.Age, 0.0f);
		float valMax = mCurveFloatMax.Eval(particle.Age, 0.0f);
		float val = Mathf::IntervalRandom(valMin, valMax);
		particle.Alpha = particle.AlphaInit * val;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_AlphaByAge::EM_P_AlphaByAge (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_AlphaByAge::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_AlphaByAge, source);
}
//----------------------------------------------------------------------------
void EM_P_AlphaByAge::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_AlphaByAge::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_AlphaByAge::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_AlphaByAge::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_AlphaByAge, target);
}
//----------------------------------------------------------------------------
int EM_P_AlphaByAge::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------------