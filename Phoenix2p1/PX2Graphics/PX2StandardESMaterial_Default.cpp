/*
*
* ÎÄ¼þÃû³Æ	£º	PX2StandardMaterial.cpp
*
*/

#include "PX2StandardESMaterial_Default.hpp"
#include "PX2PVWMatrixConstant.hpp"
#include "PX2WMatrixConstant.hpp"
#include "PX2CameraWorldPositionConstant.hpp"
#include "PX2ShineEmissiveConstant.hpp"
#include "PX2ShineAmbientConstant.hpp"
#include "PX2ShineDiffuseConstant.hpp"
#include "PX2ShineSpecularConstant.hpp"
#include "PX2LightAmbientConstant.hpp"
#include "PX2LightDiffuseConstant.hpp"
#include "PX2LightSpecularConstant.hpp"
#include "PX2LightAttenuationConstant.hpp"
#include "PX2LightModelDVectorConstant.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Material, StandardESMaterial_Default);
PX2_IMPLEMENT_STREAM(StandardESMaterial_Default);
PX2_IMPLEMENT_FACTORY(StandardESMaterial_Default);

//----------------------------------------------------------------------------
StandardESMaterial_Default::StandardESMaterial_Default (const std::string &filename)
	:
Material(filename)
{
	PixelShader* pshader = GetPixelShader(0, 0);
	pshader->SetFilter(0, Shader::SF_LINEAR_LINEAR);
}
//----------------------------------------------------------------------------
StandardESMaterial_Default::~StandardESMaterial_Default ()
{
}
//----------------------------------------------------------------------------
MaterialInstance* StandardESMaterial_Default::CreateInstance (
	PX2::Texture2D *diffTex, PX2::Light *dirLight, PX2::Shine* shine) const
{
	MaterialInstance *instance = new0 MaterialInstance(this, 0);

	if (!dirLight)
	{
		dirLight = new0 Light(Light::LT_DIRECTIONAL);
	}

	// vertex
	instance->SetVertexConstant(0, "gPVWMatrix", new0 PVWMatrixConstant());
	instance->SetVertexConstant(0, "gShineEmissive", 
		new0 ShineEmissiveConstant(shine));
	instance->SetVertexConstant(0, "gShineAmbient",
		new0 ShineAmbientConstant(shine));
	instance->SetVertexConstant(0, "gShineDiffuse",
		new0 ShineDiffuseConstant(shine));
	instance->SetVertexConstant(0, "gLightModelDirection",
		new0 LightModelDVectorConstant(dirLight));

	// pixel
	instance->SetPixelTexture(0, "gDiffuseSampler", diffTex);

	return instance;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Name support.
//----------------------------------------------------------------------------
Object* StandardESMaterial_Default::GetObjectByName (const std::string& name)
{
	Object* found = Material::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void StandardESMaterial_Default::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Material::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Streaming support.
//----------------------------------------------------------------------------
StandardESMaterial_Default::StandardESMaterial_Default (LoadConstructor value)
	:
Material(value)
{
}
//----------------------------------------------------------------------------
void StandardESMaterial_Default::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Material::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(StandardESMaterial_Default, source);
}
//----------------------------------------------------------------------------
void StandardESMaterial_Default::Link (InStream& source)
{
	Material::Link(source);
}
//----------------------------------------------------------------------------
void StandardESMaterial_Default::PostLink ()
{
	Material::PostLink();
}
//----------------------------------------------------------------------------
bool StandardESMaterial_Default::Register (OutStream& target) const
{
	if (Material::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void StandardESMaterial_Default::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Material::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(StandardESMaterial_Default, target);
}
//----------------------------------------------------------------------------
int StandardESMaterial_Default::GetStreamingSize () const
{
	int size = Material::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------