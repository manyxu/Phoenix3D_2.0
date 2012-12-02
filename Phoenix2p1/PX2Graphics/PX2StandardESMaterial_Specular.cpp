/*
*
* ÎÄ¼þÃû³Æ	£º	PX2StandardMaterial.cpp
*
*/

#include "PX2StandardESMaterial_Specular.hpp"
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

PX2_IMPLEMENT_RTTI(PX2, Material, StandardESMaterial_Specular);
PX2_IMPLEMENT_STREAM(StandardESMaterial_Specular);
PX2_IMPLEMENT_FACTORY(StandardESMaterial_Specular);

//----------------------------------------------------------------------------
StandardESMaterial_Specular::StandardESMaterial_Specular (const std::string &filename)
	:
Material(filename)
{
	PixelShader* pshader = GetPixelShader(0, 0);
	pshader->SetFilter(0, Shader::SF_LINEAR_LINEAR);
}
//----------------------------------------------------------------------------
StandardESMaterial_Specular::~StandardESMaterial_Specular ()
{
}
//----------------------------------------------------------------------------
MaterialInstance* StandardESMaterial_Specular::CreateInstance (
	PX2::Texture2D *diffTex,
	PX2::Texture2D *specTex,
	float specularPower,
	PX2::Light *dirLight,
	PX2::Shine* shine) const
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
	instance->SetVertexConstant(0, "gLightColour",
		new0 LightDiffuseConstant(dirLight));
	instance->SetVertexConstant(0, "gLightModelDirection",
		new0 LightModelDVectorConstant(dirLight));

	// pixel
	instance->SetPixelTexture(0, "gDiffuseSampler", diffTex);
	instance->SetPixelTexture(0, "gSpecularSampler", specTex);

	Float4 ctrlFloat;
	ctrlFloat[0] = specularPower;
	ctrlFloat[1] = 0.0f;
	ctrlFloat[2] = 0.0f;
	ctrlFloat[3] = 0.0f;
	ShaderFloat *ctrlShaderFloat = new0 ShaderFloat(1);
	ctrlShaderFloat->SetRegister(0, (float*)&ctrlFloat);
	instance->SetPixelConstant(0, "gControlFloat", ctrlShaderFloat);

	return instance;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Name support.
//----------------------------------------------------------------------------
Object* StandardESMaterial_Specular::GetObjectByName (const std::string& name)
{
	Object* found = Material::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void StandardESMaterial_Specular::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Material::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Streaming support.
//----------------------------------------------------------------------------
StandardESMaterial_Specular::StandardESMaterial_Specular (LoadConstructor value)
	:
Material(value)
{
}
//----------------------------------------------------------------------------
void StandardESMaterial_Specular::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Material::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(StandardESMaterial_Specular, source);
}
//----------------------------------------------------------------------------
void StandardESMaterial_Specular::Link (InStream& source)
{
	Material::Link(source);
}
//----------------------------------------------------------------------------
void StandardESMaterial_Specular::PostLink ()
{
	Material::PostLink();
}
//----------------------------------------------------------------------------
bool StandardESMaterial_Specular::Register (OutStream& target) const
{
	if (Material::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void StandardESMaterial_Specular::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Material::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(StandardESMaterial_Specular, target);
}
//----------------------------------------------------------------------------
int StandardESMaterial_Specular::GetStreamingSize () const
{
	int size = Material::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------