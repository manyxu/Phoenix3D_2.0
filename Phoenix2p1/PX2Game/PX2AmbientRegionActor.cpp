/*
*
* 文件名称	：	PX2AmbientRegionActor.cpp
*
*/

#include "PX2AmbientRegionActor.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, TriggerActor, AmbientRegionActor);
PX2_IMPLEMENT_STREAM(AmbientRegionActor);
PX2_IMPLEMENT_FACTORY(AmbientRegionActor);

//----------------------------------------------------------------------------
AmbientRegionActor::AmbientRegionActor ()
{
	mHorAngle = 30.0f;
	mVerAngle = 15.0f;
	mDirLightIntensity = 1.0f;

	mAmbientColor = Float4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLightDiffColor = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	mDirLightSpecColor = Float4(0.5f, 0.5f, 0.5f, 1.0f);
}
//----------------------------------------------------------------------------
AmbientRegionActor::~AmbientRegionActor ()
{
}
//----------------------------------------------------------------------------
void AmbientRegionActor::DoEnter ()
{
}
//----------------------------------------------------------------------------
void AmbientRegionActor::DoExecute (Event *event)
{
}
//----------------------------------------------------------------------------
void AmbientRegionActor::DoLeave ()
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* AmbientRegionActor::GetObjectByName (const std::string& name)
{
	Object* found = TriggerActor::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void AmbientRegionActor::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	TriggerActor::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
AmbientRegionActor::AmbientRegionActor (LoadConstructor value)
	:
TriggerActor(value)
{
}
//----------------------------------------------------------------------------
void AmbientRegionActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TriggerActor::Load(source);

	source.ReadAggregate<Float4>(mAmbientColor);
	source.ReadAggregate<Float4>(mDirLightDiffColor);
	source.ReadAggregate<Float4>(mDirLightSpecColor);
	source.Read(mDirLightIntensity);
	source.Read(mHorAngle);
	source.Read(mVerAngle);
	source.ReadPointer(mLight);

	PX2_END_DEBUG_STREAM_LOAD(AmbientRegionActor, source);
}
//----------------------------------------------------------------------------
void AmbientRegionActor::Link (InStream& source)
{
	TriggerActor::Link(source);

	if (mLight)
		source.ResolveLink(mLight);
}
//----------------------------------------------------------------------------
void AmbientRegionActor::PostLink ()
{
	TriggerActor::PostLink();
}
//----------------------------------------------------------------------------
bool AmbientRegionActor::Register (OutStream& target) const
{
	if (TriggerActor::Register(target))
	{
		if (mLight)
			target.Register(mLight);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void AmbientRegionActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TriggerActor::Save(target);

	target.WriteAggregate<Float4>(mAmbientColor);
	target.WriteAggregate<Float4>(mDirLightDiffColor);
	target.WriteAggregate<Float4>(mDirLightSpecColor);
	target.Write(mDirLightIntensity);
	target.Write(mHorAngle);
	target.Write(mVerAngle);
	target.WritePointer(mLight);

	PX2_END_DEBUG_STREAM_SAVE(AmbientRegionActor, target);
}
//----------------------------------------------------------------------------
int AmbientRegionActor::GetStreamingSize () const
{
	int size = TriggerActor::GetStreamingSize();
	size += sizeof(mAmbientColor);
	size += sizeof(mDirLightDiffColor);
	size += sizeof(mDirLightSpecColor);
	size += sizeof(mDirLightIntensity);
	size += sizeof(mHorAngle);
	size += sizeof(mVerAngle);
	size += PX2_POINTERSIZE(mLight);

	return size;
}
//----------------------------------------------------------------------------