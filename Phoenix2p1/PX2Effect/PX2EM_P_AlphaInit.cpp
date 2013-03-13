/*
*
* 文件名称	：	PX2EM_P_AlphaInit.cpp
*
*/

#include "PX2EM_P_AlphaInit.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_AlphaInit);
PX2_IMPLEMENT_STREAM(EM_P_AlphaInit);
PX2_IMPLEMENT_FACTORY(EM_P_AlphaInit);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_AlphaInit);

//----------------------------------------------------------------------------
EM_P_AlphaInit::EM_P_AlphaInit ()
	:
EffectModule(MT_FLOAT)
{
	SetName("P_AlphaInit");

	mCurveFloatMin.AddPoint(0.0f, 1.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
	mCurveFloatMax.AddPoint(0.0f, 1.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_AlphaInit::~EM_P_AlphaInit ()
{
}
//----------------------------------------------------------------------------
void EM_P_AlphaInit::UpdateParticle (Particle &particle, double ctrlTime)
{
	if (0.0f == particle.Age)
	{
		if (!mIsRange)
		{
			float val = mCurveFloatMin.Points[0].OutVal;
			particle.AlphaInit = val;
			particle.Alpha = particle.AlphaInit;
		}
		else
		{
			float valueMin = mCurveFloatMin.Points[0].OutVal;
			float valueMax = mCurveFloatMax.Points[0].OutVal;

			float val = Lerp<float>(valueMin, valueMax, Mathf::UnitRandom());
			particle.AlphaInit = val;
			particle.Alpha = particle.AlphaInit;
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_AlphaInit::EM_P_AlphaInit (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_AlphaInit::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_AlphaInit, source);
}
//----------------------------------------------------------------------------
void EM_P_AlphaInit::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_AlphaInit::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_AlphaInit::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_AlphaInit::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_AlphaInit, target);
}
//----------------------------------------------------------------------------
int EM_P_AlphaInit::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//------------------------------------