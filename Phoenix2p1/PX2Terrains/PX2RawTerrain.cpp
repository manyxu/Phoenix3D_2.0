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
RawTerrain::RawTerrain ()
	:
Terrain(false)
{
}
//----------------------------------------------------------------------------
RawTerrain::~RawTerrain ()
{
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
	mPages = new2<TerrainPagePtr>(mNumCols, mNumRows);
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
void RawTerrain::UseSimpleMtl (bool use)
{
	Terrain::UseSimpleMtl(use);

	for (int i=0; i<mNumRows; i++)
	{
		for (int j=0; j<mNumCols; j++)
		{
			RawTerrainPage *terPage = DynamicCast<RawTerrainPage>(GetPage(i, j));
			if (terPage)
			{
				if (!mIsUseSimpleMtl)
				{
					terPage->CreateEditMtlInstPerVertex(mMtlEdit, mShine);
				}
				else
				{
					terPage->CreateSimpleMtlInstPerVertex(mMtlSimple, mShine);
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void RawTerrain::CreatePage (int row, int col)
{
	int numHeights = mSize*mSize;
	float *heights = new1<float>(numHeights);
	memset(heights, 0, numHeights*sizeof(float));

	float length = mSpacing*(float)(mSize - 1);
	Float2 origin(col*length, row*length);

	RawTerrainPage* page = 0;
	if (!mIsUseSimpleMtl)
	{
		page = new0 RawTerrainPage(mVFormatEdit, mSize, heights, 
			origin, mSpacing);

		page->CreateEditMtlInstPerVertex(mMtlEdit, mShine);
	}
	else
	{
		page = new0 RawTerrainPage(mVFormatSimple, mSize, heights, 
			origin, mSpacing);

		page->CreateEditMtlInstPerVertex(mMtlSimple, mShine);
	}

	mPages[row][col] = page;
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
Terrain(value)
{
}
//----------------------------------------------------------------------------
void RawTerrain::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Terrain::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(RawTerrain, source);
}
//----------------------------------------------------------------------------
void RawTerrain::Link (InStream& source)
{
	Terrain::Link(source);
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
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void RawTerrain::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Terrain::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(RawTerrain, target);
}
//----------------------------------------------------------------------------
int RawTerrain::GetStreamingSize () const
{
	int size = Terrain::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------
