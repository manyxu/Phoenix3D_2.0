/*
*
* 文件名称	：	PX2EM_E_SizeInit.cpp
*
*/

#include "PX2EM_P_SizeInit.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_SizeInit);
PX2_IMPLEMENT_STREAM(EM_P_SizeInit);
PX2_IMPLEMENT_FACTORY(EM_P_SizeInit);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_SizeInit);

//----------------------------------------------------------------------------
EM_P_SizeInit::EM_P_SizeInit ()
	:
EffectModule(MT_FLOAT)
{
	SetName("P_SizeInit");

	mCurveFloatMin.AddPoint(0.0f, 0.5f, 0.0f, 0.0f, ICM_CURVE_AUTO);
	mCurveFloatMax.AddPoint(0.0f, 0.5f, 0.0f, 0.0f, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_SizeInit::~EM_P_SizeInit ()
{
}
//----------------------------------------------------------------------------
void EM_P_SizeInit::UpdateParticle (Particle &particle,
	double ctrlTime)
{
	if (0.0f == particle.Age)
	{
		if (!mIsRange)
		{
			float val = mCurveFloatMin.Points[0].OutVal;

			particle.SizeUInit = val;
			particle.SizeU = particle.SizeUInit;

			particle.SizeRInit = val;
			particle.SizeR = particle.SizeRInit;

			particle.SizeDInit = val;
			particle.SizeD = particle.SizeDInit;
		}
		else
		{
			float valueMin = mCurveFloatMin.Points[0].OutVal;
			float valueMax = mCurveFloatMax.Points[0].OutVal;

			float val = Lerp<float>(valueMin, valueMax, Mathf::UnitRandom());
			particle.SizeUInit = val;
			particle.SizeU = particle.SizeUInit;

			particle.SizeRInit = val;
			particle.SizeR = particle.SizeRInit;

			particle.SizeDInit = val;
			particle.SizeD = particle.SizeDInit;
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_SizeInit::EM_P_SizeInit (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_SizeInit::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_SizeInit, source);
}
//----------------------------------------------------------------------------
void EM_P_SizeInit::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_SizeInit::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_SizeInit::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_SizeInit::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_SizeInit, target);
}
//----------------------------------------------------------------------------
int EM_P_SizeInit::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------