/*
*
* 文件名称	：	PX2SkyActor.cpp
*
*/

#include "PX2EffectActor.hpp"
#include "PX2StandardMesh.hpp"
#include "PX2VertexColor4Material.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Actor, EffectActor);
PX2_IMPLEMENT_STREAM(EffectActor);
PX2_IMPLEMENT_FACTORY(EffectActor);

//----------------------------------------------------------------------------
EffectActor::EffectActor (EffectNode *effect)
	:
mEffect(effect)
{
	if (effect)
	{
		SetMovable(effect);
	}

	VertexFormat *vf = VertexFormat::Create(2,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0);

	StandardMesh stdMesh(vf);
	stdMesh.SetVertexColor(Float4(1.0f,1.0f,0.0f,1.0f));
	TriMesh *mesh = stdMesh.Octahedron();
	PX2::VertexColor4MaterialPtr mtl = new0 VertexColor4Material();
	mtl->GetWireProperty(0, 0)->Enabled = true;
	mtl->GetCullProperty(0, 0)->Enabled = false;
	mesh->LocalTransform.SetUniformScale(0.5f);
	mesh->SetMaterialInstance(mtl->CreateInstance());

	SetHelpMovable(mesh);
	ShowHelpMovable(true);
}
//----------------------------------------------------------------------------
EffectActor::~EffectActor ()
{
}
//----------------------------------------------------------------------------
void EffectActor::SetEffect(EffectNode *effect)
{
	mEffect = effect;
	SetMovable(mEffect);
}
//----------------------------------------------------------------------------
void EffectActor::DoEnter ()
{
}
//----------------------------------------------------------------------------
void EffectActor::DoExecute (Event *event)
{
}
//----------------------------------------------------------------------------
void EffectActor::DoLeave ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* EffectActor::GetObjectByName (const std::string& name)
{
	Object* found = Actor::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void EffectActor::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Actor::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EffectActor::EffectActor (LoadConstructor value)
	:
Actor(value)
{
}
//----------------------------------------------------------------------------
void EffectActor::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Actor::Load(source);
	source.ReadPointer(mEffect);

	PX2_END_DEBUG_STREAM_LOAD(EffectActor, source);
}
//----------------------------------------------------------------------------
void EffectActor::Link (InStream& source)
{
	Actor::Link(source);
	source.ResolveLink(mEffect);
}
//----------------------------------------------------------------------------
void EffectActor::PostLink ()
{
	Actor::PostLink();
}
//----------------------------------------------------------------------------
bool EffectActor::Register (OutStream& target) const
{
	if (Actor::Register(target))
	{
		target.Register(mEffect);

		return true;
	}	

	return false;
}
//----------------------------------------------------------------------------
void EffectActor::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Actor::Save(target);
	target.WritePointer(mEffect);

	PX2_END_DEBUG_STREAM_SAVE(EffectActor, target);
}
//----------------------------------------------------------------------------
int EffectActor::GetStreamingSize () const
{
	int size = Actor::GetStreamingSize();
	size += PX2_POINTERSIZE(mEffect);

	return size;
}
//----------------------------------------------------------------------------