/*
*
* 文件名称	：	PX2RawTerrainActor.cpp
*
*/

#include "PX2RawTerrainActor.hpp"
#include "PX2Scene.hpp"
using namespace PX2;
using namespace TdBt;

PX2_IMPLEMENT_RTTI(PX2, Actor, RawTerrainActor);
PX2_IMPLEMENT_STREAM(RawTerrainActor);
PX2_IMPLEMENT_FACTORY(RawTerrainActor);

RawTerrainActor::RawTerrainActor ()
{
}
//----------------------------------------------------------------------------
RawTerrainActor::~RawTerrainActor ()
{
}
//----------------------------------------------------------------------------
void RawTerrainActor::SetTerrain (RawTerrain *terrain)
{
	mTerrain = terrain;
	SetMovable(mTerrain);
}
//----------------------------------------------------------------------------
void RawTerrainActor::EnablePhysics (bool enable)
{
	mPhysicsEnabled = enable;

	if (mPhysicsEnabled)
	{
		_EnablePhysics();
	}
	else
	{
		_DisablePhysics();
	}
}
//----------------------------------------------------------------------------
void RawTerrainActor::DoEnter ()
{

}
//----------------------------------------------------------------------------
void RawTerrainActor::DoUpdate ()
{
}
//----------------------------------------------------------------------------
void RawTerrainActor::DoExecute (Event *event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
void RawTerrainActor::DoLeave ()
{

}
//----------------------------------------------------------------------------
void RawTerrainActor::_EnablePhysics ()
{
	assertion(mScene!=0, "Actor must already be in scene.");
	if (!mScene)
		return;

	TdBt::DynamicWorld *dynamicWorld = GetScene()->GetDynamicWorld();
	assertion(dynamicWorld!=0, "dynamicWorld must not be 0/n");
	if (!dynamicWorld)
		return;

	PX2::RawTerrain *terrain = DynamicCast<RawTerrain>(mMovable);
	if (terrain)
	{
		int numRow = terrain->GetRowQuantity();
		int numCol = terrain->GetColQuantity();
		for (int i=0; i<numRow; i++)
		{
			for (int j=0; j<numCol; j++)
			{
				RawTerrainPage *page = terrain->GetPage(i, j);
				if (page)
				{
					RigidBody *body = new0 RigidBody(dynamicWorld);

					TriangleMeshCollisionShape *shape = 
						new0 TriangleMeshCollisionShape(page);
					APoint pos = page->GetWorldTransform().GetTranslate();
					HQuaternion quat;
					HMatrix matRot = page->GetWorldTransform().GetRotate();
					quat.FromRotationMatrix(matRot);
					body->SetStaticShape(shape, 0.1f, 0.8f, pos, quat);
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void RawTerrainActor::_DisablePhysics ()
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* RawTerrainActor::GetObjectByName (const std::string& name)
{
	Object* found = Actor::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void RawTerrainActor::GetAllObjectsByName (const std::string& name,
										   std::vector<Object*>& objects)
{
	Actor::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
RawTerrainActor::RawTerrainActor (LoadConstructor value)
:
Actor(value)
{
}
//----------------------------------------------------------------------------
void RawTerrainActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Actor::Load(source);
	source.ReadPointer(mTerrain);

	PX2_END_DEBUG_STREAM_LOAD(RawTerrainActor, source);
}
//----------------------------------------------------------------------------
void RawTerrainActor::Link (InStream& source)
{
	Actor::Link(source);
	source.ResolveLink(mTerrain);
}
//----------------------------------------------------------------------------
void RawTerrainActor::PostLink ()
{
	Actor::PostLink();
}
//----------------------------------------------------------------------------
bool RawTerrainActor::Register (OutStream& target) const
{
	if (Actor::Register(target))
	{
		target.Register(mTerrain);

		return true;
	}	

	return false;
}
//----------------------------------------------------------------------------
void RawTerrainActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Actor::Save(target);
	target.WritePointer(mTerrain);

	PX2_END_DEBUG_STREAM_SAVE(RawTerrainActor, target);
}
//----------------------------------------------------------------------------
int RawTerrainActor::GetStreamingSize () const
{
	int size = Actor::GetStreamingSize();
	size += PX2_POINTERSIZE(mTerrain);

	return size;
}
//----------------------------------------------------------------------------