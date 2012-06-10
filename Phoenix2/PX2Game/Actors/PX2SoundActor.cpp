/*
*
* 文件名称	：	PX2SoundActor.cpp
*
*/

#include "PX2SoundActor.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Actor, SoundActor);
PX2_IMPLEMENT_STREAM(SoundActor);
PX2_IMPLEMENT_FACTORY(SoundActor);

SoundActor::SoundActor (const char *fileName)
{
	SoundCreateInfo3D info;
	mSoundable = new0 Soundable(fileName, info);
	SetMovable(mSoundable);

	VertexFormat *vf = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0);

	StandardMesh stdMesh(vf);
	stdMesh.SetVertexColor(Float4(0.0f,1.0f,0.0f,0.0f));
	TriMesh *mesh = stdMesh.Octahedron();
	PX2::VertexColor4Material *material = new0 VertexColor4Material();
	material->GetWireProperty(0, 0)->Enabled = true;
	mesh->WorldTransformIsCurrent = true;
	mesh->WorldTransform.SetUniformScale(0.2f);
	mesh->SetMaterialInstance(material->CreateUniqueInstance());

	SetHelpMovable(mesh);
	ShowHelpMovable(true);
}
//----------------------------------------------------------------------------
SoundActor::SoundActor (Soundable *soundable)
{
	mSoundable = soundable;
	SetMovable(mSoundable);

	VertexFormat *vf = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0);

	StandardMesh stdMesh(vf);
	stdMesh.SetVertexColor(Float4(0.0f,1.0f,0.0f,0.0f));
	TriMesh *mesh = stdMesh.Octahedron();
	PX2::VertexColor4Material *material = new0 VertexColor4Material();
	material->GetWireProperty(0, 0)->Enabled = true;
	mesh->WorldTransformIsCurrent = true;
	mesh->WorldTransform.SetUniformScale(0.2f);
	mesh->SetMaterialInstance(material->CreateUniqueInstance());

	SetHelpMovable(mesh);
	ShowHelpMovable(true);
}
//----------------------------------------------------------------------------
SoundActor::~SoundActor ()
{

}
//----------------------------------------------------------------------------
void SoundActor::Play ()
{
	if (mSoundable)
		mSoundable->Play();
}
//----------------------------------------------------------------------------
void SoundActor::DoEnter ()
{

}
//----------------------------------------------------------------------------
void SoundActor::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void SoundActor::DoExecute (Event *event)
{

}
//----------------------------------------------------------------------------
void SoundActor::DoLeave ()
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* SoundActor::GetObjectByName (const std::string& name)
{
	Object* found = Actor::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void SoundActor::GetAllObjectsByName (const std::string& name,
									  std::vector<Object*>& objects)
{
	Actor::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
SoundActor::SoundActor (LoadConstructor value)
:
Actor(value)
{
}
//----------------------------------------------------------------------------
void SoundActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Actor::Load(source);
	source.ReadPointer(mSoundable);

	PX2_END_DEBUG_STREAM_LOAD(SoundActor, source);
}
//----------------------------------------------------------------------------
void SoundActor::Link (InStream& source)
{
	Actor::Link(source);
	source.ResolveLink(mSoundable);
}
//----------------------------------------------------------------------------
void SoundActor::PostLink ()
{
	Actor::PostLink();
}
//----------------------------------------------------------------------------
bool SoundActor::Register (OutStream& target) const
{
	if (Actor::Register(target))
	{
		if (mSoundable)
			mSoundable->Register(target);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void SoundActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Actor::Save(target);
	target.WritePointer(mSoundable);

	PX2_END_DEBUG_STREAM_SAVE(SoundActor, target);
}
//----------------------------------------------------------------------------
int SoundActor::GetStreamingSize () const
{
	int size = Actor::GetStreamingSize();
	size += PX2_POINTERSIZE(mSoundable);

	return size;
}
//----------------------------------------------------------------------------