/*
*
* 文件名称	：	PX2LodTerrainActor.cpp
*
*/

#include "PX2LodTerrainActor.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Actor, LODTerrainActor);
PX2_IMPLEMENT_STREAM(LODTerrainActor);
PX2_IMPLEMENT_ABSTRACT_FACTORY(LODTerrainActor);

LODTerrainActor::LODTerrainActor ()
{
	mUsingLOD = false;
	mTerrain = 0;
}
//----------------------------------------------------------------------------
LODTerrainActor::~LODTerrainActor ()
{
	mTerrain = 0;
}
//----------------------------------------------------------------------------
void LODTerrainActor::SetTerrain (LODTerrain *terrain)
{
	mTerrain = terrain;
	SetMovable(mTerrain);
}
//----------------------------------------------------------------------------
void LODTerrainActor::UseLOD (bool use)
{
	mUsingLOD = use;
	if (mTerrain)
		mTerrain->UseLOD(use);
}
//----------------------------------------------------------------------------
void LODTerrainActor::SetPixelTolerance (float tolerance)
{
	if (mTerrain)
		mTerrain->SetPixelTolerance(tolerance);
}
//----------------------------------------------------------------------------
float LODTerrainActor::GetPixelTolerance ()
{
	if (mTerrain)
		return mTerrain->GetPixelTolerance();

	return 0.0f;
}
//----------------------------------------------------------------------------
void LODTerrainActor::DoEnter ()
{

}
//----------------------------------------------------------------------------
void LODTerrainActor::DoUpdate ()
{
	if (mTerrain)
		mTerrain->Simplify();
}
//----------------------------------------------------------------------------
void LODTerrainActor::DoExecute (Event *event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
void LODTerrainActor::DoLeave ()
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* LODTerrainActor::GetObjectByName (const std::string& name)
{
	Object* found = Actor::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void LODTerrainActor::GetAllObjectsByName (const std::string& name,
								 std::vector<Object*>& objects)
{
	Actor::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
LODTerrainActor::LODTerrainActor (LoadConstructor value)
:
Actor(value)
{
}
//----------------------------------------------------------------------------
void LODTerrainActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Actor::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(LODTerrainActor, source);
}
//----------------------------------------------------------------------------
void LODTerrainActor::Link (InStream& source)
{
	Actor::Link(source);
}
//----------------------------------------------------------------------------
void LODTerrainActor::PostLink ()
{
	Actor::PostLink();
}
//----------------------------------------------------------------------------
bool LODTerrainActor::Register (OutStream& target) const
{
	if (Actor::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void LODTerrainActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Actor::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(LODTerrainActor, target);
}
//----------------------------------------------------------------------------
int LODTerrainActor::GetStreamingSize () const
{
	int size = Actor::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------