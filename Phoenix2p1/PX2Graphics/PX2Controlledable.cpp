/*
*
* 文件名称	：	PX2Controlledable.cpp
*
*/

#include "PX2Controlledable.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, Controlledable);
PX2_IMPLEMENT_STREAM(Controlledable);
PX2_IMPLEMENT_ABSTRACT_FACTORY(Controlledable);

//----------------------------------------------------------------------------
Controlledable::Controlledable ()
:
mNumControllers(0),
mCapacity(0),
mControllers(0)
{
}
//----------------------------------------------------------------------------
Controlledable::~Controlledable ()
{
	DetachAllControllers();
	delete1(mControllers);
}
//----------------------------------------------------------------------------
void Controlledable::AttachController (Controller* controller)
{
	if (IsDerived(Controller::TYPE))
	{
		assertion(false, "Controllers may not be controlled\n");
		return;
	}

	// 控制器必须存在
	if (!controller)
	{
		assertion(false, "Cannot attach a null controller\n");
		return;
	}

	// 检测控制器是否已经在队列中
	int i;
	for (i = 0; i < mNumControllers; ++i)
	{
		if (controller == mControllers[i])
		{
			return;
		}
	}

	// 将控制器绑定到对象
	controller->SetObject(this);

	// 控制器不再当前控制器队列，将其加入
	if (mNumControllers == mCapacity)
	{
		// 控制器数组慢了，增加其大小
		mCapacity += CO_GROW_BY;
		ControllerPtr* newControllers = new1<ControllerPtr>(mCapacity);
		for (i = 0; i < mNumControllers; ++i)
		{
			newControllers[i] = mControllers[i];
		}
		delete1(mControllers);
		mControllers = newControllers;
	}

	mControllers[mNumControllers++] = controller;
}
//----------------------------------------------------------------------------
void Controlledable::DetachController (Controller* controller)
{
	for (int i = 0; i < mNumControllers; ++i)
	{
		if (controller == mControllers[i])
		{
			// Unbind
			controller->SetObject(0);

			// 从数组中移除控制器
			for (int j = i + 1; j < mNumControllers; ++j, ++i)
			{
				mControllers[i] = mControllers[j];
			}
			mControllers[--mNumControllers] = 0;
			return;
		}
	}
}
//----------------------------------------------------------------------------
void Controlledable::DetachAllControllers ()
{
	for (int i = 0; i < mNumControllers; ++i)
	{
		// Unbind
		mControllers[i]->SetObject(0);
		mControllers[i] = 0;
	}
	mNumControllers = 0;
}
//----------------------------------------------------------------------------
bool Controlledable::UpdateControllers (double applicationTime)
{
	bool someoneUpdated = false;
	for (int i = 0; i < mNumControllers; ++i)
	{
		if (mControllers[i]->Update(applicationTime))
		{
			someoneUpdated = true;
		}
	}
	return someoneUpdated;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Controlledable::GetObjectByName (const std::string& name)
{
	Object* found = Object::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	for (int i = 0; i < mNumControllers; ++i)
	{
		PX2_GET_OBJECT_BY_NAME(mControllers[i], name, found);
	}

	return 0;
}
//----------------------------------------------------------------------------
void Controlledable::GetAllObjectsByName (const std::string& name,
											std::vector<Object*>& objects)
{
	Object::GetAllObjectsByName(name, objects);

	for (int i = 0; i < mNumControllers; ++i)
	{
		PX2_GET_ALL_OBJECTS_BY_NAME(mControllers[i], name, objects);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Controlledable::Controlledable (LoadConstructor value)
:
Object(value),
mNumControllers(0),
mCapacity(0),
mControllers(0)
{
}
//----------------------------------------------------------------------------
void Controlledable::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);

	source.ReadPointerRR(mNumControllers, mControllers);

	mCapacity = mNumControllers;

	PX2_END_DEBUG_STREAM_LOAD(Controlledable, source);
}
//----------------------------------------------------------------------------
void Controlledable::Link (InStream& source)
{
	Object::Link(source);

	source.ResolveLink(mNumControllers, mControllers);
}
//----------------------------------------------------------------------------
void Controlledable::PostLink ()
{
	Object::PostLink();
}
//----------------------------------------------------------------------------
bool Controlledable::Register (OutStream& target) const
{
	if (Object::Register(target))
	{
		target.Register(mNumControllers, mControllers);
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Controlledable::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);

	target.WritePointerW(mNumControllers, mControllers);

	PX2_END_DEBUG_STREAM_SAVE(Controlledable, target);
}
//----------------------------------------------------------------------------
int Controlledable::GetStreamingSize () const
{
	int size = Object::GetStreamingSize();
	size += sizeof(mNumControllers);
	size += mNumControllers*PX2_POINTERSIZE(mControllers[0]);
	return size;
}
//----------------------------------------------------------------------------