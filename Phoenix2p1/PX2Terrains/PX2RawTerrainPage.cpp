/*
*
* 文件名称	：	PX2RawTerrainPage.cpp
*
*/

#include "PX2RawTerrainPage.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2StandardMesh.hpp"
#include "PX2VertexBufferAccessor.hpp"
#include "PX2EditTerrainMaterial.hpp"
#include "PX2CameraModelPositionConstant.hpp"
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

PX2_IMPLEMENT_RTTI(PX2, TerrainPage, RawTerrainPage);
PX2_IMPLEMENT_STREAM(RawTerrainPage);
PX2_IMPLEMENT_FACTORY(RawTerrainPage);
PX2_IMPLEMENT_DEFAULT_NAMES(TerrainPage, RawTerrainPage);

//----------------------------------------------------------------------------
RawTerrainPage::RawTerrainPage (VertexFormat* vformat, int size,
	float* heights, const Float2& origin, float spacing)
	:
TerrainPage(size, heights, origin, spacing)
{
	float ext = mSpacing*mSizeM1;
	TriMesh* mesh = StandardMesh(vformat).Rectangle(mSize, mSize, ext, ext);
	mVFormat = vformat;
	mVBuffer = mesh->GetVertexBuffer();
	mIBuffer = mesh->GetIndexBuffer();
	delete0(mesh);

	VertexBufferAccessor vba(mVFormat, mVBuffer);
	int numVertices = mVBuffer->GetNumElements();
	for (int i = 0; i < numVertices; ++i)
	{
		int x = i % mSize;
		int y = i / mSize;
		vba.Position<Float3>(i) = Float3(GetX(x), GetY(y), GetHeight(i));
		vba.Normal<Float3>(i) = Float3(0.0f, 0.0f, 1.0f);
		vba.Color<Float3>(0, i) = Float3(0.0f, 0.0f, 0.0f);
	}

	UpdateModelSpace(Renderable::GU_NORMALS);

	mUV01 = Float4(8.0f, 8.0f, 8.0f, 8.0f);
	mUV23 = Float4(8.0f, 8.0f, 8.0f, 8.0f);
	mUV4 = Float4(8.0f, 8.0f, 8.0f, 8.0f);

	mUV01Float = new0 ShaderFloat(1);
	mUV23Float = new0 ShaderFloat(1);
	mUV4Float = new0 ShaderFloat(1);

	SetUV0(Float2(mUV01[0], mUV01[1]));
	SetUV1(Float2(mUV01[2], mUV01[3]));
	SetUV2(Float2(mUV23[0], mUV23[1]));
	SetUV3(Float2(mUV23[2], mUV23[3]));
	SetUV4(Float2(mUV4[0], mUV4[1]));

	mTextureAlpha = new0 Texture2D(Texture::TF_A8R8G8B8, mSize, mSize, 1);
	mTextureDefault = DynamicCast<Texture2D>(ResourceManager::GetSingleton()
		.BlockLoad("Data/engine/grass.png"));
}
//----------------------------------------------------------------------------
RawTerrainPage::~RawTerrainPage ()
{
}
//----------------------------------------------------------------------------
void RawTerrainPage::UpdateToHighField ()
{
	int vertexNum = GetVertexBuffer()->GetNumElements();

	VertexBufferAccessor vba(this);

	for (int i=0; i<vertexNum; i++)
	{
		float height = vba.Position<Float3>(i)[2];
		mHeights[i] = height;
	}

	UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTexture (int index, Texture2D *texture)
{
	assertion(index>=0 && index<=4, "index must in right range.");

	switch (index)
	{
	case 0:
		return SetTexture0(texture);
	case 1:
		return SetTexture1(texture);
	case 2:
		return SetTexture2(texture);
	case 3:
		return SetTexture3(texture);
	case 4:
		return SetTexture4(texture);
	default:
		break;
	}
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTexture0 (Texture2D *texture)
{
	mTexture0 = texture;
	if (!mTexture0->HasMipmaps())
		mTexture0->GenerateMipmaps();
	mMtlInst->SetPixelTexture(0, "Sampler0", mTexture0);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTextureAlpha (Texture2D *texture)
{
	mTextureAlpha = texture;
	mMtlInst->SetPixelTexture(0, "SamplerAlpha", mTextureAlpha);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTexture1 (Texture2D *texture)
{
	mTexture1 = texture;
	if (!mTexture1->HasMipmaps())
		mTexture1->GenerateMipmaps();
	mMtlInst->SetPixelTexture(0, "Sampler1", mTexture1);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTexture2 (Texture2D *texture)
{
	mTexture2 = texture;
	if (!mTexture2->HasMipmaps())
		mTexture2->GenerateMipmaps();
	mMtlInst->SetPixelTexture(0, "Sampler2", mTexture2);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTexture3 (Texture2D *texture)
{
	mTexture3 = texture;
	if (!mTexture3->HasMipmaps())
		mTexture3->GenerateMipmaps();
	mMtlInst->SetPixelTexture(0, "Sampler3", mTexture3);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTexture4 (Texture2D *texture)
{
	mTexture4 = texture;
	if (!mTexture4->HasMipmaps())
		mTexture4->GenerateMipmaps();
	mMtlInst->SetPixelTexture(0, "Sampler4", mTexture4);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetUV (int index, Float2 uv)
{
	assertion(index>=0 && index<=4, "index must in right range.");

	switch (index)
	{
	case 0:
		return SetUV0(uv);
	case 1:
		return SetUV1(uv);
	case 2:
		return SetUV2(uv);
	case 3:
		return SetUV3(uv);
	case 4:
		return SetUV4(uv);
	default:
		break;
	}
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetUV0 (Float2 uv)
{
	mUV01[0] = uv[0];
	mUV01[1] = uv[1];
	mUV01Float->SetRegister(0, (float*)&mUV01);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetUV1 (Float2 uv)
{
	mUV01[2] = uv[0];
	mUV01[3] = uv[1];
	mUV01Float->SetRegister(0, (float*)&mUV01);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetUV2 (Float2 uv)
{
	mUV23[0] = uv[0];
	mUV23[1] = uv[1];
	mUV23Float->SetRegister(0, (float*)&mUV23);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetUV3 (Float2 uv)
{
	mUV23[2] = uv[0];
	mUV23[3] = uv[1];
	mUV23Float->SetRegister(0, (float*)&mUV23);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetUV4 (Float2 uv)
{
	mUV4[0] = uv[0];
	mUV4[1] = uv[1];
	mUV4Float->SetRegister(0, (float*)&mUV4);
}
//----------------------------------------------------------------------------
Float2 RawTerrainPage::GetUV (int index)
{
	assertion(index>=0 && index<=4, "index must in right range.");

	switch (index)
	{
	case 0:
		return GetUV0();
	case 1:
		return GetUV1();
	case 2:
		return GetUV2();
	case 3:
		return GetUV3();
	case 4:
		return GetUV4();
	default:
		break;
	}

	return Float2();
}
//----------------------------------------------------------------------------
void RawTerrainPage::CreateEditMtlInstPerVertex (EditTerrainMaterial *material, 
	Shine *shine)
{
	PX2::Light *light = 0;
	for (int i=0; i<(int)mInfulencedLights.size(); i++)
	{
		Light *lit = mInfulencedLights[i];
		if (lit->GetType() == Light::LT_DIRECTIONAL)
		{
			light = lit;
			break;
		}
	}

	if (light == 0)
	{
		light = new0 Light(Light::LT_DIRECTIONAL);
		light->Ambient = Float4(1.0f, 0.8f, 0.8f, 1.0f);
		light->Diffuse = Float4(1.0f, 0.8f, 0.6f, 1.0f);
		light->Intensity = 1.0f;
		light->SetDirection(AVector(-1.0f, -1.0f, -1.0f));
	}

	mMtlInst = new0 MaterialInstance(material, 0);
	mMtlInst->SetVertexConstant(0, "gPVWMatrix", new0 PVWMatrixConstant());

	mMtlInst->SetVertexConstant(0, "gShineEmissive",
		new0 ShineEmissiveConstant(shine));
	mMtlInst->SetVertexConstant(0, "gShineAmbient",
		new0 ShineAmbientConstant(shine));
	mMtlInst->SetVertexConstant(0, "gShineDiffuse",
		new0 ShineDiffuseConstant(shine));
	mMtlInst->SetVertexConstant(0, "gLightModelDirection",
		new0 LightModelDVectorConstant(light));
	mMtlInst->SetVertexConstant(0, "gLightColour",
		new0 LightDiffuseConstant(light));
	mMtlInst->SetVertexConstant(0, "gLightAttenuation",
		new0 LightAttenuationConstant(light));

	mMtlInst->SetPixelConstant(0, "UVScale01", mUV01Float);
	mMtlInst->SetPixelConstant(0, "UVScale23", mUV23Float);
	mMtlInst->SetPixelConstant(0, "UVScale4", mUV4Float);

	SetTexture0(mTextureDefault);
	SetTextureAlpha(mTextureAlpha);
	SetTexture1(mTextureDefault);
	SetTexture2(mTextureDefault);
	SetTexture3(mTextureDefault);
	SetTexture4(mTextureDefault);

	SetMaterialInstance(mMtlInst);
}
//----------------------------------------------------------------------------
void RawTerrainPage::CreateSimpleMtlInstPerVertex (
	EditTerrainMaterial *material, Shine *shine)
{

}
//----------------------------------------------------------------------------
void RawTerrainPage::UpdateWorldData (double applicationTime)
{
	TriMesh::UpdateWorldData(applicationTime);

	PX2::Light *light = 0;
	for (int i=0; i<(int)mInfulencedLights.size(); i++)
	{
		Light *lit = mInfulencedLights[i];
		if (lit->GetType() == Light::LT_DIRECTIONAL)
		{
			light = lit;
			break;
		}
	}

	if (light!=0 && light!=mDirLight)
	{
		mDirLight = light;

		mMtlInst->SetVertexConstant(0, "gLightModelDirection",
			new0 LightModelDVectorConstant(mDirLight));
		mMtlInst->SetVertexConstant(0, "gLightColour",
			new0 LightDiffuseConstant(mDirLight));
		mMtlInst->SetVertexConstant(0, "gLightAttenuation",
			new0 LightAttenuationConstant(mDirLight));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
RawTerrainPage::RawTerrainPage (LoadConstructor value)
	:
TerrainPage(value)
{
}
//----------------------------------------------------------------------------
void RawTerrainPage::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TerrainPage::Load(source);

	source.ReadPointer(mMtlInst);
	source.ReadPointer(mTextureDefault);
	source.ReadPointer(mTexture0);
	source.ReadPointer(mTextureAlpha);
	source.ReadPointer(mTexture1);
	source.ReadPointer(mTexture2);
	source.ReadPointer(mTexture3);
	source.ReadPointer(mTexture4);
	source.ReadAggregate(mUV01);
	source.ReadAggregate(mUV23);
	source.ReadAggregate(mUV4);
	source.ReadPointer(mUV01Float);
	source.ReadPointer(mUV23Float);
	source.ReadPointer(mUV4Float);

	PX2_END_DEBUG_STREAM_LOAD(RawTerrainPage, source);
}
//----------------------------------------------------------------------------
void RawTerrainPage::Link (InStream& source)
{
	TerrainPage::Link(source);

	source.ResolveLink(mMtlInst);
	source.ResolveLink(mTextureDefault);
	source.ResolveLink(mTexture0);
	source.ResolveLink(mTextureAlpha);
	source.ResolveLink(mTexture1);
	source.ResolveLink(mTexture2);
	source.ResolveLink(mTexture3);
	source.ResolveLink(mTexture4);
	source.ResolveLink(mUV01Float);
	source.ResolveLink(mUV23Float);
	source.ResolveLink(mUV4Float);
}
//----------------------------------------------------------------------------
void RawTerrainPage::PostLink ()
{
	TerrainPage::PostLink();
}
//----------------------------------------------------------------------------
bool RawTerrainPage::Register (OutStream& target) const
{
	return TerrainPage::Register(target);
}
//----------------------------------------------------------------------------
void RawTerrainPage::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TerrainPage::Save(target);

	target.WritePointer(mMtlInst);
	target.WritePointer(mTextureDefault);
	target.WritePointer(mTexture0);
	target.WritePointer(mTextureAlpha);
	target.WritePointer(mTexture1);
	target.WritePointer(mTexture2);
	target.WritePointer(mTexture3);
	target.WritePointer(mTexture4);
	target.WriteAggregate(mUV01);
	target.WriteAggregate(mUV23);
	target.WriteAggregate(mUV4);
	target.WritePointer(mUV01Float);
	target.WritePointer(mUV23Float);
	target.WritePointer(mUV4Float);

	PX2_END_DEBUG_STREAM_SAVE(RawTerrainPage, target);
}
//----------------------------------------------------------------------------
int RawTerrainPage::GetStreamingSize () const
{
	int size = TerrainPage::GetStreamingSize();
	size += PX2_POINTERSIZE(mMtlInst) * 8;
	size += sizeof(mUV01);
	size += sizeof(mUV23);
	size += sizeof(mUV4);
	size += PX2_POINTERSIZE(mUV01Float);
	size += PX2_POINTERSIZE(mUV23Float);
	size += PX2_POINTERSIZE(mUV4Float);

	return size;
}
//----------------------------------------------------------------------------
