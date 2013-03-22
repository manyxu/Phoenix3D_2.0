/*
*
* 文件名称	：	PX2InterpCurveRotateCtrl.cpp
*
*/

#include "PX2InterpCurveRotateCtrl.hpp"
#include "PX2Movable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, InterpCurveRotateController);
PX2_IMPLEMENT_STREAM(InterpCurveRotateController);
PX2_IMPLEMENT_FACTORY(InterpCurveRotateController);
PX2_IMPLEMENT_DEFAULT_NAMES(Controller, InterpCurveRotateController);

//----------------------------------------------------------------------------
InterpCurveRotateController::InterpCurveRotateController (
	const Float3 &initRotate)
	:
mInitRotate(initRotate)
{
	mRotates.AddPoint(0.0f, mInitRotate, Float3::ZERO, Float3::ZERO, ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
InterpCurveRotateController::~InterpCurveRotateController ()
{
}
//----------------------------------------------------------------------------
bool InterpCurveRotateController::Update (double applicationTime)
{
	if (!Controller::Update(applicationTime))
	{
		return false;
	}

	float ctrlTime = (float)GetControlTime(applicationTime);
	Float3 rotate = mRotates.Eval(ctrlTime, Float3::ZERO);

	Movable* movable = StaticCast<Movable>(mObject);
	movable->LocalTransform.SetRotate(Matrix3f().MakeEulerXYZ(rotate[0],
		rotate[1], rotate[2]));

	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
InterpCurveRotateController::InterpCurveRotateController (LoadConstructor value)
	:
Controller(value)
{
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);
	source.ReadAggregate(mInitRotate);
	source.ReadAggregate(mRotates);

	PX2_END_DEBUG_STREAM_LOAD(InterpCurveRotateController, source);
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::Link (InStream& source)
{
	Controller::Link(source);
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::PostLink ()
{
	Controller::PostLink();
}
//----------------------------------------------------------------------------
bool InterpCurveRotateController::Register (OutStream& target) const
{
	return Controller::Register(target);
}
//----------------------------------------------------------------------------
void InterpCurveRotateController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);
	target.WriteAggregate(mInitRotate);
	target.WriteAggregate(mRotates);

	PX2_END_DEBUG_STREAM_SAVE(InterpCurveRotateController, target);
}
//----------------------------------------------------------------------------
int InterpCurveRotateController::GetStreamingSize () const
{
	int size = Controller::GetStreamingSize();
	size += sizeof(mInitRotate);
	size += mRotates.GetStreamSize();
	return size;
}
//----------------------------------------------------------------------------