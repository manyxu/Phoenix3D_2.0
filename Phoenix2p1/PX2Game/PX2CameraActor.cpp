/*
*
* 文件名称	：	PX2CameraActor.cpp
*
*/

#include "PX2CameraActor.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Actor, CameraActor);
PX2_IMPLEMENT_STREAM(CameraActor);
PX2_IMPLEMENT_FACTORY(CameraActor);

//----------------------------------------------------------------------------
CameraActor::CameraActor (Camera *camera)
	:
mCamera(camera)
{
}
//----------------------------------------------------------------------------
CameraActor::~CameraActor ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* CameraActor::GetObjectByName (const std::string& name)
{
	Object* found = Actor::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mCamera, name, found);

	return 0;
}
//----------------------------------------------------------------------------
void CameraActor::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Actor::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mCamera, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
CameraActor::CameraActor (LoadConstructor value)
	:
mCamera(0)
{
}
//----------------------------------------------------------------------------
void CameraActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Actor::Load(source);
	source.ReadPointer(mCamera);

	PX2_END_DEBUG_STREAM_LOAD(CameraActor, source);
}
//----------------------------------------------------------------------------
void CameraActor::Link (InStream& source)
{
	Actor::Link(source);

	source.ResolveLink(mCamera);
}
//----------------------------------------------------------------------------
void CameraActor::PostLink ()
{
	Actor::PostLink();
}
//----------------------------------------------------------------------------
bool CameraActor::Register (OutStream& target) const
{
	if (Actor::Register(target))
	{
		target.Register(mCamera);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void CameraActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Actor::Save(target);
	target.WritePointer(mCamera);

	PX2_END_DEBUG_STREAM_SAVE(CameraActor, target);
}
//----------------------------------------------------------------------------
int CameraActor::GetStreamingSize () const
{
	int size = Actor::GetStreamingSize();
	size += PX2_POINTERSIZE(mCamera);

	return size;
}
//----------------------------------------------------------------------------