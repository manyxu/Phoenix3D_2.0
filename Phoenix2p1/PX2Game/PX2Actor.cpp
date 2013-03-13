/*
*
* 文件名称	：	PX2Actor.cpp
*
*/

#include "PX2Actor.hpp"
#include "PX2Scene.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Netable, Actor);
PX2_IMPLEMENT_STREAM(Actor);
PX2_IMPLEMENT_FACTORY(Actor);

//----------------------------------------------------------------------------
Actor::Actor ()
{
	mScene = 0;
	mVisible = true;
	mTransAlpha = 1.0f;
	mMovable = 0;
	mHelpMovable = 0;
	mScale = APoint(1.0f, 1.0f, 1.0f);
	mShowHelpMovable = false;

	SetName("NoName");
}
//----------------------------------------------------------------------------
Actor::~Actor ()
{
}
//----------------------------------------------------------------------------
void Actor::SetPosition (APoint &position)
{
	mPosition = position;

	if (mMovable)
	{
		mMovable->LocalTransform.SetTranslate(position);
	}

	if (mHelpMovable)
	{
		mHelpMovable->LocalTransform.SetTranslate(position);
	}
}
//----------------------------------------------------------------------------
void Actor::SetScale (APoint &scale)
{
	mScale = scale;

	if (0.0f==mScale.X() || 0.0f==mScale.Y() || 0.0f==mScale.Z())
	{
		mScale.X() = 0.0001f;
	}

	if (mMovable)
	{
		mMovable->LocalTransform.SetScale(scale);
	}
}
//----------------------------------------------------------------------------
void Actor::SetRotation (APoint &rolate)
{
	mRotation = rolate;

	if (mMovable)
	{
		mMovable->LocalTransform.SetRotate(Matrix3f().MakeEulerXYZ(
			rolate.X(), rolate.Y(), rolate.Z()));
	}
}
//----------------------------------------------------------------------------
void Actor::SetVisible (bool visible)
{
	mVisible = visible;

	if (mMovable)
	{
		if (!mVisible)
			mMovable->Culling = Movable::CULL_ALWAYS;
		else
			mMovable->Culling = Movable::CULL_DYNAMIC;
	}
}
//----------------------------------------------------------------------------
void Actor::SetTransparent (float alpha)
{
	mTransAlpha = alpha;
}
//----------------------------------------------------------------------------
void Actor::SetMovable (Movable *movable)
{
	if (mScene && mMovable)
	{
		mScene->GetSceneNode()->DetachChild(mMovable);
	}

	mMovable = movable;

	mMovable->LocalTransform.SetScale(mScale);
	mMovable->LocalTransform.SetRotate(Matrix3f().MakeEulerXYZ(
		mRotation.X(), mRotation.Y(), mRotation.Z()));
	mMovable->LocalTransform.SetTranslate(mPosition);

	if (!mVisible)
		mMovable->Culling = Movable::CULL_ALWAYS;
	else
		mMovable->Culling = Movable::CULL_DYNAMIC;

	if (mScene && mMovable)
	{
		mScene->GetSceneNode()->AttachChild(mMovable);
	}
}
//----------------------------------------------------------------------------
void Actor::ShowHelpMovable (bool show)
{
	mShowHelpMovable = show;

	if (mHelpMovable)
	{
		if (mShowHelpMovable)
		{
			mHelpMovable->Culling = Movable::CULL_DYNAMIC;
		}
		else
		{
			mHelpMovable->Culling = Movable::CULL_ALWAYS;
		}
	}
}
//----------------------------------------------------------------------------
void Actor::SetHelpMovable (Movable *movable)
{
	mHelpMovable = movable;

	mHelpMovable->LocalTransform.SetTranslate(mPosition);

	if (!mVisible)
		mHelpMovable->Culling = Movable::CULL_ALWAYS;
	else
		mHelpMovable->Culling = Movable::CULL_DYNAMIC;
}
//----------------------------------------------------------------------------
void Actor::SetScene (Scene *scene)
{
	mScene = scene;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Actor::GetObjectByName (const std::string& name)
{
	Object* found = Netable::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void Actor::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Netable::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Actor::Actor (LoadConstructor value)
	:
Netable(value),
	mScene(0),
	mVisible(true),
	mTransAlpha(1.0f),
	mMovable(0),
	mScale(APoint(1.0f, 1.0f, 1.0f)),
	mShowHelpMovable(false)
{
}
//----------------------------------------------------------------------------
void Actor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Netable::Load(source);

	// mScene不被保存，它会在Scene::Link中调用Scene::AddChild被设置。
	source.ReadAggregate(mScale);
	source.ReadAggregate(mRotation);
	source.ReadAggregate(mPosition);
	source.ReadBool(mVisible);
	source.Read(mTransAlpha);
	source.ReadPointer(mMovable);
	source.ReadPointer(mHelpMovable);
	source.ReadBool(mShowHelpMovable);

	PX2_END_DEBUG_STREAM_LOAD(Actor, source);
}
//----------------------------------------------------------------------------
void Actor::Link (InStream& source)
{
	Netable::Link(source);

	source.ResolveLink(mMovable);
	source.ResolveLink(mHelpMovable);
}
//----------------------------------------------------------------------------
void Actor::PostLink ()
{
	Netable::PostLink();
}
//----------------------------------------------------------------------------
bool Actor::Register (OutStream& target) const
{
	if (Netable::Register(target))
	{
		target.Register(mMovable);
		target.Register(mHelpMovable);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Actor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Netable::Save(target);

	target.WriteAggregate(mScale);
	target.WriteAggregate(mRotation);
	target.WriteAggregate(mPosition);
	target.WriteBool(mVisible);
	target.Write(mTransAlpha);
	target.WritePointer(mMovable);
	target.WritePointer(mHelpMovable);
	target.WriteBool(mShowHelpMovable);

	PX2_END_DEBUG_STREAM_SAVE(Actor, target);
}
//----------------------------------------------------------------------------
int Actor::GetStreamingSize () const
{
	int size = Netable::GetStreamingSize();
	size += sizeof(mScale);
	size += sizeof(mRotation);
	size += sizeof(mPosition);
	size += PX2_BOOLSIZE(mVisible);
	size += sizeof(mTransAlpha);
	size += PX2_POINTERSIZE(mMovable);
	size += PX2_POINTERSIZE(mHelpMovable);
	size += PX2_BOOLSIZE(mShowHelpMovable);

	return size;
}
//----------------------------------------------------------------------------