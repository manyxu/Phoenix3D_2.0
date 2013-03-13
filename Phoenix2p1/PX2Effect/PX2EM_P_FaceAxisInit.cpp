/*
*
* 文件名称	：	PX2EM_P_FaceAxisInit.cpp
*
*/

#include "PX2EM_P_FaceAxisInit.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, EffectModule, EM_P_FaceAxisInit);
PX2_IMPLEMENT_STREAM(EM_P_FaceAxisInit);
PX2_IMPLEMENT_FACTORY(EM_P_FaceAxisInit);
PX2_IMPLEMENT_DEFAULT_NAMES(EffectModule, EM_P_FaceAxisInit);

//----------------------------------------------------------------------------
EM_P_FaceAxisInit::EM_P_FaceAxisInit ()
	:
EffectModule(MT_FLOAT3)
{
	SetName("P_FaceAxisInit");

	mCurveFloat3Min.AddPoint(0.0f, Float3(0.0f, 0.0f, 1.0f), Float3::ZERO,
		Float3::ZERO, ICM_CURVE_AUTO);
	mCurveFloat3Max.AddPoint(0.0f, Float3(0.0f, 0.0f, 1.0f),  Float3::ZERO,
		Float3::ZERO, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
EM_P_FaceAxisInit::~EM_P_FaceAxisInit ()
{
}
//----------------------------------------------------------------------------
void EM_P_FaceAxisInit::UpdateParticle (Particle &particle, double ctrlTime)
{
	if (0.0f == particle.Age)
	{
		AVector dir = AVector::UNIT_Z;

		if (!mIsRange)
		{
			dir = mCurveFloat3Min.Eval((float)ctrlTime, Float3::ZERO);
			dir.Normalize();
		}
		else
		{
			Float3 valMin = mCurveFloat3Min.Eval((float)ctrlTime, Float3::WHITE);
			Float3 valMax = mCurveFloat3Max.Eval((float)ctrlTime, Float3::WHITE);
			dir = Float3(Mathf::IntervalRandom(valMin[0], valMax[0]),
				Mathf::IntervalRandom(valMin[1], valMax[1]),
				Mathf::IntervalRandom(valMin[2], valMax[2]));
			dir.Normalize();
		}

		particle.DVectorInit = dir;
		particle.DVector = particle.DVectorInit;

		if (particle.DVector != AVector::UNIT_Z)
		{
			particle.RVectorInit = AVector::UNIT_Z.Cross(particle.DVector);
			particle.RVectorInit.Normalize();
			particle.RVector = particle.RVectorInit;

			particle.UVectorInit = particle.DVector.Cross(particle.RVector);
			particle.UVectorInit.Normalize();
			particle.UVector = particle.UVectorInit;
		}
		else
		{
			particle.RVectorInit = AVector::UNIT_X;
			particle.RVector = particle.RVectorInit;
			particle.UVectorInit = AVector::UNIT_Y;
			particle.UVector = particle.UVectorInit;
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EM_P_FaceAxisInit::EM_P_FaceAxisInit (LoadConstructor value)
	:
EffectModule(value)
{
}
//----------------------------------------------------------------------------
void EM_P_FaceAxisInit::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	EffectModule::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EM_P_FaceAxisInit, source);
}
//----------------------------------------------------------------------------
void EM_P_FaceAxisInit::Link (InStream& source)
{
	EffectModule::Link(source);
}
//----------------------------------------------------------------------------
void EM_P_FaceAxisInit::PostLink ()
{
	EffectModule::PostLink();
}
//----------------------------------------------------------------------------
bool EM_P_FaceAxisInit::Register (OutStream& target) const
{
	if (EffectModule::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EM_P_FaceAxisInit::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	EffectModule::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EM_P_FaceAxisInit, target);
}
//----------------------------------------------------------------------------
int EM_P_FaceAxisInit::GetStreamingSize () const
{
	int size = EffectModule::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------