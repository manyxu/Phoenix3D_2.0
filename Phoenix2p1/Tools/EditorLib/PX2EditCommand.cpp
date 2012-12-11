/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditCommand.cpp
*
*/

#include "PX2EditCommand.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditMap.hpp"
#include "PX2EditSystem.hpp"

using namespace PX2Editor;
using namespace PX2;

EditCommand::EditCommand ()
{
}
//----------------------------------------------------------------------------
EditCommand::~EditCommand ()
{

}
//----------------------------------------------------------------------------
void EditCommand::OnUnDo ()
{

}
//----------------------------------------------------------------------------
void EditCommand::OnReDo ()
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ActorTransCommand
//----------------------------------------------------------------------------
ActorTransCommand::ActorTransCommand ()
{
	int num = EditSystem::GetSingleton().GetSelection()->GetActorQuantity();
	mActors.resize(num);
	mPositions.resize(num);
	mRotations.resize(num);
	mScales.resize(num);

	for (int i=0; i<num; i++)
	{
		ActorPtr actor = EditSystem::GetSingleton().GetSelection()->GetActor(i);
		mActors[i] = actor;
		mPositions[i] = actor->GetPosition();
		mScales[i] = actor->GetScale();
		mRotations[i] = actor->GetRotation();
	}
}
//----------------------------------------------------------------------------
ActorTransCommand::~ActorTransCommand ()
{

}
//----------------------------------------------------------------------------
bool ActorTransCommand::operator== (const ActorTransCommand &command) const
{
	int numActors = (int)mActors.size();
	if (numActors != (int)command.mActors.size())
		return false;

	for (int i=0; i<numActors; i++)
	{
		if ((Actor*)mActors[i] != (Actor*)command.mActors[i])
			return false;

		if (mPositions[i] != command.mPositions[i])
			return false;

		if (mRotations[i] != command.mRotations[i])
			return false;

		if (mScales[i] != command.mScales[i])
			return false;
	}

	return true;
}
//----------------------------------------------------------------------------
void ActorTransCommand::OnUnDo ()
{
	for (int i=0; i<(int)mActors.size(); i++)
	{
		mActors[i]->SetPosition(mPositions[i]);
		mActors[i]->SetRotation(mRotations[i]);
		mActors[i]->SetScale(mScales[i]);
	}
}
//----------------------------------------------------------------------------
void ActorTransCommand::OnReDo ()
{
	for (int i=0; i<(int)mActors.size(); i++)
	{
		mActors[i]->SetPosition(mPositions[i]);
		mActors[i]->SetRotation(mRotations[i]);
		mActors[i]->SetScale(mScales[i]);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ActorAddDeleteCommand
//----------------------------------------------------------------------------
ActorAddDeleteCommand::ActorAddDeleteCommand (PX2::Actor *actor)
{
	mActor = actor;
}
//----------------------------------------------------------------------------
ActorAddDeleteCommand::~ActorAddDeleteCommand ()
{

}
//----------------------------------------------------------------------------
void ActorAddDeleteCommand::OnUnDo ()
{
	EditSystem::GetSingleton().GetEditMap()->RemoveActor(mActor);
}
//----------------------------------------------------------------------------
void ActorAddDeleteCommand::OnReDo ()
{
	EditSystem::GetSingleton().GetEditMap()->AddActor(mActor);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// EditCommandManager
//----------------------------------------------------------------------------
EditCommandManager::EditCommandManager ()
{

}
//----------------------------------------------------------------------------
EditCommandManager::~EditCommandManager ()
{

}
//----------------------------------------------------------------------------
void EditCommandManager::Reset ()
{
	mUnDoCommands.clear();
	mReDoCommands.clear();

	PX2::Event *event = EditorEventSpace::CreateEventX(
		EditorEventSpace::NoUnDo);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	event = EditorEventSpace::CreateEventX(
		EditorEventSpace::NoReDo);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditCommandManager::PushUnDo (EditCommandPtr command)
{
	mUnDoCommands.push_back(command);

	if ((int)mUnDoCommands.size() > 21)
		mUnDoCommands.pop_front();

	PX2::Event *event = EditorEventSpace::CreateEventX(
		EditorEventSpace::PushUnDo);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditCommandManager::UnDo ()
{
	if ((int)mUnDoCommands.size() > 0)
	{
		EditCommandPtr command = mUnDoCommands.back();
		if (command)
			command->OnUnDo();

		mReDoCommands.push_back(command);
		mUnDoCommands.pop_back();

		PX2::Event *event = EditorEventSpace::CreateEventX(
			EditorEventSpace::UnDo);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

		if ((int)mUnDoCommands.size() == 0)
		{
			PX2::Event *event = EditorEventSpace::CreateEventX(
				EditorEventSpace::NoUnDo);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);
		}
	}
}
//----------------------------------------------------------------------------
void EditCommandManager::ReDo ()
{
	if ((int)mReDoCommands.size() > 0)
	{
		EditCommandPtr command = mReDoCommands.back();
		if (command)
			command->OnReDo();

		mUnDoCommands.push_back(command);
		mReDoCommands.pop_back();

		PX2::Event *event = EditorEventSpace::CreateEventX(
			EditorEventSpace::ReDo);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

		if ((int)mReDoCommands.size() == 0)
		{
			PX2::Event *event = EditorEventSpace::CreateEventX(
				EditorEventSpace::NoReDo);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);
		}
	}
}
//----------------------------------------------------------------------------