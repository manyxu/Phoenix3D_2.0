/*
*
* 文件名称	：	PX2EditTerrainMaterial.cpp
*
*/

#include "PX2EditTerrainMaterial.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Material, EditTerrainMaterial);
PX2_IMPLEMENT_STREAM(EditTerrainMaterial);
PX2_IMPLEMENT_FACTORY(EditTerrainMaterial);
PX2_IMPLEMENT_DEFAULT_NAMES(Material, EditTerrainMaterial);

//----------------------------------------------------------------------------
EditTerrainMaterial::EditTerrainMaterial ()
{
	// vertex shader
	VertexShader* vshader = new0 VertexShader("PX2.EditTerrain",
		4, 3, 7, 0, false);
	vshader->SetInput(0, "modelPosition", Shader::VT_FLOAT3,
		Shader::VS_POSITION);
	vshader->SetInput(1, "modelNormal", Shader::VT_FLOAT3,
		Shader::VS_NORMAL);
	vshader->SetInput(2, "modelColor0", Shader::VT_FLOAT3,
		Shader::VS_COLOR0);
	vshader->SetInput(3, "modelTCoord0", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD0);

	vshader->SetOutput(0, "clipPosition", Shader::VT_FLOAT4,
		Shader::VS_POSITION);
	vshader->SetOutput(1, "vertexColor0", Shader::VT_FLOAT4,
		Shader::VS_COLOR0);
	vshader->SetOutput(2, "vertexTCoord0", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD0);

	vshader->SetConstant(0, "gPVWMatrix", 4);
	vshader->SetConstant(1, "gShineEmissive", 1);
	vshader->SetConstant(2, "gShineAmbient", 1);
	vshader->SetConstant(3, "gShineDiffuse", 1);
	vshader->SetConstant(4, "gLightColour", 1);
	vshader->SetConstant(5, "gLightAttenuation", 1);
	vshader->SetConstant(6, "gLightModelDirection", 1);

	vshader->SetBaseRegisters(msVRegisters);
	vshader->SetPrograms(msVPrograms);

	// pixel shader
	PixelShader* pshader = new0 PixelShader("PX2.EditTerrain",
		2, 1, 3, 6, false);

	pshader->SetInput(0, "vertexColor0", Shader::VT_FLOAT4,
		Shader::VS_COLOR0);
	pshader->SetInput(1, "vertexTCoord0", Shader::VT_FLOAT2,
		Shader::VS_TEXCOORD0);

	pshader->SetOutput(0, "pixelColor", Shader::VT_FLOAT4,
		Shader::VS_COLOR0);

	pshader->SetConstant(0, "UVScale01", 1);
	pshader->SetConstant(1, "UVScale23", 1);
	pshader->SetConstant(2, "UVScale4", 1);

	pshader->SetSampler(0, "Sampler0", Shader::ST_2D);
	pshader->SetFilter(0, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(0, 0, Shader::SC_REPEAT);
	pshader->SetCoordinate(0, 1, Shader::SC_REPEAT);

	pshader->SetSampler(1, "SamplerAlpha", Shader::ST_2D);
	pshader->SetFilter(1, Shader::SF_NEAREST_NEAREST);
	pshader->SetCoordinate(1, 0, Shader::SC_CLAMP_EDGE);
	pshader->SetCoordinate(1, 1, Shader::SC_CLAMP_EDGE);

	pshader->SetSampler(2, "Sampler1", Shader::ST_2D);
	pshader->SetFilter(2, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(2, 0, Shader::SC_REPEAT);
	pshader->SetCoordinate(2, 1, Shader::SC_REPEAT);

	pshader->SetSampler(3, "Sampler2", Shader::ST_2D);
	pshader->SetFilter(3, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(3, 0, Shader::SC_REPEAT);
	pshader->SetCoordinate(3, 1, Shader::SC_REPEAT);

	pshader->SetSampler(4, "Sampler3", Shader::ST_2D);
	pshader->SetFilter(4, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(4, 0, Shader::SC_REPEAT);
	pshader->SetCoordinate(4, 1, Shader::SC_REPEAT);

	pshader->SetSampler(5, "Sampler4", Shader::ST_2D);
	pshader->SetFilter(5, Shader::SF_LINEAR_LINEAR);
	pshader->SetCoordinate(5, 0, Shader::SC_REPEAT);
	pshader->SetCoordinate(5, 1, Shader::SC_REPEAT);

	pshader->SetBaseRegisters(msPRegisters);
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
EditTerrainMaterial::~EditTerrainMaterial ()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
EditTerrainMaterial::EditTerrainMaterial (LoadConstructor value)
	:
Material(value)
{
}
//----------------------------------------------------------------------------
void EditTerrainMaterial::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Material::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(EditTerrainMaterial, source);
}
//----------------------------------------------------------------------------
void EditTerrainMaterial::Link (InStream& source)
{
	Material::Link(source);
}
//----------------------------------------------------------------------------
void EditTerrainMaterial::PostLink ()
{
	Material::PostLink();

	MaterialPass* pass = mTechniques[0]->GetPass(0);
	VertexShader* vshader = pass->GetVertexShader();
	PixelShader* pshader = pass->GetPixelShader();
	vshader->SetBaseRegisters(msVRegisters);
	vshader->SetPrograms(msVPrograms);
	pshader->SetBaseRegisters(msPRegisters);
	pshader->SetTextureUnits(msPTextureUnits);
	pshader->SetPrograms(msPPrograms);
}
//----------------------------------------------------------------------------
bool EditTerrainMaterial::Register (OutStream& target) const
{
	return Material::Register(target);
}
//----------------------------------------------------------------------------
void EditTerrainMaterial::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Material::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(EditTerrainMaterial, target);
}
//----------------------------------------------------------------------------
int EditTerrainMaterial::GetStreamingSize () const
{
	return Material::GetStreamingSize();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 版本
//----------------------------------------------------------------------------
int EditTerrainMaterial::msDx9VRegisters[7] = { 0, 4, 5, 6, 7, 8, 9};
int EditTerrainMaterial::msOglVRegisters[7] = { 1, 5, 6, 7, 8, 9, 10};
int EditTerrainMaterial::msOpenGLES2VRegisters[7] = { 1, 5, 6, 7, 8, 9, 10};
int* EditTerrainMaterial::msVRegisters[Shader::MAX_PROFILES] =
{
	0,
	msDx9VRegisters,
	msDx9VRegisters,
	msDx9VRegisters,
	msOglVRegisters,
	msOpenGLES2VRegisters
};

std::string EditTerrainMaterial::msVPrograms[Shader::MAX_PROFILES] =
{
	// VP_NONE
	"",

	// VP_VS_1_1
	"",

	// VP_VS_2_0
	"vs_2_0\n"
	"def c10, 1.00000000, 0.00000000, 0, 0\n"
	"dcl_position0 v0\n"
	"dcl_normal0 v1\n"
	"dcl_color0 v2\n"
	"dcl_texcoord0 v3\n"
	"mov r1.xyz, c7\n"
	"dp3 r0.w, v1, -c9\n"
	"add r0.xyz, v2, c4\n"
	"mul r1.xyz, c5, r1\n"
	"mad r1.xyz, r1, c8.w, r0\n"
	"mov r0.xyz, c7\n"
	"max r0.w, r0, c10.y\n"
	"mul r0.xyz, c6, r0\n"
	"mul r0.xyz, r0, r0.w\n"
	"mad oD0.xyz, r0, c8.w, r1\n"
	"mov r0.w, c10.x\n"
	"mov r0.xyz, v0\n"
	"dp4 oPos.w, r0, c3\n"
	"dp4 oPos.z, r0, c2\n"
	"dp4 oPos.y, r0, c1\n"
	"dp4 oPos.x, r0, c0\n"
	"mov oT0.xy, v3\n"
	"mov oD0.w, c6\n",

	// VP_VS_3_0
	"vs_3_0\n"
	"dcl_position o0\n"
	"dcl_color0 o1\n"
	"dcl_texcoord0 o2\n"
	"def c10, 1.00000000, 0.00000000, 0, 0\n"
	"dcl_position0 v0\n"
	"dcl_normal0 v1\n"
	"dcl_color0 v2\n"
	"dcl_texcoord0 v3\n"
	"mov r1.xyz, c7\n"
	"dp3 r0.w, v1, -c9\n"
	"add r0.xyz, v2, c4\n"
	"mul r1.xyz, c5, r1\n"
	"mad r1.xyz, r1, c8.w, r0\n"
	"mov r0.xyz, c7\n"
	"max r0.w, r0, c10.y\n"
	"mul r0.xyz, c6, r0\n"
	"mul r0.xyz, r0, r0.w\n"
	"mad o1.xyz, r0, c8.w, r1\n"
	"mov r0.w, c10.x\n"
	"mov r0.xyz, v0\n"
	"dp4 o0.w, r0, c3\n"
	"dp4 o0.z, r0, c2\n"
	"dp4 o0.y, r0, c1\n"
	"dp4 o0.x, r0, c0\n"
	"mov o2.xy, v3\n"
	"mov o1.w, c6\n",

	// VP_ARBVP1
	"",

	// vp_gles2
	"uniform mediump mat4 gPVWMatrix;\n"
	"uniform mediump vec4 gShineEmissive;\n"
	"uniform mediump vec4 gShineAmbient;\n"
	"uniform mediump vec4 gShineDiffuse;\n"
	"uniform mediump vec4 gLightColour;\n"
	"uniform mediump vec4 gLightAttenuation;\n"
	"uniform mediump vec4 gLightModelDirection;\n"
	"attribute mediump vec3 modelPosition;\n"
	"attribute mediump vec3 modelNormal;\n"
	"attribute mediump vec4 modelColor0;\n"
	"attribute mediump vec2 modelTCoord0;\n"
	"varying mediump vec4 vertexColor0;\n"
	"varying mediump vec2 vertexTCoord0;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = gPVWMatrix*vec4(modelPosition, 1.0);\n"
	"	vertexColor0.rgb = modelColor0.rgb + gShineEmissive.rgb"
	"		+ gLightColour.rgb*gShineAmbient.rgb*gLightAttenuation[3]"
	"		+ gLightColour.rgb*gShineDiffuse.rgb*gLightAttenuation[3]"
	"		* max(0.0, dot(modelNormal, -gLightModelDirection.xyz));\n"
	"	vertexColor0.a = gShineDiffuse.a;\n"
	"	vertexTCoord0 = vec2(modelTCoord0.x, 1.0-modelTCoord0.y);\n"
	"}\n"
};

int EditTerrainMaterial::msAllPRegisters[3] = { 0, 1, 2 };

int* EditTerrainMaterial::msPRegisters[Shader::MAX_PROFILES] =
{
	0,
	msAllPRegisters,
	msAllPRegisters,
	msAllPRegisters,
	msAllPRegisters,
	msAllPRegisters
};

int EditTerrainMaterial::msAllPTextureUnits[6] = { 0, 1, 2, 3, 4, 5};
int* EditTerrainMaterial::msPTextureUnits[Shader::MAX_PROFILES] =
{
	0,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits,
	msAllPTextureUnits
};

std::string EditTerrainMaterial::msPPrograms[Shader::MAX_PROFILES] =
{
	// PP_NONE
	"",

	// PP_PS_1_1
	"",

	// PP_PS_2_0
	"ps_2_0\n"
	"dcl_2d s0\n"
	"dcl_2d s1\n"
	"dcl_2d s2\n"
	"dcl_2d s3\n"
	"dcl_2d s4\n"
	"dcl_2d s5\n"
	"dcl t0.xy\n"
	"dcl v0\n"
	"texld r5, t0, s1\n"
	"mul r2.xy, t0, c1\n"
	"mul r4.xy, t0, c2\n"
	"mov r0.y, c0.w\n"
	"mov r0.x, c0.z\n"
	"mul r1.xy, t0, r0\n"
	"mul r0.xy, t0, c0\n"
	"mov r3.y, c1.w\n"
	"mov r3.x, c1.z\n"
	"mul r3.xy, t0, r3\n"
	"texld r4, r4, s5\n"
	"texld r3, r3, s4\n"
	"texld r2, r2, s3\n"
	"texld r0, r0, s0\n"
	"texld r1, r1, s2\n"
	"add r1, r1, -r0\n"
	"mad r0, r5.x, r1, r0\n"
	"add r1, r2, -r0\n"
	"mad r0, r5.y, r1, r0\n"
	"add r1, r3, -r0\n"
	"mad r0, r5.z, r1, r0\n"
	"add r1, r4, -r0\n"
	"mad r0, r5.w, r1, r0\n"
	"mul r0, r0, v0\n"
	"mov oC0, r0\n",

	// PP_PS_3_0
	"ps_3_0\n"
	"dcl_2d s0\n"
	"dcl_2d s1\n"
	"dcl_2d s2\n"
	"dcl_2d s3\n"
	"dcl_2d s4\n"
	"dcl_2d s5\n"
	"dcl_texcoord0 v1.xy\n"
	"dcl_color0 v0\n"
	"mul r1.xy, v1, c0\n"
	"mul r0.xy, v1, c0.zwzw\n"
	"texld r1, r1, s0\n"
	"texld r0, r0, s2\n"
	"add r2, r0, -r1\n"
	"texld r0, v1, s1\n"
	"mad r1, r0.x, r2, r1\n"
	"mul r3.xy, v1, c1\n"
	"texld r2, r3, s3\n"
	"add r2, r2, -r1\n"
	"mad r1, r0.y, r2, r1\n"
	"mul r3.xy, v1, c1.zwzw\n"
	"texld r2, r3, s4\n"
	"add r2, r2, -r1\n"
	"mad r1, r0.z, r2, r1\n"
	"mul r0.xy, v1, c2\n"
	"texld r2, r0, s5\n"
	"add r2, r2, -r1\n"
	"mad r0, r0.w, r2, r1\n"
	"mul oC0, r0, v0\n",

	// PP_ARBFP1
	"",

	// fp_gles2
	"varying mediump vec4 vertexColor0;\n"
	"varying mediump vec2 vertexTCoord0;\n"
	"uniform sampler2D Sampler0;\n"
	"uniform sampler2D SamplerAlpha;\n"
	"uniform sampler2D Sampler1;\n"
	"uniform sampler2D Sampler2;\n"
	"uniform sampler2D Sampler3;\n"
	"uniform sampler2D Sampler4;\n"
	"uniform mediump vec4 UVScale01;\n"
	"uniform mediump vec4 UVScale23;\n"
	"uniform mediump vec4 UVScale4;\n"
	"void main()\n"
	"{\n"
	"	mediump vec4 color0 = texture2D(Sampler0, vertexTCoord0*UVScale01.xy);\n"
	"	mediump vec4 colorAlpha = texture2D(SamplerAlpha, vertexTCoord0);\n"
	"	mediump vec4 color1 = texture2D(Sampler1, vertexTCoord0*UVScale01.zw);\n"
	"	mediump vec4 color2 = texture2D(Sampler2, vertexTCoord0*UVScale23.xy);\n"
	"	mediump vec4 color3 = texture2D(Sampler3, vertexTCoord0*UVScale23.zw);\n"
	"	mediump vec4 color4 = texture2D(Sampler4, vertexTCoord0*UVScale4.xy);\n"
	"	mediump vec4 lastColor = color0 + (color1-color0)*colorAlpha.r;\n"
	"	lastColor = lastColor + (color2-lastColor)*colorAlpha.g;\n"
	"	lastColor = lastColor + (color3-lastColor)*colorAlpha.b;\n"
	"	lastColor = lastColor + (color4-lastColor)*colorAlpha.a;\n"
	"	gl_FragColor = lastColor*vertexColor0;\n"
	"}\n"
};
//----------------------------------------------------------------------------