/*
*
* 文件名称	：	PX2RawTerrainPage.cpp
*
*/

#include "PX2RawTerrainPage.hpp"
#include "PX2StandardMesh.hpp"
#include "PX2VertexBufferAccessor.hpp"
#include "PX2ResourceManager.hpp"
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

PX2_IMPLEMENT_RTTI(PX2, TriMesh, RawTerrainPage);
PX2_IMPLEMENT_STREAM(RawTerrainPage);
PX2_IMPLEMENT_FACTORY(RawTerrainPage);
PX2_IMPLEMENT_DEFAULT_NAMES(TriMesh, RawTerrainPage);

//----------------------------------------------------------------------------
RawTerrainPage::RawTerrainPage (VertexFormat* vformat, int size,
	float* heights, const Float2& origin, float spacing)
	:
mSize(size),
	mSizeM1(size - 1),
	mHeights(heights),
	mOrigin(origin),
	mSpacing(spacing)
{
	// size = 2^p + 1, p <= 7
	assertion(size ==  3 || size ==  5 || size ==   9 || size == 17
		|| size == 33 || size == 65 || size == 129, "Invalid page size\n");

	mInvSpacing = 1.0f/mSpacing;

	// 创建地形页网格
	float ext = mSpacing*mSizeM1;
	TriMesh* mesh = StandardMesh(vformat).Rectangle(mSize, mSize, ext, ext);
	mVFormat = vformat;
	mVBuffer = mesh->GetVertexBuffer();
	mIBuffer = mesh->GetIndexBuffer();
	delete0(mesh);

	// 修改地形顶点数据
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
		.BlockLoad("Data/images/terrains/grass.png"));
	assertion(mTextureDefault!=0, "Load texture %s failed.\n",
		"Data/images/terrains/grass.png");
}
//----------------------------------------------------------------------------
RawTerrainPage::~RawTerrainPage ()
{
	delete1(mHeights);
}
//----------------------------------------------------------------------------
float RawTerrainPage::GetHeight (float x, float y) const
{
	float xGrid = (x - mOrigin[0])*mInvSpacing;
	if (xGrid < 0.0f || xGrid >= (float)mSizeM1)
	{
		// 方位在地形页中
		return Mathf::MAX_REAL;
	}

	float yGrid = (y - mOrigin[1])*mInvSpacing;
	if (yGrid < 0.0f || yGrid >= (float)mSizeM1)
	{
		// 方位不再地形页中
		return Mathf::MAX_REAL;
	}

	float fCol = Mathf::Floor(xGrid);
	int iCol = (int)fCol;
	float fRow = Mathf::Floor(yGrid);
	int iRow = (int)fRow;

	int index = iCol + mSize*iRow;
	float dx = xGrid - fCol;
	float dy = yGrid - fRow;
	float h00, h10, h01, h11, height;

	if ((iCol & 1) == (iRow & 1))
	{
		float diff = dx - dy;
		h00 = mHeights[index];
		h11 = mHeights[index + 1 + mSize];
		if (diff > 0.0f)
		{
			h10 = mHeights[index + 1];
			height = (1.0f - diff - dy)*h00 + diff*h10 + dy*h11;
		}
		else
		{
			h01 = mHeights[index + mSize];
			height = (1.0f + diff - dx)*h00 - diff*h01 + dx*h11;
		}
	}
	else
	{
		float sum = dx + dy;
		h10 = mHeights[index + 1];
		h01 = mHeights[index + mSize];
		if (sum <= 1.0f)
		{
			h00 = mHeights[index];
			height = (1.0f - sum)*h00 + dx*h10 + dy*h01;
		}
		else
		{
			h11 = mHeights[index + 1 + mSize];
			height = (sum - 1.0f)*h11 + (1.0f - dy)*h10 + (1.0f - dx)*h01;
		}
	}

	return height;
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
	mMaterialInstance->SetPixelTexture(0, "Sampler0", mTexture0);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTextureAlpha (Texture2D *texture)
{
	mTextureAlpha = texture;
	mMaterialInstance->SetPixelTexture(0, "SamplerAlpha", mTextureAlpha);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTexture1 (Texture2D *texture)
{
	mTexture1 = texture;
	if (!mTexture1->HasMipmaps())
		mTexture1->GenerateMipmaps();
	mMaterialInstance->SetPixelTexture(0, "Sampler1", mTexture1);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTexture2 (Texture2D *texture)
{
	mTexture2 = texture;
	if (!mTexture2->HasMipmaps())
		mTexture2->GenerateMipmaps();
	mMaterialInstance->SetPixelTexture(0, "Sampler2", mTexture2);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTexture3 (Texture2D *texture)
{
	mTexture3 = texture;
	if (!mTexture3->HasMipmaps())
		mTexture3->GenerateMipmaps();
	mMaterialInstance->SetPixelTexture(0, "Sampler3", mTexture3);
}
//----------------------------------------------------------------------------
void RawTerrainPage::SetTexture4 (Texture2D *texture)
{
	mTexture4 = texture;
	if (!mTexture4->HasMipmaps())
		mTexture4->GenerateMipmaps();
	mMaterialInstance->SetPixelTexture(0, "Sampler4", mTexture4);
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
void RawTerrainPage::CreateInstancePerVertex (EditTerrainMaterial *material, 
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
		light->SetDirection(AVector(-1.0f, -1.0f, -1.0f));
	}

	mMaterialInstance = new0 MaterialInstance(material, 0);
	mMaterialInstance->SetVertexConstant(0, "gPVWMatrix", new0 PVWMatrixConstant());

	mMaterialInstance->SetVertexConstant(0, "gShineEmissive",
		new0 ShineEmissiveConstant(shine));
	mMaterialInstance->SetVertexConstant(0, "gShineAmbient",
		new0 ShineAmbientConstant(shine));
	mMaterialInstance->SetVertexConstant(0, "gShineDiffuse",
		new0 ShineDiffuseConstant(shine));
	mMaterialInstance->SetVertexConstant(0, "gLightModelDirection",
		new0 LightModelDVectorConstant(light));
	mMaterialInstance->SetVertexConstant(0, "gLightColour",
		new0 LightDiffuseConstant(light));

	mMaterialInstance->SetPixelConstant(0, "UVScale01", mUV01Float);
	mMaterialInstance->SetPixelConstant(0, "UVScale23", mUV23Float);
	mMaterialInstance->SetPixelConstant(0, "UVScale4", mUV4Float);

	SetTexture0(mTextureDefault);
	SetTextureAlpha(mTextureAlpha);
	SetTexture1(mTextureDefault);
	SetTexture2(mTextureDefault);
	SetTexture3(mTextureDefault);
	SetTexture4(mTextureDefault);

	SetMaterialInstance(mMaterialInstance);
}
//----------------------------------------------------------------------------
void RawTerrainPage::CreateInstancePerPixel (EditTerrainMaterial *material,
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
		light->SetDirection(AVector(-1.0f, -1.0f, -1.0f));
	}

	mMaterialInstance = new0 MaterialInstance(material, 0);
	mMaterialInstance->SetVertexConstant(0, "gPVWMatrix", new0 PVWMatrixConstant());
	mMaterialInstance->SetVertexConstant(0, "gShineEmissive",
		new0 ShineEmissiveConstant(shine));
	mMaterialInstance->SetVertexConstant(0, "gShineAmbient",
		new0 ShineAmbientConstant(shine));
	mMaterialInstance->SetVertexConstant(0, "gShineDiffuse",
		new0 ShineDiffuseConstant(shine));
	mDirLight = light;
	mMaterialInstance->SetVertexConstant(0, "gLightModelDirection",
		new0 LightModelDVectorConstant(light));
	mMaterialInstance->SetVertexConstant(0, "gLightColour",
		new0 LightDiffuseConstant(light));

	mMaterialInstance->SetPixelConstant(0, "UVScale01", mUV01Float);
	mMaterialInstance->SetPixelConstant(0, "UVScale23", mUV23Float);
	mMaterialInstance->SetPixelConstant(0, "UVScale4", mUV4Float);

	SetTexture0(mTextureDefault);
	SetTextureAlpha(mTextureAlpha);
	SetTexture1(mTextureDefault);
	SetTexture2(mTextureDefault);
	SetTexture3(mTextureDefault);
	SetTexture4(mTextureDefault);

	SetMaterialInstance(mMaterialInstance);
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

		mMaterialInstance->SetVertexConstant(0, "gLightModelDirection",
			new0 LightModelDVectorConstant(mDirLight));
		mMaterialInstance->SetVertexConstant(0, "gLightColour",
			new0 LightDiffuseConstant(mDirLight));
	}

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
RawTerrainPage::RawTerrainPage (LoadConstructor value)
	:
TriMesh(value),
	mSize(0),
	mSizeM1(0),
	mHeights(0),
	mOrigin(Float2(0.0f, 0.0f)),
	mSpacing(0.0f),
	mInvSpacing(0.0f)
{
}
//----------------------------------------------------------------------------
void RawTerrainPage::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TriMesh::Load(source);

	source.Read(mSize);
	int numVertices = mSize*mSize;
	source.ReadVR(numVertices, mHeights);
	source.ReadAggregate(mOrigin);
	source.Read(mSpacing);

	mSizeM1 = mSize - 1;
	mInvSpacing = 1.0f/mSpacing;

	source.ReadPointer(mMaterialInstance);
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
	TriMesh::Link(source);

	source.ResolveLink(mMaterialInstance);
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
	TriMesh::PostLink();
}
//----------------------------------------------------------------------------
bool RawTerrainPage::Register (OutStream& target) const
{
	return TriMesh::Register(target);
}
//----------------------------------------------------------------------------
void RawTerrainPage::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TriMesh::Save(target);

	target.Write(mSize);
	int numVertices = mSize*mSize;
	target.WriteN(numVertices, mHeights);
	target.WriteAggregate(mOrigin);
	target.Write(mSpacing);

	target.WritePointer(mMaterialInstance);
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
	int size = TriMesh::GetStreamingSize();
	size += sizeof(mSize);
	size += mSize*mSize*sizeof(mHeights[0]);
	size += sizeof(mOrigin);
	size += sizeof(mSpacing);
	size += PX2_POINTERSIZE(mMaterialInstance) * 8;
	size += sizeof(mUV01);
	size += sizeof(mUV23);
	size += sizeof(mUV4);
	size += PX2_POINTERSIZE(mUV01Float);
	size += PX2_POINTERSIZE(mUV23Float);
	size += PX2_POINTERSIZE(mUV4Float);

	return size;
}
//----------------------------------------------------------------------------
