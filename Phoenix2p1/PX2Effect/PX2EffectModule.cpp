/*
*
* 文件名称	：	PX2EffectModule.cpp
*
*/

#include "PX2EffectModule.hpp"
#include "PX2ParticleEmitterControl.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, EffectModule);
PX2_IMPLEMENT_STREAM(EffectModule);
PX2_IMPLEMENT_ABSTRACT_FACTORY(EffectModule);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, EffectModule);

//----------------------------------------------------------------------------
EffectModule::EffectModule (ModuleType type)
	:
mModuleType(type),
mIsForInit(false),
mIsRange(false)
{
}
//----------------------------------------------------------------------------
EffectModule::~EffectModule ()
{
}
//----------------------------------------------------------------------------
void EffectModule::SetRange (bool range)
{
	mIsRange = range;
}
//----------------------------------------------------------------------------
int EffectModule::GetNumKeyPoints ()
{
	if (MT_FLOAT == mModuleType)
	{
		return mCurveFloatMin.GetNumPoints();
	}
	else if (MT_FLOAT3 == mModuleType)
	{
		return mCurveFloat3Min.GetNumPoints();
	}

	return 0;
}
//----------------------------------------------------------------------------
float *EffectModule::GetKeyPointInVal (int i)
{
	if (MT_FLOAT == mModuleType)
	{
		return &(mCurveFloatMin.Points[i].InVal);
	}
	else if (MT_FLOAT3 == mModuleType)
	{
		return &(mCurveFloat3Min.Points[i].InVal);
	}

	return 0;
}
//----------------------------------------------------------------------------
float *EffectModule::GetKeyPointOutValFloatMin (int i)
{
	if (MT_FLOAT == mModuleType)
	{
		return &(mCurveFloatMin.Points[i].OutVal);
	}

	return 0;
}
//----------------------------------------------------------------------------
float *EffectModule::GetKeyPointOutValFloatMax (int i)
{
	if (MT_FLOAT == mModuleType)
	{
		return &(mCurveFloatMax.Points[i].OutVal);
	}

	return 0;
}
//----------------------------------------------------------------------------
Float3 *EffectModule::GetKeyPointOutValFloat3Min (int i)
{
	if (MT_FLOAT3 == mModuleType)
	{
		return &(mCurveFloat3Min.Points[i].OutVal);
	}

	return 0;
}
//----------------------------------------------------------------------------
Float3 *EffectModule::GetKeyPointOutValFloat3Max (int i)
{
	if (MT_FLOAT3 == mModuleType)
	{
		return &(mCurveFloat3Max.Points[i].OutVal);
	}

	return 0;
}
//----------------------------------------------------------------------------
float *EffectModule::GetKeyPointArriveTangentFloatMin (int i)
{
	if (MT_FLOAT == mModuleType)
	{
		return &(mCurveFloatMin.Points[i].ArriveTangent);
	}

	return 0;
}
//----------------------------------------------------------------------------
float *EffectModule::GetKeyPointArriveTangentFloatMax (int i)
{
	if (MT_FLOAT == mModuleType)
	{
		return &(mCurveFloatMax.Points[i].ArriveTangent);
	}

	return 0;
}
//----------------------------------------------------------------------------
float *EffectModule::GetKeyPointLeaveTangentFloatMin (int i)
{
	if (MT_FLOAT == mModuleType)
	{
		return &(mCurveFloatMin.Points[i].LeaveTangent);
	}

	return 0;
}
//----------------------------------------------------------------------------
float *EffectModule::GetKeyPointLeaveTangentFloatMax (int i)
{
	if (MT_FLOAT == mModuleType)
	{
		return &(mCurveFloatMax.Points[i].LeaveTangent);
	}

	return 0;
}
//----------------------------------------------------------------------------
Float3 *EffectModule::GetKeyPointArriveTangentFloat3Min (int i)
{
	if (MT_FLOAT3 == mModuleType)
	{
		return &(mCurveFloat3Min.Points[i].ArriveTangent);
	}

	return 0;
}
//----------------------------------------------------------------------------
Float3 *EffectModule::GetKeyPointArriveTangentFloat3Max (int i)
{
	if (MT_FLOAT3 == mModuleType)
	{
		return &(mCurveFloat3Max.Points[i].ArriveTangent);
	}

	return 0;
}
//----------------------------------------------------------------------------
Float3 *EffectModule::GetKeyPointLeaveTangentFloat3Min (int i)
{
	if (MT_FLOAT3 == mModuleType)
	{
		return &(mCurveFloat3Min.Points[i].LeaveTangent);
	}

	return 0;
}
//----------------------------------------------------------------------------
Float3 *EffectModule::GetKeyPointLeaveTangentFloat3Max (int i)
{
	if (MT_FLOAT3 == mModuleType)
	{
		return &(mCurveFloat3Max.Points[i].LeaveTangent);
	}

	return 0;
}
//----------------------------------------------------------------------------
void EffectModule::UpdateParticleEmitter (ParticleEmitterController &ctrl,
	double ctrlTime)
{
	PX2_UNUSED(ctrl);
}
//----------------------------------------------------------------------------
void EffectModule::UpdateParticle (Particle &particle, double ctrlTime)
{
	PX2_UNUSED(particle);
}
//----------------------------------------------------------------------------
void EffectModule::OnRemove (ParticleEmitterController &ctrl)
{
	PX2_UNUSED(ctrl);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EffectModule::EffectModule (LoadConstructor value)
	:
Object(value),
mModuleType(MT_FLOAT),
mIsForInit(false),
mIsRange(false)
{
}
//----------------------------------------------------------------------------
void EffectModule::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);

	source.ReadBool(mIsForInit);
	source.ReadBool(mIsRange);
	source.ReadEnum(mModuleType);
	source.ReadAggregate(mCurveFloatMin);
	source.ReadAggregate(mCurveFloatMax);
	source.ReadAggregate(mCurveFloat3Min);
	source.ReadAggregate(mCurveFloat3Max);

	PX2_END_DEBUG_STREAM_LOAD(EffectModule, source);
}
//----------------------------------------------------------------------------
void EffectModule::Link (InStream& source)
{
	Object::Link(source);
}
//----------------------------------------------------------------------------
void EffectModule::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool EffectModule::Register (OutStream& target) const
{
	return Object::Register(target);
}
//----------------------------------------------------------------------------
void EffectModule::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);

	target.WriteBool(mIsForInit);
	target.WriteBool(mIsRange);
	target.WriteEnum(mModuleType);
	target.WriteAggregate(mCurveFloatMin);
	target.WriteAggregate(mCurveFloatMax);
	target.WriteAggregate(mCurveFloat3Min);
	target.WriteAggregate(mCurveFloat3Max);

	PX2_END_DEBUG_STREAM_SAVE(EffectModule, target);
}
//----------------------------------------------------------------------------
int EffectModule::GetStreamingSize () const
{
	int size = Object::GetStreamingSize();
	size += PX2_BOOLSIZE(mIsForInit);
	size += PX2_BOOLSIZE(mIsRange);
	size += PX2_ENUMSIZE(mModuleType);
	size += mCurveFloatMin.GetStreamSize();
	size += mCurveFloatMax.GetStreamSize();
	size += mCurveFloat3Min.GetStreamSize();
	size += mCurveFloat3Max.GetStreamSize();

	return size;
}
//----------------------------------------------------------------------------