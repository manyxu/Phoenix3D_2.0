/*
*
* 文件名称	：	PX2Scene.cpp
*
*/

#include "PX2Scene.hpp"
using namespace PX2;
using namespace std;
using namespace TdBt;

PX2_IMPLEMENT_RTTI(PX2, Netable, Scene);
PX2_IMPLEMENT_STREAM(Scene);
PX2_IMPLEMENT_FACTORY(Scene);

Scene::Scene ()
{
	mSceneNode = new0 Node();
	mIsFirstFrame = true;
	mLastFrameTime = 0.0;
	mPlayPhysicsSimulation = false;

	mDefaultLight = new0 Light(Light::LT_DIRECTIONAL);
	mDefaultLight->SetDirection(AVector(-1.0f, -1.0f, -1.0f));
	mDefaultLight->Ambient = Float4(0.2f, 0.2f, 0.2f, 1.0f);
	mDefaultLight->Diffuse = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	mDefaultLight->Specular = Float4(0.5f, 0.5f, 0.5f, 1.0f);

	GraphicsRoot::GetSingleton().ClearAllLights();
	GraphicsRoot::GetSingleton().AddLight(mDefaultLight);

	mAmbientBlend = 0.0f;
	mDefaultARActor = new0 AmbientRegionActor();
	mDefaultARActor->SetName("DefaultAmibient");
	mDefaultARActor->SetLight(mDefaultLight);
	AddActor(mDefaultARActor);

	InitPhysics(AxisAlignedBox3f(-1000, 1000, -1000, 1000, -1000, 1000), 
		Vector3f(0.0f, 0.0f, -9.8f));
}
//----------------------------------------------------------------------------
Scene::~Scene ()
{
	TermPhysics();

	// 必须在释放内存前，所有Actor离开消息世界
	for (int i=0; i<(int)mActors.size(); i++)
		mActors[i]->GoOutFromEventWorld();

	GoOutFromEventWorld();

	for (int i=0; i<(int)mActors.size(); i++)
		mActors[i] = 0;

	mSceneNode = 0;
}
//----------------------------------------------------------------------------
void Scene::InitPhysics (const PX2::AxisAlignedBox3f bounds, 
						 const PX2::Vector3f gravity)
{
	mBulletDynamicWorld = new0 DynamicWorld(bounds, gravity, true, true);

	mDebugDrawer = new DebugDrawer();
	mBulletDynamicWorld->SetDebugDrawer(mDebugDrawer);
}
//----------------------------------------------------------------------------
void Scene::TermPhysics ()
{
	mBulletDynamicWorld = 0;
	mDebugDrawer = 0;
}
//----------------------------------------------------------------------------
void Scene::EnablePhysicsSimulation (bool play)
{
	mPlayPhysicsSimulation = play;

	for (int i=0; i<(int)mActors.size(); i++)
	{
		Actor *actor = mActors[i];
		
		if (actor)
		{
			if (actor->IsDoPhysicsSimulateion())
				mActors[i]->EnablePhysics(play);
		}
	}
}
//----------------------------------------------------------------------------
static AVector AnglesToDirection(float angle0, float angle1)
{
	return AVector(-Mathf::Cos(angle1)*Mathf::Cos(angle0), 
		-Mathf::Cos(angle1)*Mathf::Sin(angle0), -Mathf::Sin(angle1));
}
//-----------------------------------------------------------------------------
void Scene::Update ()
{
	double second = GetTimeInSeconds();
	double elapseTime = 0.0;

	// camera
	Camera *camera = GraphicsRoot::GetSingleton().GetCamera();
	APoint camPos = camera->GetPosition();
	AVector dVector = camera->GetDVector();
	AVector uVector = camera->GetUVector();

	// Ambient
	PX2::Light *light = mDefaultLight;

	AmbientRegionActor *curARActor = mTwoAmbientRigion[1];
	AmbientRegionActor *pastARActor = mTwoAmbientRigion[0];
	curARActor = mDefaultARActor;
	pastARActor = mDefaultARActor;
	//if (!pastARActor)
	//{

	//}
	//else
	{
		mAmbientBlend = 1.0f;
		light->Ambient = Interpolate::LinearFloat4(
			pastARActor->mAmbientColor, curARActor->mAmbientColor, 
			mAmbientBlend);
		light->Diffuse = Interpolate::LinearFloat4(
			pastARActor->mDirLightDiffColor, curARActor->mDirLightDiffColor,
			mAmbientBlend);
		light->Specular = Interpolate::LinearFloat4(
			pastARActor->mDirLightSpecColor, curARActor->mDirLightSpecColor,
			mAmbientBlend);
		float horAngle = Interpolate::LinearFloat(
			pastARActor->mHorAngle, curARActor->mHorAngle,
			mAmbientBlend);
		float verAngle = Interpolate::LinearFloat(
			pastARActor->mVerAngle, curARActor->mVerAngle,
			mAmbientBlend);
		AVector dir = AnglesToDirection(Mathf::DEG_TO_RAD*horAngle, 
			Mathf::DEG_TO_RAD*verAngle);
		light->SetDirection(dir);
	}

	// Sound
	SoundSystem::GetSingleton().SetListener(&camPos, 0, &dVector,
		&uVector);

	// Scene
	mSceneNode->Update(second);

	if (mIsFirstFrame)
	{
		mIsFirstFrame = false;
		elapseTime = 0.0f;
	}
	else
	{
		elapseTime = second - mLastFrameTime;
		mLastFrameTime = second;
	}

	if (mBulletDynamicWorld && mPlayPhysicsSimulation)
		mBulletDynamicWorld->StepSimulation((float)elapseTime);

	if (mLODTerrainActor)
	{
		mLODTerrainActor->GetTerrain()->Simplify();
	}
}
//----------------------------------------------------------------------------
void Scene::AddActor (Actor *actor)
{
	assertion(actor!=0, "actor must not be 0.");

	if (!actor)
		return;

	if (IsActorIn(actor))
		return;

	if (actor->IsExactly(RawTerrainActor::TYPE))
	{
		mRawTerrainActor = (RawTerrainActor*)actor;
	}

	if (actor->IsExactly(LODTerrainActor::TYPE))
	{
		mLODTerrainActor = (LODTerrainActor*)actor;
	}

	if (actor->IsExactly(AmbientRegionActor::TYPE))
	{
		AmbientRegionActor *arActor = (AmbientRegionActor*)actor;
		mARActors.push_back(arActor);
	}

	Movable *movable = actor->GetMovable();
	if (movable)
	{
		mSceneNode->AttachChild(movable);
	}

	Movable *replacement = actor->GetHelpMovable();
	if (replacement)
	{
		mSceneNode->AttachChild(replacement);
	}

	actor->SetScene(this);
	mActors.push_back(actor);
}
//----------------------------------------------------------------------------
bool Scene::RemoveActor (Actor *actor)
{
	if (actor->IsExactly(AmbientRegionActor::TYPE))
	{
		std::vector<AmbientRigionActorPtr>::iterator it=mARActors.begin();
		for (; it!=mARActors.end(); it++)
		{
			if ((*it) == actor)
			{
				mARActors.erase(it);
				break;
			}
		}
	}

	std::vector<ActorPtr>::iterator it = mActors.begin();
	for (; it!=mActors.end(); it++)
	{
		if (*it == actor)
		{
			Movable *movable = (*it)->GetMovable();
			if (movable)
			{
				mSceneNode->DetachChild(movable);
			}

			Movable *replacement = (*it)->GetHelpMovable();
			if (replacement)
			{
				mSceneNode->DetachChild(replacement);
			}

			actor->SetScene(0);
			mActors.erase(it);

			if (actor == mRawTerrainActor)
				mRawTerrainActor = 0;

			if (actor == mLODTerrainActor)
				mLODTerrainActor = 0;

			return true;
		}		
	}

	return false;
}
//----------------------------------------------------------------------------
ActorPtr Scene::SetActor (int i, Actor* actor)
{
	if (actor)
	{
		assertion(!actor->GetScene(), "The actor already has a parent.\n");
	}

	const int numActor = (int)mActors.size();
	if (0 <= i && i < numActor)
	{
		// 将旧的孩子移除
		ActorPtr previousActor = mActors[i];
		if (previousActor)
		{
			previousActor->SetScene(0);
		}

		if (actor)
		{
			actor->SetScene(this);
		}

		mActors[i] = actor;
		return previousActor;
	}

	// 孩子超出范围，将其插入到孩子队列末尾
	if (actor)
	{
		actor->SetScene(this);
	}
	mActors.push_back(actor);
	return 0;
}
//----------------------------------------------------------------------------
bool Scene::IsActorIn (Actor *actor)
{
	for (int i=0; i<(int)mActors.size(); i++)
	{
		if (actor == mActors[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
int Scene::GetActorQuantity ()
{
	return (int)mActors.size();
}
//----------------------------------------------------------------------------
Actor *Scene::GetActor (int i)
{
	assertion(0<=i && i<(int)mActors.size(), "i should be in range.");

	if (0<=i && i<(int)mActors.size())
	{
		return mActors[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
Actor *Scene::GetActor (PX2::Movable *object)
{
	for (int i=0; i<(int)mActors.size(); i++)
	{
		if (object == mActors[i]->GetMovable())
			return mActors[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
int Scene::GetARActorNum ()
{
	return (int)mARActors.size();
}
//----------------------------------------------------------------------------
AmbientRegionActor *Scene::GetARActor (int i)
{
	assertion(i>=0&&i<(int)mARActors.size(), "i should be in right range.");

	if (i>=0&&i<(int)mARActors.size())
	{
		return mARActors[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
void Scene::DoUpdate ()
{
	Update();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Scene::GetObjectByName (const std::string& name)
{
	Object* found = Netable::GetObjectByName(name);

	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mSceneNode, name, found);

	const int numActors = (int)mActors.size();
	for (int i=0; i<numActors; ++i)
	{
		PX2_GET_OBJECT_BY_NAME(mActors[i], name, found);
	}

	return 0;
}
//----------------------------------------------------------------------------
void Scene::GetAllObjectsByName (const std::string& name,
								 std::vector<Object*>& objects)
{
	Netable::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mSceneNode, name, objects);

	const int numActors = (int)mActors.size();
	for (int i = 0; i < numActors; ++i)
	{
		PX2_GET_ALL_OBJECTS_BY_NAME(mActors[i], name, objects);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Scene::Scene (LoadConstructor value)
:
Netable(value),
mIsFirstFrame(true),
mLastFrameTime(0.0f),
mPlayPhysicsSimulation(false),
mDefaultLight(0)
{
	InitPhysics(AxisAlignedBox3f(0, 1000, 0, 1000, 0, 1000), 
		Vector3f(0.0f, 0.0f, -9.8f));
}
//----------------------------------------------------------------------------
void Scene::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Netable::Load(source);

	source.Read<int>(mSceneID);

	source.ReadPointer(mSceneNode);
	source.ReadPointer(mDefaultLight);
	source.ReadPointer(mLODTerrainActor);
	source.ReadPointer(mRawTerrainActor);

	source.ReadPointer(mDefaultARActor);
	int numARActors;
	source.Read(numARActors);
	if (numARActors > 0)
	{
		mARActors.resize(numARActors);
		source.ReadPointerVV(numARActors, &mARActors[0]);
	}

	int numActors;
	source.Read(numActors);
	if (numActors > 0)
	{
		mActors.resize(numActors);
		source.ReadPointerVV(numActors, &mActors[0]);
	}

	PX2_END_DEBUG_STREAM_LOAD(Scene, source);
}
//----------------------------------------------------------------------------
void Scene::Link (InStream& source)
{
	Netable::Link(source);

	source.ResolveLink(mSceneNode);
	source.ResolveLink(mDefaultLight);
	source.ResolveLink(mLODTerrainActor);
	source.ResolveLink(mRawTerrainActor);

	source.ResolveLink(mDefaultARActor);
	const int numARActors = (int)mARActors.size(); 
	for (int i=0; i<numARActors; ++i)
	{
		if (mARActors[i])
		{
			source.ResolveLink(mARActors[i]);
		}
	}

	const int numActors = (int)mActors.size();
	for (int i=0; i<numActors; ++i)
	{
		if (mActors[i])
		{
			source.ResolveLink(mActors[i]);
			SetActor(i, mActors[i]);
		}
	}
}
//----------------------------------------------------------------------------
void Scene::PostLink ()
{
	Netable::PostLink();
}
//----------------------------------------------------------------------------
bool Scene::Register (OutStream& target) const
{
	if (Netable::Register(target))
	{
		target.Register(mSceneNode);
		target.Register(mDefaultLight);
		target.Register(mLODTerrainActor);
		target.Register(mRawTerrainActor);

		target.Register(mDefaultARActor);
		const int numARActors = (int)mARActors.size();
		for (int i=0; i<numARActors; ++i)
		{
			if (mARActors[i])
			{
				target.Register(mARActors[i]);
			}
		}

		const int numActors = (int)mActors.size();
		for (int i = 0; i < numActors; ++i)
		{
			if (mActors[i])
			{
				target.Register(mActors[i]);
			}
		}

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Scene::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Netable::Save(target);

	target.Write<int>(mSceneID);

	target.WritePointer(mSceneNode);
	target.WritePointer(mDefaultLight);
	target.WritePointer(mLODTerrainActor);
	target.WritePointer(mRawTerrainActor);

	target.WritePointer(mDefaultARActor);
	const int numARActors = (int)mARActors.size();
	target.Write(numARActors);
	for (int i=0; i<numARActors; ++i)
	{
		target.WritePointer(mARActors[i]);
	}

	const int numActors = (int)mActors.size();
	target.Write(numActors);
	for (int i=0; i<numActors; ++i)
	{
		if (mActors[i])
		{
			target.WritePointer(mActors[i]);
		}
		else
		{
			target.WritePointer((Actor*)0);
		}
	}

	PX2_END_DEBUG_STREAM_SAVE(Scene, target);
}
//----------------------------------------------------------------------------
int Scene::GetStreamingSize () const
{
	int size = Netable::GetStreamingSize();
	size += sizeof(int);
	size += PX2_POINTERSIZE(mSceneNode);
	size += PX2_POINTERSIZE(mDefaultLight);
	size += PX2_POINTERSIZE(mLODTerrainActor);
	size += PX2_POINTERSIZE(mRawTerrainActor);

	size += PX2_POINTERSIZE(mDefaultARActor);
	int numARActors = (int)mARActors.size();
	size += sizeof(numARActors);
	size += numARActors*PX2_POINTERSIZE(mARActors[0]);

	int numActors = (int)mActors.size();
	size += sizeof(numActors);
	size += numActors*PX2_POINTERSIZE(mActors[0]);

	return size;
}
//----------------------------------------------------------------------------
