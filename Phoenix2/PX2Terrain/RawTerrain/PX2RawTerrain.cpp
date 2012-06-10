/*
*
* 文件名称	：	PX2RawTerrain.cpp
*
*/

#include "PX2RawTerrain.hpp"
#include "PX2TerrainMaterial.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Node, RawTerrain);
PX2_IMPLEMENT_STREAM(RawTerrain);
PX2_IMPLEMENT_FACTORY(RawTerrain);

//----------------------------------------------------------------------------
RawTerrain::RawTerrain (const std::string& heightName, VertexFormat* vformat,
				  Camera* camera, int mode)
				  :
mMode(mode),
mVFormat(vformat),
mCameraRow(-1),
mCameraCol(-1),
mCamera(camera)
{
	// 加载地形信息
	LoadHeader(heightName);

	// 加载地形页
	mPages = new2<RawTerrainPagePtr>(mNumCols, mNumRows);
	int row, col;
	for (row = 0; row < mNumRows; ++row)
	{
		for (col = 0; col < mNumCols; ++col)
		{
			char temp[64];
			sprintf(temp, "%d.%d", row, col);
			std::string heightSuffix(temp);
			LoadPage(row, col, heightName, heightSuffix);
		}
	}

	// 绑定地形页到地形节点
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

	mTerrainMaterial = new0 TerrainMaterial(
		"Data/Materials/TerrainPerPixel.pxfx");

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
	// 加载地形页
	mPages = new2<RawTerrainPagePtr>(mNumCols, mNumRows);
	int row, col;
	for (row = 0; row < mNumRows; ++row)
	{
		for (col = 0; col < mNumCols; ++col)
		{
			CreatePage(row, col);
		}
	}

	// 绑定地形页到地形节点
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
void RawTerrain::UpdateToHighField ()
{
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			RawTerrainPagePtr page = mPages[row][col];
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
void RawTerrain::LoadHeader (const std::string& heightName)
{
	std::string fileName = heightName + ".pxhf";
	FileIO header(fileName, mMode);
	assertion(header, "Cannot open file %s\n", fileName);

	header.Read(sizeof(int), &mNumRows);
	header.Read(sizeof(int), &mNumCols);

	unsigned short size;
	header.Read(sizeof(unsigned short), &size);
	mSize = (int)size;

	header.Read(sizeof(float), &mMinElevation);
	header.Read(sizeof(float), &mMaxElevation);
	header.Read(sizeof(float), &mSpacing);

	header.Close();
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

	page->CreateInstancePerPixel(mTerrainMaterial, mShine);

	mPages[row][col] = page;
}
//----------------------------------------------------------------------------
void RawTerrain::LoadPage (int row, int col, const std::string& heightName,
						const std::string& heightSuffix)
{
	int numHeights = mSize*mSize;
	float* heights = new1<float>(numHeights);
	std::string fileName = heightName + "." + heightSuffix + ".tdhf";
	FileIO heightFile(fileName, mMode);
	assertion(heightFile, "Cannot open file %s\n", fileName);
	if (heightFile)
	{
		heightFile.Read(sizeof(unsigned short), numHeights, heights);
		heightFile.Close();
	}
	else
	{
		memset(heights, 0, numHeights*sizeof(unsigned short));
	}

	float length = mSpacing*(float)(mSize - 1);
	Float2 origin(col*length, row*length);
	RawTerrainPage* page = new0 RawTerrainPage(mVFormat, mSize, heights,
		origin, mSpacing);

	mPages[row][col] = page;
}
//----------------------------------------------------------------------------
RawTerrainPagePtr RawTerrain::ReplacePage (int row, int col,
									 const std::string& heightName, const std::string& heightSuffix)
{
	if (0 <= row && row < mNumRows && 0 <= col && col < mNumCols)
	{
		RawTerrainPagePtr save = mPages[row][col];
		LoadPage(row, col, heightName, heightSuffix);
		return save;
	}

	assertion(false, "Invalid row or column index\n");
	return 0;
}
//----------------------------------------------------------------------------
RawTerrainPagePtr RawTerrain::ReplacePage (int row, int col, RawTerrainPage* newPage)
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
void RawTerrain::OnCameraMotion ()
{
	assertion(mCamera != 0, "Camera must exist\n");
	if (!mCamera)
	{
		return;
	}

	// 获得地形模型坐标系下相继的方位
	APoint worldEye = mCamera->GetPosition();
	AVector worldDir = mCamera->GetDVector();
	APoint modelEye = WorldTransform.Inverse()*worldEye;
	AVector modelDir = WorldTransform.Inverse()*worldDir;

	// Update the model-space origins of the terrain pages.  Start the
	// process by locating the page that contains the camera.
	float length = mSpacing*(float)(mSize - 1);
	float invLength = 1.0f/length;
	int newCameraCol = (int)Mathf::Floor(modelEye.X()*invLength);
	int newCameraRow = (int)Mathf::Floor(modelEye.Y()*invLength);
	if (newCameraCol != mCameraCol || newCameraRow != mCameraRow)
	{
		mCameraCol = newCameraCol;
		mCameraRow = newCameraRow;

		// Translate page origins for toroidal wraparound.
		int cminO = mCameraCol - mNumCols/2;
		int cminP = cminO % mNumCols;
		if (cminP < 0)
		{
			cminP += mNumCols;
		}

		int rminO = mCameraRow - mNumRows/2;
		int rminP = rminO % mNumRows;
		if (rminP < 0)
		{
			rminP += mNumRows;
		}

		int rO = rminO, rP = rminP;
		for (int row = 0; row < mNumRows; ++row)
		{
			int cO = cminO, cP = cminP;
			for (int col = 0; col < mNumCols; ++col)
			{
				RawTerrainPage* page = mPages[rP][cP];
				Float2 oldOrigin = page->GetOrigin();
				Float2 newOrigin(cO*length, rO*length);
				APoint pageTrn(
					newOrigin[0] - oldOrigin[0],
					newOrigin[1] - oldOrigin[1],
					page->LocalTransform.GetTranslate().Z());
				page->LocalTransform.SetTranslate(pageTrn);

				++cO;
				if (++cP == mNumCols)
				{
					cP = 0;
				}
			}

			++rO;
			if (++rP == mNumRows)
			{
				rP = 0;
			}
		}
		Update();
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称支持
//----------------------------------------------------------------------------
Object* RawTerrain::GetObjectByName (const std::string& name)
{
	Object* found = Node::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mVFormat, name, found);
	PX2_GET_OBJECT_BY_NAME(mCamera, name, found);
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			PX2_GET_OBJECT_BY_NAME(mPages[row][col], name, found);
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
void RawTerrain::GetAllObjectsByName (const std::string& name,
								   std::vector<Object*>& objects)
{
	Node::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mVFormat, name, objects);
	PX2_GET_ALL_OBJECTS_BY_NAME(mCamera, name, objects);
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			PX2_GET_ALL_OBJECTS_BY_NAME(mPages[row][col], name, objects);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
RawTerrain::RawTerrain (LoadConstructor value)
:
Node(value),
mMode(FileIO::FM_NONE),
mNumRows(0),
mNumCols(0),
mSize(0),
mMinElevation(0.0f),
mMaxElevation(0.0f),
mSpacing(0.0f),
mPages(0),
mCameraRow(0),
mCameraCol(0)
{
}
//----------------------------------------------------------------------------
void RawTerrain::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Node::Load(source);

	source.ReadEnum(mMode);
	source.Read(mNumRows);
	source.Read(mNumCols);
	source.Read(mSize);
	source.Read(mMinElevation);
	source.Read(mMaxElevation);
	source.Read(mSpacing);
	source.Read(mCameraRow);
	source.Read(mCameraCol);
	source.ReadPointer(mVFormat);
	source.ReadPointer(mCamera);
	source.ReadPointer(mShine);

	mPages = new2<RawTerrainPagePtr>(mNumCols, mNumRows);
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			source.ReadPointer(mPages[row][col]);
		}
	}

	PX2_END_DEBUG_STREAM_LOAD(RawTerrain, source);
}
//----------------------------------------------------------------------------
void RawTerrain::Link (InStream& source)
{
	Node::Link(source);

	source.ResolveLink(mVFormat);
	source.ResolveLink(mCamera);
	source.ResolveLink(mShine);
	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			source.ResolveLink(mPages[row][col]);
		}
	}
}
//----------------------------------------------------------------------------
void RawTerrain::PostLink ()
{
	Node::PostLink();
}
//----------------------------------------------------------------------------
bool RawTerrain::Register (OutStream& target) const
{
	if (Node::Register(target))
	{
		target.Register(mVFormat);
		target.Register(mCamera);
		target.Register(mShine);
		for (int row = 0; row < mNumRows; ++row)
		{
			for (int col = 0; col < mNumCols; ++col)
			{
				target.Register(mPages[row][col]);
			}
		}
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void RawTerrain::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Node::Save(target);

	target.WriteEnum(mMode);
	target.Write(mNumRows);
	target.Write(mNumCols);
	target.Write(mSize);
	target.Write(mMinElevation);
	target.Write(mMaxElevation);
	target.Write(mSpacing);
	target.Write(mCameraRow);
	target.Write(mCameraCol);
	target.WritePointer(mVFormat);
	target.WritePointer(mCamera);
	target.WritePointer(mShine);

	for (int row = 0; row < mNumRows; ++row)
	{
		for (int col = 0; col < mNumCols; ++col)
		{
			target.WritePointer(mPages[row][col]);
		}
	}

	PX2_END_DEBUG_STREAM_SAVE(RawTerrain, target);
}
//----------------------------------------------------------------------------
int RawTerrain::GetStreamingSize () const
{
	int size = Node::GetStreamingSize();
	size += PX2_ENUMSIZE(mMode);
	size += sizeof(mNumRows);
	size += sizeof(mNumCols);
	size += sizeof(mSize);
	size += sizeof(mMinElevation);
	size += sizeof(mMaxElevation);
	size += sizeof(mSpacing);
	size += sizeof(mCameraRow);
	size += sizeof(mCameraCol);
	size += PX2_POINTERSIZE(mVFormat);
	size += PX2_POINTERSIZE(mCamera);
	size += PX2_POINTERSIZE(mShine);
	size += mNumRows*mNumCols*PX2_POINTERSIZE(mPages[0][0]);
	return size;
}
//----------------------------------------------------------------------------
