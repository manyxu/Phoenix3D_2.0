/*
*
* 文件名称	：	PX2Controller.cpp
*
*/

#include "PX2Controller.hpp"
#include "PX2Controlledable.hpp"
#include "PX2Math.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, Controller);
PX2_IMPLEMENT_STREAM(Controller);
PX2_IMPLEMENT_ABSTRACT_FACTORY(Controller);

//----------------------------------------------------------------------------
Controller::Controller ()
:
Repeat(RT_CLAMP),
MinTime(0.0),
MaxTime(0.0),
Phase(0.0),
Frequency(1.0),
Active(true),
mObject(0),
mApplicationTime(-Mathd::MAX_REAL)
{
}
//----------------------------------------------------------------------------
Controller::~Controller ()
{
}
//----------------------------------------------------------------------------
bool Controller::Update (double applicationTime)
{
	if (Active)
	{
		mApplicationTime = applicationTime;
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Controller::SetObject (Controlledable* object)
{
	mObject = object;
}
//----------------------------------------------------------------------------
double Controller::GetControlTime (double applicationTime)
{
	double controlTime = Frequency*applicationTime + Phase;

	if (Repeat == RT_CLAMP)
	{
		// 将时间夹取到区间[min,max]
		if (controlTime < MinTime)
		{
			return MinTime;
		}
		if (controlTime > MaxTime)
		{
			return MaxTime;
		}
		return controlTime;
	}

	double timeRange = MaxTime - MinTime;
	if (timeRange > 0.0)
	{
		double multiples = (controlTime - MinTime)/timeRange;
		double integerTime = Mathd::Floor(multiples);
		double fractionTime = multiples - integerTime;
		if (Repeat == RT_WRAP)
		{
			return MinTime + fractionTime*timeRange;
		}

		// Repeat == PX2_RT_CYCLE
		if (((int)integerTime) & 1)
		{
			// 后退.
			return MaxTime - fractionTime*timeRange;
		}
		else
		{
			// 前进
			return MinTime + fractionTime*timeRange;
		}
	}

	// minimum和maximum相同，返回minimum
	return MinTime;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Controller::GetObjectByName (const std::string& name)
{
	// mObject 不用查询
	return Object::GetObjectByName(name);
}
//----------------------------------------------------------------------------
void Controller::GetAllObjectsByName (const std::string& name,
									  std::vector<Object*>& objects)
{
	// mObject 不用查询
	Object::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Controller::Controller (LoadConstructor value)
:
Object(value),
Repeat(RT_CLAMP),
MinTime(0.0),
MaxTime(0.0),
Phase(0.0),
Frequency(1.0),
Active(true),
mObject(0),
mApplicationTime(-Mathd::MAX_REAL)
{
}
//----------------------------------------------------------------------------
void Controller::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);
	Object::Load(source);

	source.ReadEnum(Repeat);
	source.Read(MinTime);
	source.Read(MaxTime);
	source.Read(Phase);
	source.Read(Frequency);
	source.ReadBool(Active);
	source.ReadPointer(mObject);

	mApplicationTime = -Mathd::MAX_REAL;

	PX2_END_DEBUG_STREAM_LOAD(Controller, source);
}
//----------------------------------------------------------------------------
void Controller::Link (InStream& source)
{
	Object::Link(source);

	source.ResolveLink(mObject);
}
//----------------------------------------------------------------------------
void Controller::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool Controller::Register (OutStream& target) const
{
	if (Object::Register(target))
	{
		target.Register(mObject);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Controller::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);

	target.WriteEnum(Repeat);
	target.Write(MinTime);
	target.Write(MaxTime);
	target.Write(Phase);
	target.Write(Frequency);
	target.WriteBool(Active);
	target.WritePointer(mObject);

	PX2_END_DEBUG_STREAM_SAVE(Controller, target);
}
//----------------------------------------------------------------------------
int Controller::GetStreamingSize () const
{
	int size = Object::GetStreamingSize();
	size += PX2_ENUMSIZE(Repeat);
	size += sizeof(MinTime);
	size += sizeof(MaxTime);
	size += sizeof(Phase);
	size += sizeof(Frequency);
	size += PX2_BOOLSIZE(Active);
	size += PX2_POINTERSIZE(mObject);
	return size;
}
//----------------------------------------------------------------------------