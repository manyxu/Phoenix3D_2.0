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
		VertexFormat::AU_NORMAL, VertexFormat::AT_FLOAT3, 0,
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
	mLoadedScenePath = "";
	EditSystem::GetSingleton().Reset();

	if (mScene)
		mScene->GoOutFromEventWorld();

	mScene = new0 Scene();
	mScene->ComeInToEventWorld();

	Event *event = EditorEventSpace::CreateEventX(
		EditorEventSpace::NewScene);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
bool EditMap::LoadScene (const char *pathname)
{
	InStream inStream;

	if (inStream.Load(pathname))
	{
		Object *object = inStream.GetObjectAt(0);

		Scene *scene = DynamicCast<Scene>(object);

		if (scene)
		{
			EditSystem::GetSingleton().Reset();

			mLoadedScenePath = pathname;

			if (mScene)
				mScene->GoOutFromEventWorld();

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
bool EditMap::SaveScene (const char *pathname)
{
	if (SaveSceneAs(pathname))
	{
		mLoadedScenePath = pathname;
	}

	return false;
}
//----------------------------------------------------------------------------
bool EditMap::SaveSceneAs (const char *pathname)
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
void EditMap::CreateBox (PX2::APoint pos)
{
	PX2::Texture2D *tex = DynamicCast<PX2::Texture2D>(
		ResourceManager::GetSingleton().BlockLoad("ToolRes/images/default.png"));
	if (!tex)
		return;

	StandardMesh stdMesh(mVertexFormat);
	TriMesh *mesh = stdMesh.Box(1, 1, 1);
	mesh->SetName("NoName");

	Texture2DMaterialPtr material = new0 Texture2DMaterial;
	mesh->SetMaterialInstance(material->CreateInstance(tex));

	ActorPtr actor = new0 Actor();
	actor->SetName("NoName");
	actor->SetMovable(mesh);
	actor->SetPosition(pos);
	actor->ComeInToEventWorld();

	AddActor(actor);

	Event *event = 0;
	event = EditorEventSpace::CreateEventX
		(EditorEventSpace::AddActor);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	ActorAddDeleteCommand *command = new0 ActorAddDeleteCommand(actor);
	EditSystem::GetSingleton().GetCM()->PushUnDo(command);
}
//----------------------------------------------------------------------------
void EditMap::CreateSphere (PX2::APoint pos)
{
	PX2::Texture2D *tex = DynamicCast<PX2::Texture2D>(
		ResourceManager::GetSingleton().BlockLoad("ToolRes/images/default.png"));
	if (!tex)
		return;

	StandardMesh stdMesh(mVertexFormat);
	TriMesh *mesh = stdMesh.Sphere(16, 16, 1);
	mesh->SetName("NoName");

	Texture2DMaterialPtr material = new0 Texture2DMaterial;
	mesh->SetMaterialInstance(material->CreateInstance(tex));

	ActorPtr actor = new0 Actor();
	actor->SetName("NoName");
	actor->SetMovable(mesh);
	actor->SetPosition(pos);
	actor->ComeInToEventWorld();

	AddActor(actor);

	Event *event = 0;
	event = EditorEventSpace::CreateEventX
		(EditorEventSpace::AddActor);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	ActorAddDeleteCommand *command = new0 ActorAddDeleteCommand(actor);
	EditSystem::GetSingleton().GetCM()->PushUnDo(command);
}
//----------------------------------------------------------------------------
void EditMap::AddModelActor (PX2::Movable *mov, PX2::APoint pos)
{
	if (!mov)
		return;

	PX2::Node *node = new0 PX2::Node();
	node->AttachChild(mov);
	node->SetName(mov->GetName()+"Par");

	PX2::Actor *actor = new0 Actor();
	actor->SetName(mov->GetName());
	actor->SetMovable(node);
	actor->SetPosition(pos);
	actor->ComeInToEventWorld();
	AddActor(actor);

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::AddActor);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditMap::CreateTerrain (std::string name, int terrainSize, int pageSize,
	float gridSpacing)
{
	TerrainActor *actor = new0 TerrainActor();
	actor->SetName(name);

	RawTerrain *rawTerrain = new0 RawTerrain();
	rawTerrain->SetName(name);
	rawTerrain->SetSize(pageSize);
	int quantity = terrainSize/(pageSize-1);
	rawTerrain->SetRowQuantity(quantity);
	rawTerrain->SetColQuantity(quantity);
	rawTerrain->SetSpacing(gridSpacing);
	rawTerrain->AllocateRawTerrainPages();

	actor->SetTerrain(rawTerrain);
	actor->ComeInToEventWorld();

	Event *event = EditorEventSpace::CreateEventX(
		EditorEventSpace::CreateTerrain);
	event->SetData<TerrainActor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	mScene->AddActor(actor);
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
void EditMap::CloneShare (PX2::Actor *actor, PX2::APoint pos)
{
	Actor *act = new0 Actor();
	*act = *actor;
	act->GetMovable()->SetParent(0);

	actor->SetPosition(pos);
	AddActor(act);
}
//----------------------------------------------------------------------------
void EditMap::CloneData (PX2::Actor *actor, PX2::APoint pos)
{
	Object *obj = actor->Copy("");
	Actor *newActor = DynamicCast<Actor>(obj);
	if (newActor)
	{
		newActor->SetPosition(pos);
		AddActor(newActor);
	}
}
//----------------------------------------------------------------------------