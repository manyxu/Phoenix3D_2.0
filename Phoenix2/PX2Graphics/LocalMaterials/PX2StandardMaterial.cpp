/*
*
* ÎÄ¼þÃû³Æ	£º	PX2StandardMaterial.cpp
*
*/

#include "PX2StandardMaterial.hpp"
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

PX2_IMPLEMENT_RTTI(PX2, Material, StandardMaterial);
PX2_IMPLEMENT_STREAM(StandardMaterial);
PX2_IMPLEMENT_FACTORY(StandardMaterial);

//----------------------------------------------------------------------------
StandardMaterial::StandardMaterial (const std::string &filename)
									:
Material(filename)
{
	PixelShader* pshader = GetPixelShader(0, 0);
	pshader->SetFilter(0, Shader::SF_LINEAR_LINEAR);
	pshader->SetFilter(1, Shader::SF_LINEAR_LINEAR);
	pshader->SetFilter(2, Shader::SF_LINEAR_LINEAR);
}
//----------------------------------------------------------------------------
StandardMaterial::~StandardMaterial ()
{
}
//----------------------------------------------------------------------------
MaterialInstance* StandardMaterial::CreateInstance (PX2::Texture2D *diffTex,
													bool alphaVertex,
													bool normalEnable,
													PX2::Texture2D *normalTex,
													float normalScale,
													bool specularEnable,
													PX2::Texture2D *specularTex,
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
	instance->SetVertexConstant(0, "gWMatrix", new0 WMatrixConstant());
	instance->SetVertexConstant(0, "gCameraWorldPosition", 
		new0 CameraWorldPositionConstant());
	instance->SetVertexConstant(0, "gLightModelDirection",
		new0 LightModelDVectorConstant(dirLight));

	Float4 ctrlFloat;
	ctrlFloat[0] = alphaVertex ? 1.0f : 0.0f;
	ctrlFloat[1] = normalEnable ? 1.0f : 0.0f;
	ctrlFloat[2] = specularEnable ? 1.0f : 0.0f;
	ctrlFloat[3] = 1.0f;
	ShaderFloat *ctrlShaderFloat = new0 ShaderFloat(1);
	ctrlShaderFloat->SetRegister(0, (float*)&ctrlFloat);
	instance->SetVertexConstant(0, "gControlFloat", ctrlShaderFloat);

	// pixel
	instance->SetPixelConstant(0, "gControlFloat", ctrlShaderFloat);
	Float4 degreeFloat;
	degreeFloat[0] = normalScale;
	degreeFloat[1] = specularPower;
	degreeFloat[2] = 1.0f;
	degreeFloat[3] = 1.0f;
	ShaderFloat *degreeShaderFloat = new0 ShaderFloat(1);
	degreeShaderFloat->SetRegister(0, (float*)&degreeFloat);
	instance->SetPixelConstant(0, "gDegreeFloat", degreeShaderFloat);
	instance->SetPixelTexture(0, "gDiffuseSampler", diffTex);

	if (normalTex && normalEnable)
		instance->SetPixelTexture(0, "gNormalSampler", normalTex);
	else
		instance->SetPixelTexture(0, "gNormalSampler", diffTex);

	if (specularTex && specularEnable)
		instance->SetPixelTexture(0, "gSpecularSampler", specularTex);
	else
		instance->SetPixelTexture(0, "gSpecularSampler", diffTex);
	instance->SetPixelConstant(0, "gShineEmissive", 
		new0 ShineEmissiveConstant(shine));
	instance->SetPixelConstant(0, "gShineAmbient", 
		new0 ShineAmbientConstant(shine));
	instance->SetPixelConstant(0, "gShineDiffuse", 
		new0 ShineDiffuseConstant(shine));

	instance->SetPixelConstant(0, "gLightColour",
		new0 LightDiffuseConstant(dirLight));

	return instance;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Name support.
//----------------------------------------------------------------------------
Object* StandardMaterial::GetObjectByName (const std::string& name)
{
	Object* found = Material::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void StandardMaterial::GetAllObjectsByName (const std::string& name,
											std::vector<Object*>& objects)
{
	Material::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Streaming support.
//----------------------------------------------------------------------------
StandardMaterial::StandardMaterial (LoadConstructor value)
:
Material(value)
{
}
//----------------------------------------------------------------------------
void StandardMaterial::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Material::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(StandardMaterial, source);
}
//----------------------------------------------------------------------------
void StandardMaterial::Link (InStream& source)
{
	Material::Link(source);
}
//----------------------------------------------------------------------------
void StandardMaterial::PostLink ()
{
	Material::PostLink();
}
//----------------------------------------------------------------------------
bool StandardMaterial::Register (OutStream& target) const
{
	if (Material::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void StandardMaterial::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Material::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(StandardMaterial, target);
}
//----------------------------------------------------------------------------
int StandardMaterial::GetStreamingSize () const
{
	int size = Material::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------