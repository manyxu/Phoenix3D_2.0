/*
*
* 文件名称	：	PX2LightActor.cpp
*
*/

#include "PX2LightActor.hpp"
#include "PX2StandardMesh.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Actor, LightActor);
PX2_IMPLEMENT_STREAM(LightActor);
PX2_IMPLEMENT_FACTORY(LightActor);

LightActor::LightActor (PX2::Light *light)
{
	mLight = light;
	mLightNode = new0 LightNode(light);
	SetMovable(mLightNode);

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
LightActor::~LightActor ()
{

}
//----------------------------------------------------------------------------
void LightActor::SetLight (PX2::Light *light)
{
	mLight = light;
	mLightNode->SetLight(light);
}
//----------------------------------------------------------------------------
void LightActor::DoEnter ()
{

}
//----------------------------------------------------------------------------
void LightActor::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void LightActor::DoExecute (Event *event)
{
	Actor::DoExecute(event);
}
//----------------------------------------------------------------------------
void LightActor::DoLeave ()
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* LightActor::GetObjectByName (const std::string& name)
{
	Object* found = Actor::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void LightActor::GetAllObjectsByName (const std::string& name,
										   std::vector<Object*>& objects)
{
	Actor::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
LightActor::LightActor (LoadConstructor value)
:
Actor(value)
{
}
//----------------------------------------------------------------------------
void LightActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Actor::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(LightActor, source);
}
//----------------------------------------------------------------------------
void LightActor::Link (InStream& source)
{
	Actor::Link(source);
}
//----------------------------------------------------------------------------
void LightActor::PostLink ()
{
	Actor::PostLink();
}
//----------------------------------------------------------------------------
bool LightActor::Register (OutStream& target) const
{
	if (Actor::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void LightActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Actor::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(LightActor, target);
}
//----------------------------------------------------------------------------
int LightActor::GetStreamingSize () const
{
	int size = Actor::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------