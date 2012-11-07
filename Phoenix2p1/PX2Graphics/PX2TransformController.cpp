/*
*
* 文件名称	：	PX2TransformController.cpp
*
*/

#include "PX2TransformController.hpp"
#include "PX2Movable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, TransformController);
PX2_IMPLEMENT_STREAM(TransformController);
PX2_IMPLEMENT_FACTORY(TransformController);
PX2_IMPLEMENT_DEFAULT_NAMES(Controller, TransformController);

//----------------------------------------------------------------------------
TransformController::TransformController (const Transform& localTransform)
:
mLocalTransform(localTransform)
{
}
//----------------------------------------------------------------------------
TransformController::~TransformController ()
{
}
//----------------------------------------------------------------------------
bool TransformController::Update (double applicationTime)
{
	if (!Controller::Update(applicationTime))
	{
		return false;
	}

	Movable* movable = StaticCast<Movable>(mObject);
	movable->LocalTransform = mLocalTransform;
	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
TransformController::TransformController (LoadConstructor value)
:
Controller(value)
{
}
//----------------------------------------------------------------------------
void TransformController::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);

	source.ReadAggregate(mLocalTransform);

	PX2_END_DEBUG_STREAM_LOAD(TransformController, source);
}
//----------------------------------------------------------------------------
void TransformController::Link (InStream& source)
{
	Controller::Link(source);
}
//----------------------------------------------------------------------------
void TransformController::PostLink ()
{
	Controller::PostLink();
}
//----------------------------------------------------------------------------
bool TransformController::Register (OutStream& target) const
{
	return Controller::Register(target);
}
//----------------------------------------------------------------------------
void TransformController::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);

	target.WriteAggregate(mLocalTransform);

	PX2_END_DEBUG_STREAM_SAVE(TransformController, target);
}
//----------------------------------------------------------------------------
int TransformController::GetStreamingSize () const
{
	int size = Controller::GetStreamingSize();
	size += mLocalTransform.GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------
