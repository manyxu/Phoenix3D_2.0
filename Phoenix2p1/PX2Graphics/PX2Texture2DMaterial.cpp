/*
*
* 文件名称	：	PX2Texture2DMaterial.cpp
*
*/

#include "PX2Texture2DMaterial.hpp"
#include "PX2PVWMatrixConstant.hpp"
#include "PX2PMatrixConstant.hpp"
#include "PX2WMatrixConstant.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Material, Texture2DMaterial);
PX2_IMPLEMENT_STREAM(Texture2DMaterial);
PX2_IMPLEMENT_FACTORY(Texture2DMaterial);
PX2_IMPLEMENT_DEFAULT_NAMES(Material, Texture2DMaterial);

//----------------------------------------------------------------------------
Texture2DMaterial::Texture2DMaterial (Shader::SamplerFilter filter,
								  Shader::SamplerCoordinate coordinate0,
								  Shader::SamplerCoordinate coordinate1)
{
	VertexShader* vshader = new0 VertexShader("PX2.Texture2D",
		2, 2, 1, 0, false);
	vshader->SetInput(0, "modelPosition", Shader::VT_FLOAT3,
		Shader::VS_POSITION);
	vshader->SetInput(1, "modelTCoord", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD0);
	vshader->SetOutput(0, "clipPosition", Shader::VT_FLOAT4,
		Shader::VS_POSITION);
	vshader->SetOutput(1, "vertexTCoord", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD0);
	vshader->SetConstant(0, "PVWMatrix", 4);
	vshader->SetBaseRegisters(msVRegisters);
	vshader->SetPrograms(msVPrograms);

	PixelShader* pshader = new0 PixelShader("PX2.Texture2D",
		1, 1, 0, 1, false);
	pshader->SetInput(0, "vertexTCoord", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD0);
	pshader->SetOutput(0, "pixelColor", Shader::VT_FLOAT4,
		Shader::VS_COLOR0);
	pshader->SetSampler(0, "BaseSampler", Shader::ST_2D);
	pshader->SetFilter(0, filter);
	pshader->SetCoordinate(0, 0, coordinate0);
	pshader->SetCoordinate(0, 1, coordinate1);
	pshader->SetTextureUnits(msPTextureUnits);
	pshader->SetPrograms(msPPrograms);

	MaterialPass* pass = new0 MaterialPass();
	pass->SetVertexShader(vshader);
	pass->SetPixelShader(pshader);
	pass->SetAlphaProperty(new0 AlphaProperty());
	pass->SetCullProperty(new0 CullProperty());
	pass->SetDepthProperty(new0 DepthProperty());
	pass->SetOffsetProperty(new0 OffsetProperty());
	pass->SetStencilProperty(new0 StencilProperty());
	pass->SetWireProperty(new0 WireProperty());

	MaterialTechnique* technique = new0 MaterialTechnique();
	technique->InsertPass(pass);
	InsertTechnique(technique);
}
//----------------------------------------------------------------------------
Texture2DMaterial::~Texture2DMaterial ()
{
}
//----------------------------------------------------------------------------
PixelShader* Texture2DMaterial::GetPixelShader () const
{
	return mTechniques[0]->GetPass(0)->GetPixelShader();
}
//----------------------------------------------------------------------------
MaterialInstance* Texture2DMaterial::CreateInstance (Texture2D* texture) const
{
	MaterialInstance* instance = new0 MaterialInstance(this, 0);
	instance->SetVertexConstant(0, "PVWMatrix", new0 PVWMatrixConstant());
	instance->SetPixelTexture(0, "BaseSampler", texture);

	//Shader::SamplerFilter filter = GetPixelShader()->GetFilter(0);
	//if (filter != Shader::SF_NEAREST && filter != Shader::SF_LINEAR
	//	&&  !texture->HasMipmaps() && texture->GetFormat()!=Texture::TF_DXT1
	//	&& texture->GetFormat()!=Texture::TF_DXT3 && texture->GetFormat()!=
	//	Texture::TF_DXT5)
	//{
	//	//texture->GenerateMipmaps();
	//}

	return instance;
}
//----------------------------------------------------------------------------
MaterialInstance* Texture2DMaterial::CreateUniqueInstance (
	Texture2D* texture, Shader::SamplerFilter filter,
	Shader::SamplerCoordinate coordinate0,
	Shader::SamplerCoordinate coordinate1)
{
	Texture2DMaterial* effect = new0 Texture2DMaterial();
	PixelShader* pshader = effect->GetPixelShader();
	pshader->SetFilter(0, filter);
	pshader->SetCoordinate(0, 0, coordinate0);
	pshader->SetCoordinate(0, 1, coordinate1);
	return effect->CreateInstance(texture);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
Texture2DMaterial::Texture2DMaterial (LoadConstructor value)
:
Material(value)
{
}
//----------------------------------------------------------------------------
void Texture2DMaterial::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Material::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(Texture2DMaterial, source);
}
//----------------------------------------------------------------------------
void Texture2DMaterial::Link (InStream& source)
{
	Material::Link(source);
}
//----------------------------------------------------------------------------
void Texture2DMaterial::PostLink ()
{
	Material::PostLink();

	MaterialPass* pass = mTechniques[0]->GetPass(0);
	VertexShader* vshader = pass->GetVertexShader();
	PixelShader* pshader = pass->GetPixelShader();
	vshader->SetBaseRegisters(msVRegisters);
	vshader->SetPrograms(msVPrograms);
	pshader->SetTextureUnits(msPTextureUnits);
	pshader->SetPrograms(msPPrograms);
}
//----------------------------------------------------------------------------
bool Texture2DMaterial::Register (OutStream& target) const
{
	return Material::Register(target);
}
//----------------------------------------------------------------------------
void Texture2DMaterial::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Material::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(Texture2DMaterial, target);
}
//----------------------------------------------------------------------------
int Texture2DMaterial::GetStreamingSize () const
{
	return Material::GetStreamingSize();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Profiles.
//----------------------------------------------------------------------------
int Texture2DMaterial::msDx9VRegisters[1] = { 0 };
int Texture2DMaterial::msOglVRegisters[1] = { 1 };
int Texture2DMaterial::msOpenGLES2VRegisters[1] = { 0 };
int* Texture2DMaterial::msVRegisters[Shader::MAX_PROFILES] =
{
	0,
	msDx9VRegisters,
	msDx9VRegisters,
	msDx9VRegisters,
	msOglVRegisters,
	msOpenGLES2VRegisters
};

std::string Texture2DMaterial::msVPrograms[Shader::MAX_PROFILES] =
{
	// VP_NONE
	"",

	// VP_VS_1_1
	"vs_1_1\n"
	"def c4, 1.00000000, 0, 0, 0\n"
	"dcl_position0 v0\n"
	"dcl_texcoord0 v1\n"
	"mov r0.w, c4.x\n"
	"mov r0.xyz, v0\n"
	"dp4 oPos.w, r0, c3\n"
	"dp4 oPos.z, r0, c2\n"
	"dp4 oPos.y, r0, c1\n"
	"dp4 oPos.x, r0, c0\n"
	"mov oT0.xy, v1\n",

	// VP_VS_2_0
	"vs_2_0\n"
	"def c4, 1.00000000, 0, 0, 0\n"
	"dcl_position v0\n"
	"dcl_texcoord0 v1\n"
	"mov r0.w, c4.x\n"
	"mov r0.xyz, v0\n"
	"dp4 oPos.w, r0, c3\n"
	"dp4 oPos.z, r0, c2\n"
	"dp4 oPos.y, r0, c1\n"
	"dp4 oPos.x, r0, c0\n"
	"mov oT0.xy, v1\n",

	// VP_VS_3_0
	"vs_3_0\n"
	"dcl_position o0\n"
	"dcl_texcoord0 o1\n"
	"def c4, 1.00000000, 0, 0, 0\n"
	"dcl_position0 v0\n"
	"dcl_texcoord0 v1\n"
	"mov r0.w, c4.x\n"
	"mov r0.xyz, v0\n"
	"dp4 o0.w, r0, c3\n"
	"dp4 o0.z, r0, c2\n"
	"dp4 o0.y, r0, c1\n"
	"dp4 o0.x, r0, c0\n"
	"mov o1.xy, v1\n",

	// VP_ARBVP1
	"!!ARBvp1.0\n"
	"PARAM c[5] = { { 1 }, program.local[1..4] };\n"
	"TEMP R0;\n"
	"MOV R0.w, c[0].x;\n"
	"MOV R0.xyz, vertex.position;\n"
	"DP4 result.position.w, R0, c[4];\n"
	"DP4 result.position.z, R0, c[3];\n"
	"DP4 result.position.y, R0, c[2];\n"
	"DP4 result.position.x, R0, c[1];\n"
	"MOV result.texcoord[0].xy, vertex.texcoord[0];\n"
	"END\n",

	// vp_gles2
	"uniform highp mat4 PVWMatrix;"
	"attribute highp vec3 modelPosition;\n"
	"attribute mediump vec2 modelTCoord0;\n"
	"varying mediump vec2 vertexTCoord0;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = PVWMatrix * vec4(modelPosition, 1.0);\n"
	"	vertexTCoord0 = modelTCoord0;\n"
	"}\n"
};

int Texture2DMaterial::msAllPTextureUnits[1] = { 0 };
int* Texture2DMaterial::msPTextureUnits[Shader::MAX_PROFILES] =
{
	0,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits
};

std::string Texture2DMaterial::msPPrograms[Shader::MAX_PROFILES] =
{
	// PP_NONE
	"",

	// PP_PS_1_1
	"ps.1.1\n"
	"tex t0\n"
	"mov r0, t0\n",

	// PP_PS_2_0
	"ps_2_0\n"
	"dcl_2d s0\n"
	"dcl t0.xy\n"
	"texld r0, t0, s0\n"
	"mov oC0, r0\n",

	// PP_PS_3_0
	"ps_3_0\n"
	"dcl_2d s0\n"
	"dcl_texcoord0 v0.xy\n"
	"texld r0, v0, s0\n"
	"mov oC0, r0\n",

	// PP_ARBFP1
	"!!ARBfp1.0\n"
	"TEX result.color, fragment.texcoord[0], texture[0], 2D;\n"
	"END\n",

	// fp_gles2
	"varying mediump vec2 vertexTCoord0;\n"
	"uniform sampler2D BaseSampler;\n"
	"void main()\n"
	"{\n"
	"	gl_FragColor = texture2D(BaseSampler, vertexTCoord0);\n"
	"}\n"
};
//----------------------------------------------------------------------------
