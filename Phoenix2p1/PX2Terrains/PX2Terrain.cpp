/*
*
* 文件名称	：	PX2Terrain.cpp
*
*/

#include "PX2Terrain.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Node, Terrain);
PX2_IMPLEMENT_STREAM(Terrain);
PX2_IMPLEMENT_ABSTRACT_FACTORY(Terrain);

//----------------------------------------------------------------------------
Terrain::~Terrain ()
{
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			mPages[row][col] = 0;
		}
	}

	delete2(mPages);
}
//----------------------------------------------------------------------------
Terrain::Terrain(bool useSimpleMtl)
	:
mPages(0),
mNumRows(0),
mNumCols(0),
mSize(0),
mMinElevation(0),
mMaxElevation(0),
mSpacing(1.0f),
mIsUseSimpleMtl(useSimpleMtl)
{
	mShine = new0 Shine();
	mShine->Emissive = Float4(0.05f, 0.05f, 0.05f, 1.0f);
	mShine->Ambient = Float4(0.25f, 0.25f, 0.25f, 1.0f);
	mShine->Diffuse = Float4(1.0f, 1.0f, 1.0f, 1.0f);

	mVFormatEdit = VertexFormat::Create(4,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_NORMAL, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);
	mVFormatSimple = VertexFormat::Create(4,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_NORMAL, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);
		
	mMtlEdit = new0 EditTerrainMaterial();
	mMtlSimple = new0 EditTerrainMaterial();
}
//----------------------------------------------------------------------------
Terrain::Terrain()
{
}
//----------------------------------------------------------------------------
void Terrain::UseSimpleMtl (bool use)
{
	mIsUseSimpleMtl = use;
}
//----------------------------------------------------------------------------
TerrainPage *Terrain::GetPage (int row, int col)
{
	if (0 <= row && row < mNumRows && 0 <= col && col < mNumCols)
	{
		return mPages[row][col];
	}

	assertion(false, "Invalid row or column index\n");
	return 0;
}
//----------------------------------------------------------------------------
TerrainPage *Terrain::GetCurrentPage (float x, float y) const
{
	float invLength = 1.0f/(mSpacing*(float)(mSize - 1));

	int col = (int)Mathf::Floor(x*invLength);
	col %= mNumCols;
	if (col < 0)
	{
		col += mNumCols;
	}

	int row = (int)Mathf::Floor(y*invLength);
	row %= mNumRows;
	if (row < 0)
	{
		row += mNumRows;
	}

	return mPages[row][col];
}
//----------------------------------------------------------------------------
bool Terrain::GetPageIndex (int &outRow, int &outCol, TerrainPage *page)
{
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			TerrainPage *curPage = mPages[row][col];

			if (curPage == page)
			{
				outRow = row;
				outCol = col;

				return true;
			}
		}
	}

	return false;
}
//----------------------------------------------------------------------------
TerrainPagePtr Terrain::ReplacePage (int row, int col, TerrainPage* newPage)
{
	if (0 <= row && row < mNumRows && 0 <= col && col < mNumCols)
	{
		TerrainPagePtr save = mPages[row][col];
		mPages[row][col] = newPage;
		return save;
	}

	assertion(false, "Invalid row or column index\n");
	return 0;
}
//----------------------------------------------------------------------------
float Terrain::GetHeight (float x, float y) const
{
	TerrainPage* page = GetCurrentPage(x,y);

	x -= page->LocalTransform.GetTranslate().X();
	y -= page->LocalTransform.GetTranslate().Y();

	return page->GetHeight(x, y);
}
//----------------------------------------------------------------------------
AVector Terrain::GetNormal (float x, float y) const
{
	float xp = x + mSpacing;
	float xm = x - mSpacing;
	float yp = y + mSpacing;
	float ym = y - mSpacing;

	TerrainPage* page = GetCurrentPage(xp, y);
	float xtmp = xp - page->LocalTransform.GetTranslate().X();
	float ytmp = y - page->LocalTransform.GetTranslate().Y();
	float hpz = page->GetHeight(xtmp,ytmp);

	page = GetCurrentPage(xm, y);
	xtmp = xm - page->LocalTransform.GetTranslate().X();
	ytmp = y - page->LocalTransform.GetTranslate().Y();
	float hmz = page->GetHeight(xtmp,ytmp);

	page = GetCurrentPage(x, yp);
	xtmp = x - page->LocalTransform.GetTranslate().X();
	ytmp = yp - page->LocalTransform.GetTranslate().Y();
	float hzp = page->GetHeight(xtmp,ytmp);

	page = GetCurrentPage(x, ym);
	xtmp = x - page->LocalTransform.GetTranslate().X();
	ytmp = ym - page->LocalTransform.GetTranslate().Y();
	float hzm = page->GetHeight(xtmp,ytmp);

	AVector normal(hmz - hpz, hzm - hzp, 1.0f);
	normal.Normalize();
	return normal;
}
//----------------------------------------------------------------------------
void Terrain::AddJunglers (Texture2D *tex, APoint center, float radius,
	int num, float width, float height, float lower)
{
	for (int i=0; i<mNumRows; i++)
	{
		for (int j=0; j<mNumCols; j++)
		{
			GetPage(i, j)->mAddingJObjs.clear();
		}
	}

	for (int i=0; i<num; i++)
	{
		float unitRadius = Mathf::UnitRandom();
		float fX0 = Mathf::SymmetricRandom();
		float fY0 = Mathf::SymmetricRandom();
		AVector normal0(fX0, fY0, 0.0f);
		normal0.Normalize();

		float fX1 = Mathf::SymmetricRandom();
		float fY1 = Mathf::SymmetricRandom();
		AVector normal1(fX1, fY1, 0.0f);
		normal1.Normalize();

		APoint pos = center + normal0*unitRadius*radius;
		pos.Z() = GetHeight(pos.X(), pos.Y()) - lower;

		JObj obj;
		obj.Pos = pos;
		obj.Normal = normal1;
		obj.Width = width;
		obj.Height = height;

		TerrainPage *page = GetCurrentPage(obj.Pos.X(), obj.Pos.Y());
		page->mAddingJObjs.push_back(obj);
	}

	for (int i=0; i<mNumRows; i++)
	{
		for (int j=0; j<mNumCols; j++)
		{
			TerrainPage *page = GetPage(i, j);
			page->AddJunglers(tex, page->mAddingJObjs);
		}
	}
}
//----------------------------------------------------------------------------
void Terrain::RemoveJunglers (Texture2D *tex, APoint center, float radius,
	int num)
{
	for (int i=0; i<mNumRows; i++)
	{
		for (int j=0; j<mNumCols; j++)
		{
			TerrainPage *page = GetPage(i, j);

			page->RemoveJunglers(tex, center, radius, num);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* Terrain::GetObjectByName (const std::string& name)
{
	Object* found = Node::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void Terrain::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Node::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Terrain::Terrain (LoadConstructor value)
	:
Node(value),
	mPages(0),
	mNumRows(0),
	mNumCols(0),
	mSize(0),
	mMinElevation(0.0f),
	mMaxElevation(0.0f),
	mSpacing(0.0f),
	mIsUseSimpleMtl(false)
{
}
//----------------------------------------------------------------------------
void Terrain::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Node::Load(source);

	source.Read(mNumRows);
	source.Read(mNumCols);
	source.Read(mSize);
	source.Read(mMinElevation);
	source.Read(mMaxElevation);
	source.Read(mSpacing);

	mPages = new2<TerrainPagePtr>(mNumCols, mNumRows);
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			source.ReadPointer(mPages[row][col]);
		}
	}

	source.ReadBool(mIsUseSimpleMtl);
	source.ReadPointer(mVFormatEdit);
	source.ReadPointer(mVFormatSimple);
	source.ReadPointer(mMtlEdit);
	source.ReadPointer(mMtlSimple);
	source.ReadPointer(mShine);

	PX2_END_DEBUG_STREAM_LOAD(Terrain, source);
}
//----------------------------------------------------------------------------
void Terrain::Link (InStream& source)
{
	Node::Link(source);

	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			source.ResolveLink(mPages[row][col]);
		}
	}

	source.ResolveLink(mVFormatEdit);
	source.ResolveLink(mVFormatSimple);
	source.ResolveLink(mMtlEdit);
	source.ResolveLink(mMtlSimple);
	source.ResolveLink(mShine);
}
//----------------------------------------------------------------------------
void Terrain::PostLink ()
{
	Node::PostLink();
}
//----------------------------------------------------------------------------
bool Terrain::Register (OutStream& target) const
{
	if (Node::Register(target))
	{
		for (int row = 0; row < mNumRows; ++row)
		{
			for (int col = 0; col < mNumCols; ++col)
			{
				target.Register(mPages[row][col]);
			}
		}

		target.Register(mVFormatEdit);
		target.Register(mVFormatSimple);
		target.Register(mMtlEdit);
		target.Register(mMtlSimple);
		target.Register(mShine);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void Terrain::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Node::Save(target);

	target.Write(mNumRows);
	target.Write(mNumCols);
	target.Write(mSize);
	target.Write(mMinElevation);
	target.Write(mMaxElevation);
	target.Write(mSpacing);

	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			target.WritePointer(mPages[row][col]);
		}
	}

	target.WriteBool(mIsUseSimpleMtl);
	target.WritePointer(mVFormatEdit);
	target.WritePointer(mVFormatSimple);
	target.WritePointer(mMtlEdit);
	target.WritePointer(mMtlSimple);
	target.WritePointer(mShine);

	PX2_END_DEBUG_STREAM_SAVE(Terrain, target);
}
//----------------------------------------------------------------------------
int Terrain::GetStreamingSize () const
{
	int size = Node::GetStreamingSize();
	size += sizeof(mNumRows);
	size += sizeof(mNumCols);
	size += sizeof(mSize);
	size += sizeof(mMinElevation);
	size += sizeof(mMaxElevation);
	size += sizeof(mSpacing);
	size += mNumRows*mNumCols*PX2_POINTERSIZE(mPages[0][0]);
	size += PX2_BOOLSIZE(mIsUseSimpleMtl);
	size += PX2_POINTERSIZE(mVFormatEdit);
	size += PX2_POINTERSIZE(mVFormatSimple);
	size += PX2_POINTERSIZE(mMtlEdit);
	size += PX2_POINTERSIZE(mMtlSimple);
	size += PX2_POINTERSIZE(mShine);

	return size;
}
//----------------------------------------------------------------------------
