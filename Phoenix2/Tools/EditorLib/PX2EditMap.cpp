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

EditMap::EditMap ()
{
	mScene = new Scene();
	mVertexFormat = VertexFormat::Create(3,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);

	mScene->ComeInToEventWorld();

	mDrawPhysics = false;
}
//----------------------------------------------------------------------------
EditMap::~EditMap ()
{
	mScene = 0;
	mVertexFormat =0;
}
//----------------------------------------------------------------------------
void EditMap::NewScene ()
{
	mScene = new Scene();
	mScene->ComeInToEventWorld();

	mLoadedScenePath = "";
	EditCommandManager::GetSingleton().Reset();

	Event *event = EditorEventSpace::CreateEvent(
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

			Event *event = EditorEventSpace::CreateEvent(
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
		Event *event = EditorEventSpace::CreateEvent(
			EditorEventSpace::SavedScene);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EditMap::NewAndAddTerrain (std::string name, int terrainSize, 
								int pageSize, float gridSpacing)
{
	RawTerrainActorPtr terrainActor = new0 RawTerrainActor();
	terrainActor->SetName(name);
	RawTerrainPtr rawTerrain = new0 RawTerrain();
	rawTerrain->SetName(name);
	rawTerrain->SetSize(pageSize);
	int quantity = terrainSize/(pageSize-1);
	rawTerrain->SetRowQuantity(quantity);
	rawTerrain->SetColQuantity(quantity);
	rawTerrain->SetSpacing(gridSpacing);
	rawTerrain->AllocateRawTerrainPages();
	terrainActor->SetTerrain(rawTerrain);
	terrainActor->ComeInToEventWorld();

	mTerrainActor = terrainActor;

	Event *event = EditorEventSpace::CreateEvent(
		EditorEventSpace::CreateTerrainAndAddToScene);
	event->SetData<RawTerrainActor*>(terrainActor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	mScene->AddActor(terrainActor);

	ActorAddDeleteCommand *command = new0 ActorAddDeleteCommand(terrainActor);
	EditCommandManager::GetSingleton().PushUnDo(command);
}
//----------------------------------------------------------------------------
void EditMap::NewAndAddCube (std::string name)
{
	StandardMesh stdMesh(mVertexFormat);
	TriMesh *mesh = stdMesh.Box(1, 1, 1);
	mesh->SetName(name);

	Texture2DMaterialPtr material = new0 Texture2DMaterial;
	PX2::Texture2D *tex = DynamicCast<PX2::Texture2D>(
		ResourceManager::GetSingleton().BlockLoad("ToolRes/DefaultTexture.dds"));
	mesh->SetMaterialInstance(material->CreateInstance(tex));

	ActorPtr actor = new0 Actor();
	actor->SetName(name);
	actor->SetMovable(mesh);
	actor->ComeInToEventWorld();

	Event *event = 0;
	event = EditorEventSpace::CreateEvent
		(EditorEventSpace::CreateModelActorAndAddToScene);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	AddActor(actor);

	ActorAddDeleteCommand *command = new0 ActorAddDeleteCommand(actor);
	EditCommandManager::GetSingleton().PushUnDo(command);
}
//----------------------------------------------------------------------------
void EditMap::NewAndAddSphere (std::string name)
{
	StandardMesh stdMesh(mVertexFormat);
	TriMesh *mesh = stdMesh.Sphere(12, 12, 4);
	mesh->SetName(name);
	VertexColor4MaterialPtr material = new0 VertexColor4Material;
	//	material->GetWireProperty(0, 0)->Enabled = true;
	//	material->GetCullProperty(0, 0)->Enabled = false;
	mesh->SetMaterialInstance(material->CreateInstance());

	ActorPtr actor = new0 Actor();
	actor->SetName(name);
	actor->SetMovable(mesh);
	actor->ComeInToEventWorld();

	Event *event = 0;
	event = EditorEventSpace::CreateEvent
		(EditorEventSpace::CreateModelActorAndAddToScene);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	AddActor(actor);

	ActorAddDeleteCommand *command = new0 ActorAddDeleteCommand(actor);
	EditCommandManager::GetSingleton().PushUnDo(command);
}
//----------------------------------------------------------------------------
void EditMap::NewAndAddPlane (std::string name)
{
	StandardMesh stdMesh(mVertexFormat);
	TriMesh *mesh = stdMesh.Rectangle(2, 2, 50, 50);
	mesh->SetName(name);
	VertexColor4MaterialPtr material = new0 VertexColor4Material;
	mesh->SetMaterialInstance(material->CreateInstance());

	ActorPtr actor = new0 Actor();
	actor->SetName(name);
	actor->SetMovable(mesh);
	actor->ComeInToEventWorld();

	Event *event = 0;
	event = EditorEventSpace::CreateEvent
		(EditorEventSpace::CreateModelActorAndAddToScene);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	AddActor(actor);

	ActorAddDeleteCommand *command = new0 ActorAddDeleteCommand(actor);
	EditCommandManager::GetSingleton().PushUnDo(command);
}
//----------------------------------------------------------------------------
void EditMap::NewAndAddLight (std::string name, PX2::APoint pos,
							  PX2::Light::Type type)
{
	Light *light = new0 Light(type);
	LightActor *actor = new0 LightActor(light);

	actor->SetName(name);
	actor->SetPosition(pos);
	actor->ComeInToEventWorld();

	Event *event = 0;
	event = EditorEventSpace::CreateEvent
		(EditorEventSpace::CreateLightActor);
	event->SetData<LightActor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	mScene->AddActor(actor);

	ActorAddDeleteCommand *command = new0 ActorAddDeleteCommand(actor);
	EditCommandManager::GetSingleton().PushUnDo(command);
}
//----------------------------------------------------------------------------
void EditMap::NewAndAddModel (PX2::APoint pos)
{
	PX2::Object *obj = EditSystem::GetSingleton().GetSelectedResource();
	PX2::Movable *mov = DynamicCast<PX2::Movable>(obj);
	if (mov)
	{
		PX2::Actor *actor = new0 Actor();
		actor->SetName(mov->GetName());
		actor->SetMovable(mov);
		actor->SetPosition(pos);
		actor->ComeInToEventWorld();

		Event *event = 0;
		event = EditorEventSpace::CreateEvent
			(EditorEventSpace::CreateModelActorAndAddToScene);
		event->SetData<Actor*>(actor);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);
		AddActor(actor);
	}
}
//----------------------------------------------------------------------------
void EditMap::NewAndAddSound (PX2::APoint pos)
{
	PX2::Object *objOrigin = EditSystem::GetSingleton().GetSelectedResource();
	PX2::Object *obj = objOrigin->Copy("");
	PX2::Soundable *sound = DynamicCast<PX2::Soundable>(obj);
	if (sound)
	{
		PX2::SoundActor *soundActor = new0 SoundActor(sound);
		soundActor->SetName(sound->GetName());
		soundActor->SetPosition(pos);
		soundActor->ComeInToEventWorld();

		Event *event = 0;
		event = EditorEventSpace::CreateEvent
			(EditorEventSpace::CreateSoundActor);
		event->SetData<SoundActor*>(soundActor);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);
		AddActor(soundActor);
	}
}
//----------------------------------------------------------------------------
void EditMap::FireACube (PX2::APoint pos, PX2::AVector dir, float strength)
{
	//StandardMesh stdMesh(mVertexFormat);
	//TriMesh *mesh = stdMesh.Box(0.2f, 0.2f, 0.2f);
	//mesh->SetName("NoName");

	//Texture2DMaterialPtr material = new0 Texture2DMaterial;
	//PX2::Texture2D *tex = DynamicCast<PX2::Texture2D>(
	//	ResourceManager::GetSingleton().BlockLoad("ToolRes/DefaultTexture.dds"));
	//mesh->SetMaterialInstance(material->CreateInstance(tex));

	//ActorPtr actor = new0 Actor();
	//actor->SetName("NoName");
	//actor->SetMovable(mesh);
	//actor->ComeInToEventWorld();

	//actor->SetPosition(pos);

	//Event *event = 0;
	//event = EditorEventSpace::CreateEvent
	//	(EditorEventSpace::CreateModelActorAndAddToScene);
	//event->SetData<Actor*>(actor);
	//EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	//AddActor(actor);

	//actor->SetPhysicsStatic(false);
	//actor->EnablePhysics(true);
	//AVector speedDir = dir * strength;
	//actor->GetRigidBody()->SetLinearVelocity(speedDir);
}
//----------------------------------------------------------------------------
void EditMap::AddActor (PX2::Actor *actor)
{
	mScene->AddActor(actor);

	Event *event = 0;
	event = EditorEventSpace::CreateEvent(EditorEventSpace::AddActor);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditMap::RemoveActor (PX2::Actor *actor)
{
	mScene->RemoveActor(actor);

	Event *event = 0;
	event = EditorEventSpace::CreateEvent
		(EditorEventSpace::RemoveActor);
	event->SetData<Actor*>(actor);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditMap::RemoveSelection ()
{
	int selectedNum = ActorSelection::GetSingleton().GetActorQuantity();
	for (int i=0; i<selectedNum; i++)
	{
		Actor *actor = ActorSelection::GetSingleton().GetActor(i);
		RemoveActor(actor);
	}

	ActorSelection::GetSingleton().Clear();
}
//----------------------------------------------------------------------------
RawTerrainActor *EditMap::GetTerrainActor ()
{
	return mTerrainActor;
}
//----------------------------------------------------------------------------
void EditMap::SetDrawPhysics (bool draw)
{
	mDrawPhysics = draw;

	GetScene()->GetDynamicWorld()->GetDebugDrawer()->SetDrawWireframe(
		mDrawPhysics);
}
//----------------------------------------------------------------------------
bool EditMap::IsPhysicsDraw ()
{
	return mDrawPhysics;
}
//----------------------------------------------------------------------------