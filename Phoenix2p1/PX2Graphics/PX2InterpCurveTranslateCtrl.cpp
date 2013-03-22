/*
*
* 文件名称	：	PX2InterpCurveTransCtrl.cpp
*
*/

#include "PX2InterpCurveTranslateCtrl.hpp"
#include "PX2Movable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, InterpCurveTranslateController);
PX2_IMPLEMENT_STREAM(InterpCurveTranslateController);
PX2_IMPLEMENT_FACTORY(InterpCurveTranslateController);
PX2_IMPLEMENT_DEFAULT_NAMES(Controller, InterpCurveTranslateController);

//----------------------------------------------------------------------------
InterpCurveTranslateController::InterpCurveTranslateController (
	const Float3 &trans)
	:
mInitTrans(trans)
{
	mTranslates.AddPoint(0.0f, mInitTrans, Float3::ZERO, Float3::ZERO,
		ICM_CURVE_AUTO);
}
//----------------------------------------------------------------------------
InterpCurveTranslateController::~InterpCurveTranslateController ()
{
}
//----------------------------------------------------------------------------
bool InterpCurveTranslateController::Update (double applicationTime)
{
	if (!Controller::Update(applicationTime))
	{
		return false;
	}

	float ctrlTime = (float)GetControlTime(applicationTime);
	Float3 trans = mTranslates.Eval(ctrlTime, Float3::ZERO);

	Movable* movable = StaticCast<Movable>(mObject);
	movable->LocalTransform.SetTranslate(trans);

	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
InterpCurveTranslateController::InterpCurveTranslateController (LoadConstructor value)
	:
Controller(value)
{
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);
	source.ReadAggregate(mInitTrans);
	source.ReadAggregate(mTranslates);

	PX2_END_DEBUG_STREAM_LOAD(InterpCurveTranslateController, source);
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::Link (InStream& source)
{
	Controller::Link(source);
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::PostLink ()
{
	Controller::PostLink();
}
//----------------------------------------------------------------------------
bool InterpCurveTranslateController::Register (OutStream& target) const
{
	return Controller::Register(target);
}
//----------------------------------------------------------------------------
void InterpCurveTranslateController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);
	target.WriteAggregate(mInitTrans);
	target.WriteAggregate(mTranslates);

	PX2_END_DEBUG_STREAM_SAVE(InterpCurveTranslateController, target);
}
//----------------------------------------------------------------------------
int InterpCurveTranslateController::GetStreamingSize () const
{
	int size = Controller::GetStreamingSize();
	size += sizeof(mInitTrans);
	size += mTranslates.GetStreamSize();
	return size;
}
//----------------------------------------------------------------------------