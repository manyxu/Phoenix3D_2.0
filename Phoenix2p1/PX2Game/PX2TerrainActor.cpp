/*
*
* 文件名称	：	PX2RawTerrainActor.cpp
*
*/

#include "PX2TerrainActor.hpp"
#include "PX2Scene.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Actor, TerrainActor);
PX2_IMPLEMENT_STREAM(TerrainActor);
PX2_IMPLEMENT_FACTORY(TerrainActor);

TerrainActor::TerrainActor ()
{
}
//----------------------------------------------------------------------------
TerrainActor::~TerrainActor ()
{
}
//----------------------------------------------------------------------------
void TerrainActor::SetTerrain (Terrain *terrain)
{
	mTerrain = terrain;
	SetMovable(mTerrain);
}
//----------------------------------------------------------------------------
void TerrainActor::DoEnter ()
{
}
//----------------------------------------------------------------------------
void TerrainActor::DoExecute (Event *event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
void TerrainActor::DoLeave ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* TerrainActor::GetObjectByName (const std::string& name)
{
	Object* found = Actor::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void TerrainActor::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Actor::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
TerrainActor::TerrainActor (LoadConstructor value)
	:
Actor(value)
{
}
//----------------------------------------------------------------------------
void TerrainActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Actor::Load(source);
	source.ReadPointer(mTerrain);

	PX2_END_DEBUG_STREAM_LOAD(TerrainActor, source);
}
//----------------------------------------------------------------------------
void TerrainActor::Link (InStream& source)
{
	Actor::Link(source);
	source.ResolveLink(mTerrain);
}
//----------------------------------------------------------------------------
void TerrainActor::PostLink ()
{
	Actor::PostLink();
}
//----------------------------------------------------------------------------
bool TerrainActor::Register (OutStream& target) const
{
	if (Actor::Register(target))
	{
		target.Register(mTerrain);

		return true;
	}	

	return false;
}
//----------------------------------------------------------------------------
void TerrainActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Actor::Save(target);
	target.WritePointer(mTerrain);

	PX2_END_DEBUG_STREAM_SAVE(TerrainActor, target);
}
//----------------------------------------------------------------------------
int TerrainActor::GetStreamingSize () const
{
	int size = Actor::GetStreamingSize();
	size += PX2_POINTERSIZE(mTerrain);

	return size;
}
//----------------------------------------------------------------------------