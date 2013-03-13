/*
*
* 文件名称	：	PX2EM_P_SizeByAge.cpp
*
*/

#include "PX2EM_P_SizeByAge.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_SizeByAge);
PX2_IMPLEMENT_STREAM(EM_P_SizeByAge);
PX2_IMPLEMENT_FACTORY(EM_P_SizeByAge);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_SizeByAge);

//----------------------------------------------------------------------------
EM_P_SizeByAge::EM_P_SizeByAge ()
	:
EffectModule(MT_FLOAT)
{
	SetName("P_SizeByAge");

	mCurveFloatMin.AddPoint(0.0f, 1.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
	mCurveFloatMax.AddPoint(0.0f, 1.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_SizeByAge::~EM_P_SizeByAge ()
{
}
//----------------------------------------------------------------------------
void EM_P_SizeByAge::UpdateParticle (Particle &particle,
	double ctrlTime)
{
	if (0.0f == particle.Age)
		return;

	if (!mIsRange)
	{
		float val = mCurveFloatMin.Eval(particle.Age, 0.0f);
		particle.SizeU = particle.SizeUInit * val;
		particle.SizeR = particle.SizeRInit * val;
		particle.SizeD = particle.SizeDInit * val;
	}
	else
	{
		float valMin = mCurveFloatMin.Eval(particle.Age, 0.0f);
		float valMax = mCurveFloatMax.Eval(particle.Age, 0.0f);
		float val = Mathf::IntervalRandom(valMin, valMax);
		particle.SizeU = particle.SizeUInit * val;
		particle.SizeR = particle.SizeRInit * val;
		particle.SizeD = particle.SizeDInit * val;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_SizeByAge::EM_P_SizeByAge (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_SizeByAge::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_SizeByAge, source);
}
//----------------------------------------------------------------------------
void EM_P_SizeByAge::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_SizeByAge::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_SizeByAge::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_SizeByAge::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_SizeByAge, target);
}
//----------------------------------------------------------------------------
int EM_P_SizeByAge::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------------