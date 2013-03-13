/*
*
* 文件名称	：	PX2EM_P_LifeInit.cpp
*
*/

#include "PX2EM_P_LifeInit.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_LifeInit);
PX2_IMPLEMENT_STREAM(EM_P_LifeInit);
PX2_IMPLEMENT_FACTORY(EM_P_LifeInit);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_LifeInit);

//----------------------------------------------------------------------------
EM_P_LifeInit::EM_P_LifeInit ()
	:
EffectModule(MT_FLOAT)
{
	SetName("P_LifeInit");

	mCurveFloatMin.AddPoint(0.0f, 1.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
	mCurveFloatMax.AddPoint(0.0f, 1.0f, 0.0f, 0.0f, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_LifeInit::~EM_P_LifeInit ()
{
}
//----------------------------------------------------------------------------
void EM_P_LifeInit::UpdateParticle (Particle &particle,
	double ctrlTime)
{
	if (0.0f == particle.Age)
	{
		if (!mIsRange)
		{
			float val = mCurveFloatMin.Eval((float)ctrlTime, 0.0f);
			particle.Life = val;
		}
		else
		{
			float val = Mathf::IntervalRandom(
				mCurveFloatMin.Eval((float)ctrlTime, 0.0f),
				mCurveFloatMax.Eval((float)ctrlTime, 0.0f));
			particle.Life = val;
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_LifeInit::EM_P_LifeInit (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_LifeInit::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_LifeInit, source);
}
//----------------------------------------------------------------------------
void EM_P_LifeInit::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_LifeInit::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_LifeInit::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_LifeInit::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_LifeInit, target);
}
//----------------------------------------------------------------------------
int EM_P_LifeInit::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------