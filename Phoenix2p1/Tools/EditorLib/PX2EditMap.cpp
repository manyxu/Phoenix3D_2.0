/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditMap.cpp
*
*/

#include "PX2EditMap.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditCommand.hpp"
#include "PX2EditSystem.hpp"
#include "PX2ObjectSelection.hpp"
#include "PX2ParticleEmitter.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2EffectActor.hpp"
#include "PX2SkyActor.hpp"
#include "PX2Project.hpp"
#include "PX2UIManager.hpp"
#include "PX2StringHelp.hpp"
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

	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		delete0(proj);
		Project::Set(0);
	}
}
//----------------------------------------------------------------------------
void EditMap::NewProject (const char *pathname, const char *projName,
	int width, int height)
{
	EditSystem::GetSingleton().Reset();
	CloseProject();

	Project *proj = new0 Project();
	proj->SetName(projName);
	proj->SetWidth(width);
	proj->SetHeight(height);
	mProjectFilePath = pathname;
	proj->Save(pathname);

	Event *event = EditorEventSpace::CreateEventX(
		EditorEventSpace::NewProject);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
bool EditMap::LoadProject (const char *pathname)
{
	EditSystem::GetSingleton().Reset();

	Project *proj  = Project::GetSingletonPtr();
	if (proj)
	{
		delete0(proj);
		Project::Set(0);
	}

	proj = new0 Project();
	if (proj->Load(pathname))
	{
		std::string sceneFilename = proj->GetSceneFilename();

		if ("" != sceneFilename)
			LoadScene(sceneFilename.c_str());

		mProjectFilePath = pathname;

		Event *event = EditorEventSpace::CreateEventX(
			EditorEventSpace::LoadedProject);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

		return true;
	}
	else
	{
		delete0(proj);
		proj = 0;
	}

	return false;
}
//----------------------------------------------------------------------------
bool EditMap::SaveProject ()
{
	Project *proj  = Project::GetSingletonPtr();
	if (proj)
	{
		 if (proj->Save(mProjectFilePath))
		 {
			 Event *event = EditorEventSpace::CreateEventX(				 
				 EditorEventSpace::SavedProject);
			 EventWorld::GetSingleton().BroadcastingLocalEvent(event);

			 return true;
		 }
	}

	return false;
}
//----------------------------------------------------------------------------
bool EditMap::SaveProjectAs (const char *pathname)
{
	Project *proj  = Project::GetSingletonPtr();
	if (proj)
	{
		if (proj->Save(pathname))
		{
			Event *event = EditorEventSpace::CreateEventX(
				EditorEventSpace::SavedProject);
			EventWorld::GetSingleton().BroadcastingLocalEvent(event);
			
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void EditMap::CloseProject ()
{
	EditSystem::GetSingleton().Reset();

	CloseScene();

	mProjectFilePath = "";

	Project *proj  = Project::GetSingletonPtr();
	if (proj)
	{
		delete0(proj);
		Project::Set(0);

		Event *event = EditorEventSpace::CreateEventX(
			EditorEventSpace::ClosedProject);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);
	}
}
//----------------------------------------------------------------------------
void EditMap::NewScene ()
{
	EditSystem::GetSingleton().Reset();

	if (mScene)
		mScene->GoOutFromEventWorld();

	mScene = new0 Scene();
	mScene->ComeInToEventWorld();
	Project::GetSingleton().SetSceneFilename("");
	Project::GetSingleton().SetScene(mScene);

	Event *event = EditorEventSpace::CreateEventX(
		EditorEventSpace::NewScene);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
bool EditMap::LoadScene (const char *pathname)
{
	EditSystem::GetSingleton().Reset();

	InStream inStream;

	if (inStream.Load(pathname))
	{
		Object *object = inStream.GetObjectAt(0);

		Scene *scene = DynamicCast<Scene>(object);

		if (scene)
		{
			EditSystem::GetSingleton().Reset();

			if (mScene)
				mScene->GoOutFromEventWorld();

			mScene = scene;
			mScene->ComeInToEventWorld();
			Project::GetSingleton().SetScene(mScene);

			Project::GetSingleton().SetSceneFilename(pathname);

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
		Project::GetSingleton().SetSceneFilename(pathname);
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
void EditMap::CloseScene ()
{
	EditSystem::GetSingleton().Reset();

	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		proj->SetScene(0);
		proj->SetSceneFilename("");

		Event *event = EditorEventSpace::CreateEventX(
			EditorEventSpace::CloseScene);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);
	}
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

	//Texture2DMaterialPtr material = new0 Texture2DMaterial;
	//mesh->SetMaterialInstance(material->CreateInstance(tex));

	StandardESMaterial_DefaultPtr mtl = new0 StandardESMaterial_Default();
	mesh->SetMaterialInstance(mtl->CreateInstance(tex, 0, 0));

	ActorPtr actor = new0 Actor();
	actor->SetName("NoName");
	actor->SetMovable(mesh);
	actor->SetPosition(pos);
	actor->ComeInToEventWorld();

	AddActor(actor);

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

	//Texture2DMaterialPtr material = new0 Texture2DMaterial;
	//mesh->SetMaterialInstance(material->CreateInstance(tex));

	StandardESMaterial_DefaultPtr mtl = new0 StandardESMaterial_Default();
	mesh->SetMaterialInstance(mtl->CreateInstance(tex, 0 ,0));

	ActorPtr actor = new0 Actor();
	actor->SetName("NoName");
	actor->SetMovable(mesh);
	actor->SetPosition(pos);
	actor->ComeInToEventWorld();

	AddActor(actor);

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
	actor->SetName("ModelActor");
	actor->SetMovable(node);
	actor->SetPosition(pos);
	actor->ComeInToEventWorld();

	AddActor(actor);
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

	actor->SetRawTerrain(rawTerrain);
	actor->ComeInToEventWorld();

	AddActor(actor);
}
//----------------------------------------------------------------------------
void EditMap::CreateSky ()
{
	SkySphere *sky = new0 SkySphere();
	SkyActor *actor = new0 SkyActor(sky);

	AddActor(actor);
}
//----------------------------------------------------------------------------
void EditMap::CreateUIFrame (PX2::Node *parent, PX2::Float2 posScreen)
{
	APoint localPos = APoint(posScreen[0], 0.0f, posScreen[1]);

	if (parent)
	{
		localPos = parent->WorldTransform.Inverse() * localPos;
	}
	
	UIFrame *frame = UIManager::GetSingleton().CreateUIFrame(localPos);

	if (parent)
	{
		parent->AttachChild(frame);
	}

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::AddUI);
	event->SetData<Object*>(frame);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditMap::CreateUIPicBox (PX2::Node *parent, PX2::Float2 posScreen,
	const std::string &filename)
{
	APoint localPos = APoint(posScreen[0], 0.0f, posScreen[1]);

	if (parent)
	{
		localPos = parent->WorldTransform.Inverse() * localPos;
	}

	UIPicBox *box = UIManager::GetSingleton().CreateUIPicBox(localPos,
		filename);

	if (parent)
	{
		parent->AttachChild(box);
	}

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::AddUI);
	event->SetData<Object*>(box);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditMap::CreateUIAnimPicBox(PX2::Node *parent, PX2::Float2 posScreen,
	const std::string &texPack)
{
	APoint localPos = APoint(posScreen[0], 0.0f, posScreen[1]);

	if (parent)
	{
		localPos = parent->WorldTransform.Inverse() * localPos;
	}

	UIAnimPicBox *animPicBox = UIManager::GetSingleton().CreateUIAnimPicBox(
		localPos, texPack);

	if (parent)
	{
		parent->AttachChild(animPicBox);
	}

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::AddUI);
	event->SetData<Object*>(animPicBox);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditMap::CreateUIStaticText (PX2::Node *parent, PX2::Float2 posScreen,
	const std::string &filename)
{
	APoint localPos = APoint(posScreen[0], 0.0f, posScreen[1]);

	if (parent)
	{
		localPos = parent->WorldTransform.Inverse() * localPos;
	}

	UIStaticText *text = UIManager::GetSingleton().CreateUIStaticText(
		localPos);

	if (parent)
	{
		parent->AttachChild(text);
	}

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::AddUI);
	event->SetData<Object*>(text);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditMap::CreateUIButton (PX2::Node *parent, PX2::Float2 posScreen)
{
	APoint localPos = APoint(posScreen[0], 0.0f, posScreen[1]);

	if (parent)
	{
		localPos = parent->WorldTransform.Inverse() * localPos;
	}

	UIButton *bnt = UIManager::GetSingleton().CreateUIButton(localPos);

	if (parent)
	{
		parent->AttachChild(bnt);
	}

	Event *event = 0;
	event = EditorEventSpace::CreateEventX(EditorEventSpace::AddUI);
	event->SetData<Object*>(bnt);
	EventWorld::GetSingleton().BroadcastingLocalEvent(event);
}
//----------------------------------------------------------------------------
void EditMap::CreateEffect(PX2::APoint pos)
{
	EffectNode *node = new0 EffectNode();
	EffectActor *actor = new0 EffectActor(node);
	actor->SetPosition(pos);

	AddActor(actor);
}
//----------------------------------------------------------------------------
PX2::Movable *EditMap::CreateParticlesToEffect (PX2::Node *node)
{
	ParticleEmitter *emitter = new0 ParticleEmitter();
	emitter->SetName("NewParticleEmitter");
	node->AttachChild(emitter);
	return emitter;
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
bool EditMap::RemoveUI (PX2::Object *obj)
{
	if (!Project::GetSingletonPtr())
		return false;

	if (obj == Project::GetSingleton().GetUI())
		return false;

	Movable *mov = DynamicCast<Movable>(obj);
	if (!mov)
		return false;

	UIFrame *frame = DynamicCast<UIFrame>(obj);
	UIPicBox *pixBox = DynamicCast<UIPicBox>(obj);
	UIStaticText *staticText = DynamicCast<UIStaticText>(obj);

	Node *parent = DynamicCast<Node>(mov->GetParent());
	if (parent)
	{
		parent->DetachChild(mov);

		Event *event = 0;
		event = EditorEventSpace::CreateEventX
			(EditorEventSpace::RemoveUI);
		event->SetData<Object*>(obj);
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

		return true;
	}

	return false;
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