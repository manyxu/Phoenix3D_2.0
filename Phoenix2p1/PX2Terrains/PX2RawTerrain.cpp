/*
*
* 文件名称	：	PX2RawTerrain.cpp
*
*/

#include "PX2RawTerrain.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Terrain, RawTerrain);
PX2_IMPLEMENT_STREAM(RawTerrain);
PX2_IMPLEMENT_FACTORY(RawTerrain);

//----------------------------------------------------------------------------
RawTerrain::~RawTerrain ()
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
RawTerrain::RawTerrain ()
{
	mVFormat = VertexFormat::Create(9,
		VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_NORMAL, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT3, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 1,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 2,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 3,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 4,
		VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 5);

	mMaterial = new0 EditTerrainMaterial("Data/mtls/EditTerrain.pxfx");

	mShine = new0 Shine();
	mShine->Emissive = Float4(0.0f, 0.0f, 0.0f, 1.0f);
	mShine->Ambient = Float4(0.3f, 0.3f, 0.3f, 1.0f);
	mShine->Diffuse = Float4(1.0f, 1.0f, 1.0f, 1.0f);
}
//----------------------------------------------------------------------------
void RawTerrain::SetRowQuantity (int numRows)
{
	mNumRows = numRows;
}
//----------------------------------------------------------------------------
void RawTerrain::SetColQuantity (int numCols)
{
	mNumCols = numCols;
}
//----------------------------------------------------------------------------
void RawTerrain::SetSize (int size)
{
	mSize = size;
}
//----------------------------------------------------------------------------
void RawTerrain::SetSpacing (float spacing)
{
	mSpacing = spacing;
}
//----------------------------------------------------------------------------
void RawTerrain::AllocateRawTerrainPages ()
{
	mPages = new2<RawTerrainPagePtr>(mNumCols, mNumRows);
	int row, col;
	for (row = 0; row < mNumRows; ++row)
	{
		for (col = 0; col < mNumCols; ++col)
		{
			CreatePage(row, col);
		}
	}

	mChild.resize(mNumRows*mNumCols);
	for (row = 0; row < mNumRows; ++row)
	{
		for (col = 0; col < mNumCols; ++col)
		{
			AttachChild(mPages[row][col]);
		}
	}
}
//----------------------------------------------------------------------------
RawTerrainPage* RawTerrain::GetPage (int row, int col)
{
	if (0 <= row && row < mNumRows && 0 <= col && col < mNumCols)
	{
		return mPages[row][col];
	}

	assertion(false, "Invalid row or column index\n");
	return 0;
}
//----------------------------------------------------------------------------
RawTerrainPage* RawTerrain::GetCurrentPage (float x, float y) const
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
bool RawTerrain::GetPageIndex (int &outRow, int &outCol, RawTerrainPage *page)
{
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			RawTerrainPage *curPage = mPages[row][col];

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
float RawTerrain::GetHeight (float x, float y) const
{
	RawTerrainPage* page = GetCurrentPage(x,y);

	x -= page->LocalTransform.GetTranslate().X();
	y -= page->LocalTransform.GetTranslate().Y();

	return page->GetHeight(x, y);
}
//----------------------------------------------------------------------------
AVector RawTerrain::GetNormal (float x, float y) const
{
	float xp = x + mSpacing;
	float xm = x - mSpacing;
	float yp = y + mSpacing;
	float ym = y - mSpacing;

	RawTerrainPage* page = GetCurrentPage(xp, y);
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
void RawTerrain::CreatePage (int row, int col)
{
	int numHeights = mSize*mSize;
	float *heights = new1<float>(numHeights);
	memset(heights, 0, numHeights*sizeof(float));

	float length = mSpacing*(float)(mSize - 1);
	Float2 origin(col*length, row*length);
	RawTerrainPage* page = new0 RawTerrainPage(mVFormat, mSize, heights, 
		origin, mSpacing);

	page->CreateInstancePerVertex(mMaterial, mShine);

	mPages[row][col] = page;
}
//----------------------------------------------------------------------------
RawTerrainPagePtr RawTerrain::ReplacePage (int row, int col, 
	RawTerrainPage* newPage)
{
	if (0 <= row && row < mNumRows && 0 <= col && col < mNumCols)
	{
		RawTerrainPagePtr save = mPages[row][col];
		mPages[row][col] = newPage;
		return save;
	}

	assertion(false, "Invalid row or column index\n");
	return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* RawTerrain::GetObjectByName (const std::string& name)
{
	Object* found = Terrain::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	return 0;
}
//----------------------------------------------------------------------------
void RawTerrain::GetAllObjectsByName (const std::string& name,
	std::vector<Object*>& objects)
{
	Terrain::GetAllObjectsByName(name, objects);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
RawTerrain::RawTerrain (LoadConstructor value)
	:
Terrain(value),
	mPages(0)
{
}
//----------------------------------------------------------------------------
void RawTerrain::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Terrain::Load(source);

	source.ReadPointer(mVFormat);
	mPages = new2<RawTerrainPagePtr>(mNumCols, mNumRows);
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			source.ReadPointer(mPages[row][col]);
		}
	}

	source.ReadPointer(mShine);

	PX2_END_DEBUG_STREAM_LOAD(RawTerrain, source);
}
//----------------------------------------------------------------------------
void RawTerrain::Link (InStream& source)
{
	Terrain::Link(source);

	source.ResolveLink(mVFormat);
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			source.ResolveLink(mPages[row][col]);
		}
	}

	source.ResolveLink(mShine);
}
//----------------------------------------------------------------------------
void RawTerrain::PostLink ()
{
	Terrain::PostLink();
}
//----------------------------------------------------------------------------
bool RawTerrain::Register (OutStream& target) const
{
	if (Terrain::Register(target))
	{
		target.Register(mVFormat);
		for (int row = 0; row < mNumRows; ++row)
		{
			for (int col = 0; col < mNumCols; ++col)
			{
				target.Register(mPages[row][col]);
			}
		}

		target.Register(mShine);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void RawTerrain::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Terrain::Save(target);

	target.WritePointer(mVFormat);
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			target.WritePointer(mPages[row][col]);
		}
	}

	target.WritePointer(mShine);

	PX2_END_DEBUG_STREAM_SAVE(RawTerrain, target);
}
//----------------------------------------------------------------------------
int RawTerrain::GetStreamingSize () const
{
	int size = Node::GetStreamingSize();
	size += PX2_POINTERSIZE(mVFormat);
	size += mNumRows*mNumCols*PX2_POINTERSIZE(mPages[0][0]);
	size += PX2_POINTERSIZE(mShine);
	return size;
}
//----------------------------------------------------------------------------
