/*
*
* 文件名称	：	PX2UIPicBox.cpp
*
*/

#include "PX2UIPicBox.hpp"
#include "PX2Renderer.hpp"
#include "PX2UIManager.hpp"
#include "PX2UIFrame.hpp"
#include "PX2ResourceManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, TriMesh, UIPicBox);
PX2_IMPLEMENT_STREAM(UIPicBox);
PX2_IMPLEMENT_FACTORY(UIPicBox);

//----------------------------------------------------------------------------
UIPicBox::UIPicBox (std::string filename)
	:
mPicBoxType(PBT_MAX_TYPE),
mIsDynamic(false),
mAnchorPoint(0.0f, 0.0f),
mSize(128, 64),
mCorSize(6, 6),
mUV0(0.0f, 0.0f),
mUV1(1.0f, 0.0f),
mUV2(0.0f, 1.0f),
mUV3(1.0f, 1.0f),
mColor(Float4::WHITE)
{
	SetName("UIPicBox");
	
	SetRenderLayer(Renderable::RL_FRONT);

	SetPicBoxType(PBT_NORMAL);

	mUIMtl = UIManager::GetSingleton().GetUIMaterial();
	Object *obj = PX2_RM.BlockLoad(filename);
	Texture2D *tex = DynamicCast<Texture2D>(obj);
	SetTexture(tex);
	if (tex)
	{
		float texWidth = (float)tex->GetWidth();
		float texHeight = (float)tex->GetHeight();
		SetSize(texWidth, texHeight);
	}
}
//----------------------------------------------------------------------------
UIPicBox::~UIPicBox ()
{
}
//----------------------------------------------------------------------------
void UIPicBox::SetPicBoxType (PicBoxType type)
{
	mPicBoxType = type;

	VertexFormat *vFormat = UIManager::GetSingleton().GetVertexFormat();
	SetVertexFormat(vFormat);

	int numVertex = 4;
	int numIndex = 6;

	if (PBT_NORMAL == mPicBoxType)
	{
		numVertex = 4;
		numIndex = 6;
	}
	else if (PBT_NINE == mPicBoxType)
	{
		numVertex = 16;
		numIndex = 54;
	}

	VertexBuffer *vBuffer = new0 VertexBuffer(numVertex, vFormat->GetStride(),
		mIsDynamic ? Buffer::BU_DYNAMIC : Buffer::BU_STATIC);
	IndexBuffer *iBuffer = new0 IndexBuffer(numIndex, 2);
	SetVertexBuffer(vBuffer);
	SetIndexBuffer(iBuffer);

	UpdateBuffers();
}
//----------------------------------------------------------------------------
void UIPicBox::SetDynamic (bool dyn)
{
	mIsDynamic = dyn;
	SetPicBoxType(mPicBoxType);
}
//----------------------------------------------------------------------------
void UIPicBox::SetAnchorPoint (Float2 anchor)
{
	mAnchorPoint = anchor;
	UpdateBuffers();
}
//----------------------------------------------------------------------------
void UIPicBox::SetSize (float width, float height)
{
	mSize.Width = width;
	mSize.Height = height;

	UpdateBuffers();
}
//----------------------------------------------------------------------------
void UIPicBox::SetSize (const Sizef &size)
{
	mSize = size;

	UpdateBuffers();
}
//----------------------------------------------------------------------------
void UIPicBox::SetWidth (float width)
{
	mSize.Width = width;

	UpdateBuffers();
}
//----------------------------------------------------------------------------
void UIPicBox::SetHeight (float height)
{
	mSize.Height = height;

	UpdateBuffers();
}
//----------------------------------------------------------------------------
void UIPicBox::SetColor (Float3 color)
{
	mColor[0] = color[0];
	mColor[1] = color[1];
	mColor[2] = color[2];

	UpdateBuffers();
}
//----------------------------------------------------------------------------
void UIPicBox::SetAlpha (float alpha)
{
	mColor[3] = alpha;

	UpdateBuffers();
}
//----------------------------------------------------------------------------
void UIPicBox::SetTexture (Texture2D *tex)
{
	mTexture = tex;

	if (!mUIMtlInst)
	{
		mUIMtlInst = mUIMtl->CreateInstance(mTexture);
		SetMaterialInstance(mUIMtlInst);
	}
	else
	{
		mUIMtlInst->SetPixelTexture(0, "gDiffuseSampler", mTexture);
	}
}
//----------------------------------------------------------------------------
void UIPicBox::SetTexture (const std::string &filename)
{
	Object *obj = ResourceManager::GetSingleton().BlockLoad(filename);
	Texture2D *tex = DynamicCast<Texture2D>(obj);
	
	if (tex)
	{
		SetTexture(tex);
	}
}
//----------------------------------------------------------------------------
void UIPicBox::SetTexture (const std::string &texPackName, std::string eleName)
{
	ResourceManager::GetSingleton().AddTexPack(texPackName);
	mPackEle = 
		ResourceManager::GetSingleton().GetTexPackElement(texPackName, eleName);

	if (!mPackEle.IsValid())
		return;

	Object *obj = ResourceManager::GetSingleton().BlockLoad(
		mPackEle.ImagePathFull);
	Texture2D *tex = DynamicCast<Texture2D>(obj);

	if (tex)
	{
		mTexture = tex;

		float u0 = (float)mPackEle.X/(float)mPackEle.TexWidth;
		float u1 = (float)(mPackEle.X+mPackEle.W)/(float)mPackEle.TexWidth;
		float v0 = (float)(mPackEle.TexHeight-mPackEle.Y-mPackEle.H)/(float)mPackEle.TexHeight;
		float v1 = (float)(mPackEle.TexHeight-mPackEle.Y)/(float)mPackEle.TexHeight;

		if (PBT_NORMAL == mPicBoxType)
		{
			if (!mPackEle.Rolated)
			{
				mUV0 = Float2(u0, v0);
				mUV1 = Float2(u1, v0);
				mUV2 = Float2(u0, v1);
				mUV3 = Float2(u1, v1);
			}
			else
			{
				mUV0 = Float2(u0, v1);
				mUV1 = Float2(u0, v0);
				mUV2 = Float2(u1, v1);
				mUV3 = Float2(u1, v0);
			}
		}
		else
		{
			mUV0 = Float2(u0, v0);
			mUV1 = Float2(u1, v0);
			mUV2 = Float2(u0, v1);
			mUV3 = Float2(u1, v1);
		}

		SetTexture(mTexture);

		UpdateBuffers();
	}
}
//----------------------------------------------------------------------------
void UIPicBox::SetDoubleSide (bool d)
{
	if (d)
	{
		mUIMtl = UIManager::GetSingleton().GetUIMaterialDoubleSide();
		SetMaterialInstance(mUIMtl->CreateInstance(mTexture));
	}
	else
	{
		mUIMtl = UIManager::GetSingleton().GetUIMaterial();
		SetMaterialInstance(mUIMtl->CreateInstance(mTexture));
	}
}
//----------------------------------------------------------------------------
bool UIPicBox::IsDoubleSide ()
{
	return (mUIMtl==UIManager::GetSingleton().GetUIMaterialDoubleSide());
}
//----------------------------------------------------------------------------
void UIPicBox::SetTexCornorSize (float width, float height)
{
	mCorSize.Width = width;
	mCorSize.Height = height;

	if (mPicBoxType == PBT_NINE)
	{
		UpdateBuffers();
	}
}
//----------------------------------------------------------------------------
void UIPicBox::SetTexCornorSize (const Sizef &size)
{
	mCorSize = size;

	if (mPicBoxType == PBT_NINE)
	{
		UpdateBuffers();
	}
}
//----------------------------------------------------------------------------
void UIPicBox::SetTexCornerWidth (float width)
{
	mCorSize.Width = width;

	if (mPicBoxType == PBT_NINE)
	{
		UpdateBuffers();
	}
}
//----------------------------------------------------------------------------
void UIPicBox::SetTexCornerHeight (float height)
{
	mCorSize.Height = height;

	if (mPicBoxType == PBT_NINE)
	{
		UpdateBuffers();
	}
}
//----------------------------------------------------------------------------
void UIPicBox::UpdateBuffers ()
{
	UpdateVertexBuffer();
	UpdateIndexBuffer();
}
//----------------------------------------------------------------------------
void UIPicBox::UpdateVertexBuffer ()
{
	VertexBufferAccessor vba(GetVertexFormat(), GetVertexBuffer());

	float anchorWidth = mAnchorPoint[0]*mSize.Width;
	float anchorHeight = mAnchorPoint[1]*mSize.Height;

	if (PBT_NORMAL == mPicBoxType)
	{
		vba.Position<Float3>(0) = Float3(0.0f-anchorWidth, 0.0f, 0.0f-anchorHeight);
		vba.Position<Float3>(1) = Float3(mSize.Width-anchorWidth, 0.0f, 0.0f-anchorHeight);
		vba.Position<Float3>(2) = Float3(0.0f-anchorWidth, 0.0f, mSize.Height-anchorHeight);
		vba.Position<Float3>(3) = Float3(mSize.Width-anchorWidth, 0.0f, mSize.Height-anchorHeight);

		vba.Color<Float4>(0, 0) = mColor;
		vba.Color<Float4>(0, 1) = mColor;
		vba.Color<Float4>(0, 2) = mColor;
		vba.Color<Float4>(0, 3) = mColor;
		vba.TCoord<Float2>(0, 0) = mUV0;
		vba.TCoord<Float2>(0, 1) = mUV1;
		vba.TCoord<Float2>(0, 2) = mUV2;
		vba.TCoord<Float2>(0, 3) = mUV3;
	}
	else if (PBT_NINE == mPicBoxType)
	{
		float texWidth = 32;
		float texHeight = 32;

		if (mTexture)
		{
			texWidth = (float)mTexture->GetWidth();
			texHeight = (float)mTexture->GetHeight();
		}

		float corW = mCorSize.Width/texWidth;
		float corH = mCorSize.Height/texHeight;

		float u0 = mUV0[0];
		float u1 = mUV0[0] + corW;
		float u2 = mUV1[0] - corW;
		float u3 = mUV1[0];
		float v0 = mUV0[1];
		float v1 = mUV0[1] + corH;
		float v2 = mUV2[1] - corH;
		float v3 = mUV2[1];

		Float2 uv[16];
		if (!mPackEle.Rolated)
		{
			uv[0] = Float2(u0, v0);
			uv[1] = Float2(u1, v0);
			uv[2] = Float2(u2, v0);
			uv[3] = Float2(u3, v0);
			uv[4] = Float2(u0, v1);
			uv[5] = Float2(u1, v1);
			uv[6] = Float2(u2, v1);
			uv[7] = Float2(u3, v1);
			uv[8] = Float2(u0, v2);
			uv[9] = Float2(u1, v2);
			uv[10] = Float2(u2, v2);
			uv[11] = Float2(u3, v2);
			uv[12] = Float2(u0, v3);
			uv[13] = Float2(u1, v3);
			uv[14] = Float2(u2, v3);
			uv[15] = Float2(u3, v3);
		}
		else
		{
			uv[0] = Float2(u0, v3);
			uv[1] = Float2(u0, v2);
			uv[2] = Float2(u0, v1);
			uv[3] = Float2(u0, v0);

			uv[4] = Float2(u1, v3);
			uv[5] = Float2(u1, v2);
			uv[6] = Float2(u1, v1);
			uv[7] = Float2(u1, v0);

			uv[8] = Float2(u2, v3);
			uv[9] = Float2(u2, v2);
			uv[10] = Float2(u2, v1);
			uv[11] = Float2(u2, v0);

			uv[12] = Float2(u3, v3);
			uv[13] = Float2(u3, v2);
			uv[14] = Float2(u3, v1);
			uv[15] = Float2(u3, v0);
		}

		vba.Position<Float3>(0) = Float3(0.0f-anchorWidth, 0.0f, 0.0f-anchorHeight);
		vba.TCoord<Float2>(0, 0) = uv[0];
		vba.Position<Float3>(1) = Float3(mCorSize.Width-anchorWidth, 0.0f, 0.0f-anchorHeight);
		vba.TCoord<Float2>(0, 1) = uv[1];
		vba.Position<Float3>(2) = Float3(mSize.Width-mCorSize.Width-anchorWidth, 0.0f, 0.0f-anchorHeight);
		vba.TCoord<Float2>(0, 2) = uv[2];
		vba.Position<Float3>(3) = Float3(mSize.Width-anchorWidth, 0.0f, 0.0f-anchorHeight);
		vba.TCoord<Float2>(0, 3) = uv[3];
		vba.Position<Float3>(4) = Float3(0.0f-anchorWidth, 0.0f, mCorSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 4) = uv[4];
		vba.Position<Float3>(5) = Float3(mCorSize.Width-anchorWidth, 0.0f, mCorSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 5) = uv[5];
		vba.Position<Float3>(6) = Float3(mSize.Width-mCorSize.Width-anchorWidth, 0.0f, mCorSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 6) = uv[6];
		vba.Position<Float3>(7) = Float3(mSize.Width-anchorWidth, 0.0f, mCorSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 7) = uv[7];
		vba.Position<Float3>(8) = Float3(0.0f-anchorWidth, 0.0f, mSize.Height-mCorSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 8) = uv[8];
		vba.Position<Float3>(9) = Float3(mCorSize.Width-anchorWidth, 0.0f, mSize.Height-mCorSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 9) = uv[9];
		vba.Position<Float3>(10) = Float3(mSize.Width-mCorSize.Width-anchorWidth, 0.0f, mSize.Height-mCorSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 10) = uv[10];
		vba.Position<Float3>(11) = Float3(mSize.Width-anchorWidth, 0.0f, mSize.Height-mCorSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 11) = uv[11];
		vba.Position<Float3>(12) = Float3(0.0f-anchorWidth, 0.0f, mSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 12) = uv[12];
		vba.Position<Float3>(13) = Float3(mCorSize.Width-anchorWidth, 0.0f, mSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 13) = uv[13];
		vba.Position<Float3>(14) = Float3(mSize.Width-mCorSize.Width-anchorWidth, 0.0f, mSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 14) = uv[14];
		vba.Position<Float3>(15) = Float3(mSize.Width-anchorWidth, 0.0f, mSize.Height-anchorHeight);
		vba.TCoord<Float2>(0, 15) = uv[15];
		vba.Color<Float4>(0, 0) = mColor;
		vba.Color<Float4>(0, 1) = mColor;
		vba.Color<Float4>(0, 2) = mColor;
		vba.Color<Float4>(0, 3) = mColor;
		vba.Color<Float4>(0, 4) = mColor;
		vba.Color<Float4>(0, 5) = mColor;
		vba.Color<Float4>(0, 6) = mColor;
		vba.Color<Float4>(0, 7) = mColor;
		vba.Color<Float4>(0, 8) = mColor;
		vba.Color<Float4>(0, 9) = mColor;
		vba.Color<Float4>(0, 10) = mColor;
		vba.Color<Float4>(0, 11) = mColor;
		vba.Color<Float4>(0, 12) = mColor;
		vba.Color<Float4>(0, 13) = mColor;
		vba.Color<Float4>(0, 14) = mColor;
		vba.Color<Float4>(0, 15) = mColor;
	}

	UpdateModelSpace(GU_MODEL_BOUND_ONLY);
	Renderer::UpdateAll(GetVertexBuffer());
}
//----------------------------------------------------------------------------
void UIPicBox::UpdateIndexBuffer ()
{
	unsigned short *indices = (unsigned short*)GetIndexBuffer()->GetData();
	if (PBT_NORMAL == mPicBoxType)
	{
		unsigned short v0 = 0;
		unsigned short v1 = 1;
		unsigned short v2 = 2;
		unsigned short v3 = 3;

		*indices++ = v0;
		*indices++ = v1;
		*indices++ = v2;
		*indices++ = v1;
		*indices++ = v3;
		*indices++ = v2;
	}
	else if (PBT_NINE == mPicBoxType)
	{
		for (unsigned short j=0; j<3; j++)
		{
			for (unsigned short i=0; i<3; i++)
			{
				unsigned short v0 = i + 4 * j;
				unsigned short v1 = v0 + 1;
				unsigned short v2 = v0 + 4;
				unsigned short v3 = v1 + 4;

				*indices++ = v0;
				*indices++ = v1;
				*indices++ = v2;
				*indices++ = v1;
				*indices++ = v3;
				*indices++ = v2;
			}
		}
	}

	UpdateModelSpace(GU_MODEL_BOUND_ONLY);
	Renderer::UpdateAll(GetIndexBuffer());
}
//----------------------------------------------------------------------------
void UIPicBox::OnPicked (int info)
{
	UIFrame *frame = DynamicCast<UIFrame>(GetParent());
	if (frame)
	{
		frame->OnChildPicked(info, this);
	}
}
//----------------------------------------------------------------------------
void UIPicBox::UIAfterPicked (int info)
{
	UIFrame *frame = DynamicCast<UIFrame>(GetParent());
	if (frame)
	{
		frame->OnChildUIAfterPicked(info, this);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* UIPicBox::GetObjectByName (const std::string& name)
{
	Object* found = TriMesh::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mUIMtl, name, found);
	PX2_GET_OBJECT_BY_NAME(mTexture, name, found);

	return 0;
}
//----------------------------------------------------------------------------
void UIPicBox::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	TriMesh::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mUIMtl, name, objects);
	PX2_GET_ALL_OBJECTS_BY_NAME(mTexture, name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIPicBox::UIPicBox (LoadConstructor value)
	:
TriMesh(value)
{
}
//----------------------------------------------------------------------------
void UIPicBox::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TriMesh::Load(source);

	source.ReadEnum(mPicBoxType);
	source.ReadBool(mIsDynamic);
	source.ReadAggregate(mAnchorPoint),
	source.ReadAggregate(mSize);
	source.ReadAggregate(mCorSize);
	source.ReadAggregate(mUV0);
	source.ReadAggregate(mUV1);
	source.ReadAggregate(mUV2);
	source.ReadAggregate(mUV3);
	source.ReadAggregate(mColor);
	source.ReadPointer(mUIMtl);
	source.ReadPointer(mUIMtlInst);
	source.ReadPointer(mTexture);

	PX2_END_DEBUG_STREAM_LOAD(UIPicBox, source);
}
//----------------------------------------------------------------------------
void UIPicBox::Link (InStream& source)
{
	TriMesh::Link(source);

	source.ResolveLink(mUIMtl);
	source.ResolveLink(mUIMtlInst);
	source.ResolveLink(mTexture);
}
//----------------------------------------------------------------------------
void UIPicBox::PostLink ()
{
	TriMesh::PostLink();
}
//----------------------------------------------------------------------------
bool UIPicBox::Register (OutStream& target) const
{
	 if (TriMesh::Register(target))
	 {
		 target.Register(mUIMtl);
		 target.Register(mUIMtlInst);
		 target.Register(mTexture);

		 return true;
	 }

	 return false;
}
//----------------------------------------------------------------------------
void UIPicBox::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TriMesh::Save(target);

	target.WriteEnum(mPicBoxType);
	target.WriteBool(mIsDynamic);
	target.WriteAggregate(mAnchorPoint);
	target.WriteAggregate(mSize);
	target.WriteAggregate(mCorSize);
	target.WriteAggregate(mUV0);
	target.WriteAggregate(mUV1);
	target.WriteAggregate(mUV2);
	target.WriteAggregate(mUV3);
	target.WriteAggregate(mColor);
	target.WritePointer(mUIMtl);
	target.WritePointer(mUIMtlInst);
	target.WritePointer(mTexture);

	PX2_END_DEBUG_STREAM_SAVE(UIPicBox, target);
}
//----------------------------------------------------------------------------
int UIPicBox::GetStreamingSize () const
{
	int size = TriMesh::GetStreamingSize();
	size += PX2_ENUMSIZE(mPicBoxType);
	size += PX2_BOOLSIZE(mIsDynamic);
	size += sizeof(mAnchorPoint),
	size += sizeof(mSize);
	size += sizeof(mCorSize);
	size += sizeof(mUV0);
	size += sizeof(mUV1);
	size += sizeof(mUV2);
	size += sizeof(mUV3);
	size += sizeof(mColor);
	size += PX2_POINTERSIZE(mUIMtl);
	size += PX2_POINTERSIZE(mUIMtlInst);
	size += PX2_POINTERSIZE(mTexture);

	return size;
}
//----------------------------------------------------------------------------
