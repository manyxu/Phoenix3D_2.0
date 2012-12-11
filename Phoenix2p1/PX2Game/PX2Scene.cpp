/*
*
* 文件名称	：	PX2Scene.cpp
*
*/

#include "PX2Scene.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2Interpolate.hpp"
using namespace PX2;
using namespace std;

PX2_IMPLEMENT_RTTI(PX2, Netable, Scene);
PX2_IMPLEMENT_STREAM(Scene);
PX2_IMPLEMENT_FACTORY(Scene);

//----------------------------------------------------------------------------
Scene::Scene ()
{
	mSceneNode = new0 Node();
	mDefaultCameraActor = new0 CameraActor();

	mDefaultLight = new0 Light(Light::LT_DIRECTIONAL);
	mDefaultLight->SetDirection(AVector(-1.0f, -1.0f, -1.0f));
	mDefaultLight->Ambient = Float4(0.2f, 0.2f, 0.2f, 1.0f);
	mDefaultLight->Diffuse = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	mDefaultLight->Specular = Float4(0.0f, 0.0f, 0.0f, 1.0f);

	GraphicsRoot::GetSingleton().ClearAllLights();
	GraphicsRoot::GetSingleton().AddLight(mDefaultLight);

	mAmbientBlend = 0.0f;
	mDefaultARActor = new0 AmbientRegionActor();
	mDefaultARActor->SetName("DefaultAmibient");
	mDefaultARActor->SetLight(mDefaultLight);
	AddActor(mDefaultARActor);
}
//----------------------------------------------------------------------------
Scene::~Scene ()
{
	// make out of event space
	for (int i=0; i<(int)mActors.size(); i++)
		mActors[i]->GoOutFromEventWorld();

	if (mDefaultCameraActor)
		mDefaultCameraActor->GoOutFromEventWorld();
}
//----------------------------------------------------------------------------
static AVector AnglesToDirection(float angle0, float angle1)
{
	return AVector(-Mathf::Cos(angle1)*Mathf::Cos(angle0), 
		-Mathf::Cos(angle1)*Mathf::Sin(angle0), -Mathf::Sin(angle1));
}
//-----------------------------------------------------------------------------
void Scene::Update (double appSeconds, double elapsedSeconds)
{
	// Ambient
	PX2::Light *light = mDefaultLight;

	AmbientRegionActor *curARActor = mTwoAmbientRigion[1];
	AmbientRegionActor *pastARActor = mTwoAmbientRigion[0];
	curARActor = mDefaultARActor;
	pastARActor = mDefaultARActor;

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

	// Scene
	mSceneNode->Update(appSeconds);
}
//----------------------------------------------------------------------------
void Scene::AddActor (Actor *actor)
{
	assertion(actor!=0, "actor must not be 0.");

	if (!actor)
		return;

	if (IsActorIn(actor))
		return;

	if (actor->IsExactly(TerrainActor::TYPE))
	{
		mTerrainActor = DynamicCast<TerrainActor>(actor);
	}

	Movable *movable = actor->GetMovable();
	if (movable)
	{
		mSceneNode->AttachChild(movable);
	}

	Movable *helpMoveable = actor->GetHelpMovable();
	if (helpMoveable)
	{
		mSceneNode->AttachChild(helpMoveable);
	}

	actor->SetScene(this);
	mActors.push_back(actor);
}
//----------------------------------------------------------------------------
bool Scene::RemoveActor (Actor *actor)
{
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

			Movable *helpMoveable = (*it)->GetHelpMovable();
			if (helpMoveable)
			{
				mSceneNode->DetachChild(helpMoveable);
			}

			actor->SetScene(0);
			mActors.erase(it);

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

	PX2_GET_OBJECT_BY_NAME(mDefaultCameraActor, name, found);

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

	PX2_GET_ALL_OBJECTS_BY_NAME(mDefaultCameraActor, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Scene::Scene (LoadConstructor value)
	:
Netable(value)
{
}
//----------------------------------------------------------------------------
void Scene::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Netable::Load(source);

	source.Read<int>(mSceneID);

	source.ReadPointer(mSceneNode);

	int numActors;
	source.Read(numActors);
	if (numActors > 0)
	{
		mActors.resize(numActors);
		source.ReadPointerVV(numActors, &mActors[0]);
	}

	source.ReadPointer(mDefaultCameraActor);

	PX2_END_DEBUG_STREAM_LOAD(Scene, source);
}
//----------------------------------------------------------------------------
void Scene::Link (InStream& source)
{
	Netable::Link(source);

	source.ResolveLink(mSceneNode);

	const int numActors = (int)mActors.size();
	for (int i=0; i<numActors; ++i)
	{
		if (mActors[i])
		{
			source.ResolveLink(mActors[i]);
			SetActor(i, mActors[i]);
		}
	}

	source.ResolveLink(mDefaultCameraActor);
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

		const int numActors = (int)mActors.size();
		for (int i = 0; i < numActors; ++i)
		{
			if (mActors[i])
			{
				target.Register(mActors[i]);
			}
		}

		target.Register(mDefaultCameraActor);

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

	target.WritePointer(mDefaultCameraActor);

	PX2_END_DEBUG_STREAM_SAVE(Scene, target);
}
//----------------------------------------------------------------------------
int Scene::GetStreamingSize () const
{
	int size = Netable::GetStreamingSize();
	size += sizeof(int);
	size += PX2_POINTERSIZE(mSceneNode);

	int numActors = (int)mActors.size();
	size += sizeof(numActors);
	size += numActors*PX2_POINTERSIZE(mActors[0]);
	size += PX2_POINTERSIZE(mDefaultCameraActor);

	return size;
}
//----------------------------------------------------------------------------
