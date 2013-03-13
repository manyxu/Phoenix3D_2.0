/*
*
* 文件名称	：	PX2InterpCurveTransCtrl.cpp
*
*/

#include "PX2InterpCurveTransCtrl.hpp"
#include "PX2Movable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, TransformController, InterpCurveTransController);
PX2_IMPLEMENT_STREAM(InterpCurveTransController);
PX2_IMPLEMENT_FACTORY(InterpCurveTransController);
PX2_IMPLEMENT_DEFAULT_NAMES(TransformController, InterpCurveTransController);

//----------------------------------------------------------------------------
InterpCurveTransController::InterpCurveTransController (
	const Transform& localTransform)
	:
TransformController(localTransform)
{
}
//----------------------------------------------------------------------------
InterpCurveTransController::~InterpCurveTransController ()
{
}
//----------------------------------------------------------------------------
bool InterpCurveTransController::Update (double applicationTime)
{
	if (!Controller::Update(applicationTime))
	{
		return false;
	}

	float ctrlTime = (float)GetControlTime(applicationTime);

	Float3 scale = mScales.Eval(ctrlTime, Float3::ZERO);
	Float3 rotate = mRotates.Eval(ctrlTime, Float3::ZERO);
	Float3 trans = mTrans.Eval(ctrlTime, Float3::ZERO);

	mLocalTransform.SetScale(scale);
	mLocalTransform.SetRotate(Matrix3f().MakeEulerXYZ(rotate[0], rotate[1],
		rotate[2]));
	mLocalTransform.SetTranslate(trans);

	Movable* movable = StaticCast<Movable>(mObject);
	movable->LocalTransform = mLocalTransform;
	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
InterpCurveTransController::InterpCurveTransController (LoadConstructor value)
	:
TransformController(value)
{
}
//----------------------------------------------------------------------------
void InterpCurveTransController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TransformController::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(InterpCurveTransController, source);
}
//----------------------------------------------------------------------------
void InterpCurveTransController::Link (InStream& source)
{
	TransformController::Link(source);
}
//----------------------------------------------------------------------------
void InterpCurveTransController::PostLink ()
{
	TransformController::PostLink();
}
//----------------------------------------------------------------------------
bool InterpCurveTransController::Register (OutStream& target) const
{
	return TransformController::Register(target);
}
//----------------------------------------------------------------------------
void InterpCurveTransController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TransformController::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(InterpCurveTransController, target);
}
//----------------------------------------------------------------------------
int InterpCurveTransController::GetStreamingSize () const
{
	int size = TransformController::GetStreamingSize();

	return size;
}
//----------------------------------------------------------------------------