/*
*
* 文件名称	：	PX2InterpCurveTransCtrl.cpp
*
*/

#include "PX2InterpCurveScaleCtrl.hpp"
#include "PX2Movable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, InterpCurveScaleController);
PX2_IMPLEMENT_STREAM(InterpCurveScaleController);
PX2_IMPLEMENT_FACTORY(InterpCurveScaleController);
PX2_IMPLEMENT_DEFAULT_NAMES(Controller, InterpCurveScaleController);

//----------------------------------------------------------------------------
InterpCurveScaleController::InterpCurveScaleController (
	const Float3 &initScale)
	:
mInitScale(initScale)
{
	mScales.AddPoint(0.0f, mInitScale, Float3::ZERO, Float3::ZERO, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
InterpCurveScaleController::~InterpCurveScaleController ()
{
}
//----------------------------------------------------------------------------
bool InterpCurveScaleController::Update (double applicationTime)
{
	if (!Controller::Update(applicationTime))
	{
		return false;
	}

	float ctrlTime = (float)GetControlTime(applicationTime);
	Float3 scale = mScales.Eval(ctrlTime, Float3::ZERO);

	Movable* movable = StaticCast<Movable>(mObject);
	movable->LocalTransform.SetScale(scale);

	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
InterpCurveScaleController::InterpCurveScaleController (LoadConstructor value)
	:
Controller(value)
{
}
//----------------------------------------------------------------------------
void InterpCurveScaleController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);
	source.ReadAggregate(mInitScale);
	source.ReadAggregate(mScales);

	PX2_END_DEBUG_STREAM_LOAD(InterpCurveScaleController, source);
}
//----------------------------------------------------------------------------
void InterpCurveScaleController::Link (InStream& source)
{
	Controller::Link(source);
}
//----------------------------------------------------------------------------
void InterpCurveScaleController::PostLink ()
{
	Controller::PostLink();
}
//----------------------------------------------------------------------------
bool InterpCurveScaleController::Register (OutStream& target) const
{
	return Controller::Register(target);
}
//----------------------------------------------------------------------------
void InterpCurveScaleController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);
	target.WriteAggregate(mInitScale);
	target.WriteAggregate(mScales);

	PX2_END_DEBUG_STREAM_SAVE(InterpCurveScaleController, target);
}
//----------------------------------------------------------------------------
int InterpCurveScaleController::GetStreamingSize () const
{
	int size = Controller::GetStreamingSize();
	size += sizeof(mInitScale);
	size += mScales.GetStreamSize();
	return size;
}
//----------------------------------------------------------------------------