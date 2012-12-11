/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ActorSelection.cpp
*
*/

#include "PX2ActorSelection.hpp"
#include "PX2EditEventType.hpp"
using namespace PX2Editor;
using namespace PX2;

ActorSelection::ActorSelection ()
{
}
//----------------------------------------------------------------------------
ActorSelection::~ActorSelection ()
{
	Clear();
}
//----------------------------------------------------------------------------
void ActorSelection::AddActor (PX2::Actor *actor)
{
	assertion(actor!=0, "actor must not be 0.");

	if (IsActorIn(actor))
		return;

	mActors.push_back(actor);

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::AddSelectActor);
	event->SetData<Actor*>(actor);

	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void ActorSelection::RemoveActor (PX2::Actor *actor)
{
	std::vector<ActorPtr>::iterator it = mActors.begin();

	for (; it!=mActors.end(); it++)
	{
		if (actor == *it)
		{
			Event *event = 0;
			event = EditorEventSpace::CreateEventX(
				EditorEventSpace::RemoveSelectActor);
			event->SetData<Actor*>(actor);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);

			mActors.erase(it);

			return;
		}
	}
}
//----------------------------------------------------------------------------
PX2::Actor *ActorSelection::GetActor (int i)
{
	if (0<=i&&i<(int)mActors.size())
		return mActors[i];

	return 0;
}
//----------------------------------------------------------------------------
int ActorSelection::GetActorQuantity ()
{
	return (int)mActors.size();
}
//----------------------------------------------------------------------------
void ActorSelection::Clear ()
{
	for (int i=0; i<(int)mActors.size(); i++)
	{
		mActors[i] = 0;
	}

	mActors.clear();

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(
		EditorEventSpace::ClearSelectActor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
bool ActorSelection::IsActorIn (PX2::Actor *actor)
{
	for (int i=0; i<(int)mActors.size(); i++)
	{
		if (actor == mActors[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void ActorSelection::Translate (PX2::AVector vec)
{
	for (int i=0; i<(int)mActors.size(); i++)
	{
		APoint position = mActors[i]->GetPosition();
		position += vec;
		mActors[i]->SetPosition(position);
	}
}
//----------------------------------------------------------------------------
void ActorSelection::TranslateTo (PX2::APoint pos)
{
	for (int i=0; i<(int)mActors.size(); i++)
	{
		mActors[i]->SetPosition(pos);
	}
}
//----------------------------------------------------------------------------
void ActorSelection::AddRolate (PX2::AVector vec)
{
	for (int i=0; i<(int)mActors.size(); i++)
	{
		APoint rolate = mActors[i]->GetRotation();
		rolate += vec;
		mActors[i]->SetRotation(rolate);
	}
}
//----------------------------------------------------------------------------
void ActorSelection::AddScale (PX2::AVector vec)
{
	for (int i=0; i<(int)mActors.size(); i++)
	{
		APoint scale = mActors[i]->GetScale();
		scale += vec;

		mActors[i]->SetScale(scale);
	}
}
//----------------------------------------------------------------------------