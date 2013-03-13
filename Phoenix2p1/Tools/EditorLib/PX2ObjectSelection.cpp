/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorSelection.cpp
*
*/

#include "PX2ObjectSelection.hpp"
#include "PX2EditEventType.hpp"
using namespace PX2Editor;
using namespace PX2;

ObjectSelection::ObjectSelection ()
{
}
//----------------------------------------------------------------------------
ObjectSelection::~ObjectSelection ()
{
	Clear();
}
//----------------------------------------------------------------------------
void ObjectSelection::AddObject(PX2::Object *obj)
{
	assertion(obj!=0, "obj must not be 0.");

	if (IsObjectIn(obj))
		return;

	mObjects.push_back(obj);

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::AddSelectObject);
	event->SetData<Object*>(obj);

	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void ObjectSelection::RemoveObject(PX2::Object *obj)
{
	std::vector<ObjectPtr>::iterator it = mObjects.begin();

	for (; it!=mObjects.end(); it++)
	{
		if (obj == *it)
		{
			Event *event = 0;
			event = EditorEventSpace::CreateEventX(
				EditorEventSpace::RemoveSelectObject);
			event->SetData<Object*>(obj);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);

			mObjects.erase(it);

			return;
		}
	}
}
//----------------------------------------------------------------------------
PX2::Object *ObjectSelection::GetObjectAt(int i)
{
	if (0<=i&&i<(int)mObjects.size())
		return mObjects[i];

	return 0;
}
//----------------------------------------------------------------------------
int ObjectSelection::GetNumObjects ()
{
	return (int)mObjects.size();
}
//----------------------------------------------------------------------------
void ObjectSelection::Clear ()
{
	for (int i=0; i<(int)mObjects.size(); i++)
	{
		mObjects[i] = 0;
	}

	mObjects.clear();

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(
		EditorEventSpace::ClearSelectObject);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
bool ObjectSelection::IsObjectIn (PX2::Object *obj)
{
	for (int i=0; i<(int)mObjects.size(); i++)
	{
		if (obj == mObjects[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void ObjectSelection::Translate (PX2::AVector vec)
{
	for (int i=0; i<(int)mObjects.size(); i++)
	{
		Actor *actor = DynamicCast<Actor>(mObjects[i]);
		if (actor)
		{
			APoint position = actor->GetPosition();
			position += vec;
			actor->SetPosition(position);
		}
	}
}
//----------------------------------------------------------------------------
void ObjectSelection::TranslateTo (PX2::APoint pos)
{
	for (int i=0; i<(int)mObjects.size(); i++)
	{
		Actor *actor = DynamicCast<Actor>(mObjects[i]);
		if (actor)
		{
			actor->SetPosition(pos);
		}
	}
}
//----------------------------------------------------------------------------
void ObjectSelection::AddRolate (PX2::AVector vec)
{
	for (int i=0; i<(int)mObjects.size(); i++)
	{
		Actor *actor = DynamicCast<Actor>(mObjects[i]);
		if (actor)
		{
			APoint rolate = actor->GetRotation();
			rolate += vec;
			actor->SetRotation(rolate);
		}
	}
}
//----------------------------------------------------------------------------
void ObjectSelection::AddScale (PX2::AVector vec)
{
	for (int i=0; i<(int)mObjects.size(); i++)
	{
		Actor *actor = DynamicCast<Actor>(mObjects[i]);
		if (actor)
		{
			APoint scale = actor->GetScale();
			scale += vec;

			actor->SetScale(scale);
		}
	}
}
//----------------------------------------------------------------------------