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
		mMovable->WorldTransform.SetTranslate(position);
	}

	if (mHelpMovable)
	{
		mHelpMovable->WorldTransform.SetTranslate(position);
	}
}
//----------------------------------------------------------------------------
void Actor::SetScale (APoint &scale)
{
	mScale = scale;

	if (mMovable)
	{
		mMovable->WorldTransform.SetScale(scale);
	}
}
//----------------------------------------------------------------------------
void Actor::SetRotation (APoint &rolate)
{
	mRotation = rolate;

	if (mMovable)
	{
		mMovable->WorldTransform.SetRotate(Matrix3f().MakeEulerXYZ(
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
	mMovable = movable;
	mMovable->WorldTransformIsCurrent = true;

	mMovable->WorldTransform.SetScale(mScale);
	mMovable->WorldTransform.SetRotate(Matrix3f().MakeEulerXYZ(
		mRotation.X(), mRotation.Y(), mRotation.Z()));
	mMovable->WorldTransform.SetTranslate(mPosition);

	if (!mVisible)
		mMovable->Culling = Movable::CULL_ALWAYS;
	else
		mMovable->Culling = Movable::CULL_DYNAMIC;
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

	mHelpMovable->WorldTransformIsCurrent = true;
	mHelpMovable->WorldTransform.SetTranslate(mPosition);

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
	mScale(APoint(1.0f, 1.0f, 1.0f))
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

	PX2_END_DEBUG_STREAM_LOAD(Actor, source);
}
//----------------------------------------------------------------------------
void Actor::Link (InStream& source)
{
	Netable::Link(source);

	source.ResolveLink(mMovable);
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

	return size;
}
//----------------------------------------------------------------------------