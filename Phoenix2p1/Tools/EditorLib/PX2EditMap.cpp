/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditMap.cpp
*
*/

#include "PX2EditMap.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditCommand.hpp"
#include "PX2EditSystem.hpp"
#include "PX2ActorSelection.hpp"
using namespace PX2Editor;
using namespace PX2;

//----------------------------------------------------------------------------
EditMap::EditMap ()
{
	mScene = new Scene();
	mScene->ComeInToEventWorld();
	
	mVertexFormat = VertexFormat::Create(3,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);
}
//----------------------------------------------------------------------------
EditMap::~EditMap ()
{
	if (mScene)
	{
		mScene->GoOutFromEventWorld();
	}
}
//----------------------------------------------------------------------------
void EditMap::NewScene ()
{
	mScene = new0 Scene();
	mScene->ComeInToEventWorld();

	mLoadedScenePath = "";
	EditCommandManager::GetSingleton().Reset();

	Event *event = EditorEventSpace::CreateEventX(
		EditorEventSpace::NewScene);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
bool EditMap::LoadScene (std::string pathname)
{
	InStream inStream;

	if (inStream.Load(pathname))
	{
		Object *object = inStream.GetObjectAt(0);

		Scene *scene = DynamicCast<Scene>(object);

		if (scene)
		{
			mLoadedScenePath = pathname;

			mScene = scene;

			mScene->ComeInToEventWorld();

			Event *event = EditorEventSpace::CreateEventX(
				EditorEventSpace::LoadedScene);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);

			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
bool EditMap::SaveScene (std::string pathname)
{
	if (SaveSceneAs(pathname))
	{
		mLoadedScenePath = pathname;
	}

	return false;
}
//----------------------------------------------------------------------------
bool EditMap::SaveSceneAs (std::string pathname)
{
	if (!mScene)
		return false;

	OutStream outStream;

	outStream.Insert(mScene);

	if (outStream.Save(pathname))
	{
		Event *event = EditorEventSpace::CreateEventX(
			EditorEventSpace::SavedScene);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EditMap::AddActor (PX2::Actor *actor)
{
	mScene->AddActor(actor);

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::AddActor);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditMap::RemoveActor (PX2::Actor *actor)
{
	mScene->RemoveActor(actor);

	Event *event = 0;
	event = EditorEventSpace::CreateEventX
		(EditorEventSpace::RemoveActor);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------