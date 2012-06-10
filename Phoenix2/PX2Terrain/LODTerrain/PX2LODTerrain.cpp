/*
*
* 文件名称	：	PX2LODTerrain.cpp
*
*/

#include "PX2LODTerrain.hpp"
#include "PX2Camera.hpp"
#include "PX2Renderer.hpp"
#include "PX2Environment.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Node, LODTerrain);
PX2_IMPLEMENT_STREAM(LODTerrain);
PX2_IMPLEMENT_FACTORY(LODTerrain);

//----------------------------------------------------------------------------
LODTerrain::LODTerrain (const char *heightName, const char *imageName,
						  VertexFormat *vertexFormat, Renderer* renderer,
						  float uvBias,	Float4 *borderColor)
						  :
mVFormat(vertexFormat),
mUVBias(uvBias),
mRenderer(0),
mBorderColor(borderColor ? *borderColor : Float4(1.0f,1.0f,1.0f,1.0f))
{
	assertion(heightName&&imageName&&renderer,
		"heightName, imageName, renderer must exist.");

	mRenderer = renderer;
	mCameraRow = -1;
	mCameraCol = -1;

	mCloseAssumption = false;
	mPixelTolerance = 1.0f;

	// 加载地形头信息
	LoadHeader(heightName);

	// 加载地形页
	mPages = new2<LODRawTerrainPagePtr>(mRowQuantity, mColQuantity);
	int row, col;
	for (row = 0; row < mRowQuantity; row++)
	{
		for (col = 0; col < mColQuantity; col++)
		{
			char suffix[64];
			sprintf(suffix, "%d.%d", row, col);
			LoadPage(row,col,heightName,suffix,imageName,suffix);
		}
	}

	// 绑定地形页到地形节点
	mChild.resize(mRowQuantity*mColQuantity);
	for (row = 0; row < mRowQuantity; row++)
	{
		for (col = 0; col < mColQuantity; col++)
		{
			AttachChild(mPages[row][col]);
		}
	}

	StitchAll();
	Simplify();
}
//----------------------------------------------------------------------------
LODTerrain::LODTerrain ()
:
mBorderColor(Float4(0.0f,0.0f,0.0f,0.0f))
{
	mRowQuantity = 0;
	mColQuantity = 0;
	mSize = 0;
	mMinElevation = 0.0f;
	mMaxElevation = 0.0f;
	mSpacing = 0.0f;;
	mPages = 0;
	mPixelTolerance = 0.0f;
	mRenderer = 0;
	mCloseAssumption = false;
	mCameraRow = -1;
	mCameraCol = -1;
	mUVBias = 0.0f;
}
//----------------------------------------------------------------------------
LODTerrain::~LODTerrain ()
{
	for (int row = 0; row < mRowQuantity; row++)
	{
		for (int col = 0; col < mColQuantity; col++)
		{
			mPages[row][col] = 0;
		}
	}

	delete2<LODRawTerrainPagePtr>(mPages);
}
//----------------------------------------------------------------------------
void LODTerrain::SetPixelTolerance (float fTolerance)
{
	mPixelTolerance = fTolerance;

	for (int row = 0; row < mRowQuantity; row++)
	{
		for (int col = 0; col < mColQuantity; col++)
		{
			mPages[row][col]->SetPixelTolerance(mRenderer,
				mPixelTolerance);
		}
	}
}
//----------------------------------------------------------------------------
LODTerrainPage* LODTerrain::GetPage (int row, int col)
{
	assert(0 <= row && row < mRowQuantity && 0 <= col && col < mColQuantity);
	if (0 <= row && row < mRowQuantity && 0 <= col && col < mColQuantity)
	{
		return mPages[row][col];
	}

	return 0;
}
//----------------------------------------------------------------------------
LODTerrainPage* LODTerrain::GetCurrentPage (float x, float y) const
{
	float invLength = 1.0f/(mSpacing*(float)(mSize-1));

	int col = (int)Mathf::Floor(x*invLength);
	col %= mColQuantity;
	if (col < 0)
	{
		col += mColQuantity;
	}

	int row = (int)Mathf::Floor(y*invLength);
	row %= mRowQuantity;
	if (row < 0)
	{
		row += mRowQuantity;
	}

	return mPages[row][col];
}
//----------------------------------------------------------------------------
float LODTerrain::GetHeight (float x, float y) const
{
	LODTerrainPage* page = GetCurrentPage(x,y);

	// 减去地形页的offset
	x -= page->LocalTransform.GetTranslate().X();
	y -= page->LocalTransform.GetTranslate().Y();

	return page->GetHeight(x,y);
}
//----------------------------------------------------------------------------
AVector LODTerrain::GetNormal (float x, float y) const
{
	float xP = x + mSpacing;
	float xM = x - mSpacing;
	float yP = y + mSpacing;
	float yM = y - mSpacing;

	LODTerrainPage* page;
	float xTemp, yTemp;

	page = GetCurrentPage(xP,y);
	xTemp = xP - page->LocalTransform.GetTranslate().X();
	yTemp = y - page->LocalTransform.GetTranslate().Y();
	float fHpz = page->GetHeight(xTemp,yTemp);

	page = GetCurrentPage(xM,y);
	xTemp = xM - page->LocalTransform.GetTranslate().X();
	yTemp = y - page->LocalTransform.GetTranslate().Y();
	float fHmz = page->GetHeight(xTemp,yTemp);

	page = GetCurrentPage(x,yP);
	xTemp = x - page->LocalTransform.GetTranslate().X();
	yTemp = yP - page->LocalTransform.GetTranslate().Y();
	float fHzp = page->GetHeight(xTemp,yTemp);

	page = GetCurrentPage(x,yM);
	xTemp = x - page->LocalTransform.GetTranslate().X();
	yTemp = yM - page->LocalTransform.GetTranslate().Y();
	float fHzm = page->GetHeight(xTemp,yTemp);

	AVector normal(fHmz-fHpz,fHzm-fHzp,1.0f);
	normal.Normalize();
	return normal;
}
//----------------------------------------------------------------------------
void LODTerrain::LoadHeader (const char* heightName)
{
	char acFilename[512];
	sprintf(acFilename, "%s,%s,tdhf", heightName);
	const std::string path= Environment::GetPathR(acFilename);

	FileIO inFile(path, FileIO::FM_DEFAULT_READ);
	if (!inFile)
	{
		assertion(false, "Failed to load file %s\n", path);
		return;
	}

	inFile.Read(sizeof(int), &mRowQuantity);
	inFile.Read(sizeof(int), &mColQuantity);
	inFile.Read(sizeof(int), &mSize);
	inFile.Read(sizeof(float), &mMinElevation);
	inFile.Read(sizeof(float), &mMaxElevation);
	inFile.Read(sizeof(float), &mSpacing);

	inFile.Close();
}
//----------------------------------------------------------------------------
void LODTerrain::LoadPage (int row, int col, const char* heightName,
							const char* heightSuffix, const char* imageName,
							const char* imageSuffix)
{
	PX2_UNUSED(imageSuffix);
	PX2_UNUSED(imageName);

	int iQuantity = mSize*mSize;
	unsigned short *height = new1<unsigned short>(iQuantity);
	const size_t size = 512;
	char filename[size];
	sprintf(filename, "%s,%s,tdhf", heightName, heightSuffix);
	
	std::string path = Environment::GetPathR(filename);
	FileIO inFile(path, FileIO::FM_READ);
	if (!inFile)
	{
		assertion(false, "Failed to load file %s\n", path.c_str());
		return;
	}

	inFile.Read(sizeof(height), height);

	inFile.Close();

	float length = mSpacing*(float)(mSize-1);
	Vector2f origin(col*length,row*length);
	LODTerrainPage *page = new0 LODTerrainPage(mVFormat,mSize,
		height,origin,mMinElevation,mMaxElevation,mSpacing,
		mUVBias);

	// Material

	mPages[row][col] = page;
}
//----------------------------------------------------------------------------
LODRawTerrainPagePtr LODTerrain::ReplacePage (int row, int col,
											 const char *heightName, const char *heightSuffix,
											 const char *imageName, const char * /*imageSuffix */)
{
	assert(0<=row && row<mRowQuantity && 0<=col&&col<mColQuantity);

	if (0<=row && row<mRowQuantity && 0<=col&&col<mColQuantity)
	{
		LODRawTerrainPagePtr save = mPages[row][col];
		LoadPage(row,col,heightName,heightSuffix,imageName,
			heightSuffix);
		return save;
	}

	return 0;
}
//----------------------------------------------------------------------------
LODRawTerrainPagePtr LODTerrain::ReplacePage (int row, int col,
										   LODTerrainPage* newPage)
{
	assert(0<=row && row<mRowQuantity && 0<=col&&col<mColQuantity);

	if (0<=row && row<mRowQuantity && 0<=col&&col<mColQuantity)
	{
		LODRawTerrainPagePtr save = mPages[row][col];
		mPages[row][col] = newPage;
		return save;
	}

	return 0;
}
//----------------------------------------------------------------------------
void LODTerrain::Simplify ()
{
	if (!mRenderer)
		return;

	// 获得Camera在地形模型坐标系的位置和方向
	const Camera *camera = mRenderer->GetCamera();
	APoint worldEye = camera->GetPosition();
	AVector worldDir = camera->GetDVector();
	APoint modelEye = WorldTransform.GetMatrix().Inverse() * worldEye;
	AVector modelDir = WorldTransform.GetRotate().Inverse() * worldDir;

	// 初始化地形页
	int row, col;
	for (row=0; row<mRowQuantity; row++)
	{
		for (col=0; col<mColQuantity; col++)
		{
			mPages[row][col]->ResetBlocks();
		}
	}

	for (row=0; row<mRowQuantity; row++)
	{
		for (col=0; col<mColQuantity; col++)
		{
			LODTerrainPage *page = mPages[row][col];
			if (page->IntersectFrustum(camera))
			{
				modelEye = page->WorldTransform.GetMatrix().Inverse()
					* worldEye;
				modelDir = page->WorldTransform.GetRotate().Inverse()
					* worldDir;

				page->Simplify(mRenderer,modelEye,modelDir,mCloseAssumption);

				Renderer::UpdateAll(page->mVBuffer);
				Renderer::UpdateAll(page->mIBuffer);
			}
		}
	}
}
//----------------------------------------------------------------------------
void LODTerrain::StitchAll ()
{
	// 将地形页缝合在一起
	int row, col;
	for (row=0; row<mRowQuantity; row++)
	{
		for (col=0; col+1<mColQuantity; col++)
		{
			mPages[row][col]->StitchNextCol(mPages[row][col+1]);
		}
	}

	for (col=0; col<mColQuantity; col++)
	{
		for (row=0; row+1<mRowQuantity; row++)
		{
			mPages[row][col]->StitchNextRow(mPages[row+1][col]);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 名称
//----------------------------------------------------------------------------
Object* LODTerrain::GetObjectByName (const std::string& name)
{
	Object* found = Node::GetObjectByName(name);
	if (found)
	{
		return found;
	}

	PX2_GET_OBJECT_BY_NAME(mVFormat, name, found);
	for (int row = 0; row < mRowQuantity; ++row)
	{
		for (int col = 0; col < mColQuantity; ++col)
		{
			PX2_GET_OBJECT_BY_NAME(mPages[row][col], name, found);
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
void LODTerrain::GetAllObjectsByName (const std::string& name,
								   std::vector<Object*>& objects)
{
	Node::GetAllObjectsByName(name, objects);

	PX2_GET_ALL_OBJECTS_BY_NAME(mVFormat, name, objects);
	for (int row = 0; row < mRowQuantity; ++row)
	{
		for (int col = 0; col < mColQuantity; ++col)
		{
			PX2_GET_ALL_OBJECTS_BY_NAME(mPages[row][col], name, objects);
		}
	}
}
//----------------------------------------------------------------------------
void LODTerrain::UseLOD (bool use)
{
	mUseLOD = use;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
LODTerrain::LODTerrain (LoadConstructor value)
:
Node(value)
{
	mBorderColor = Float4(1.0f,1.0f,1.0f,1.0f);
	mRowQuantity = 0;
	mColQuantity = 0;
	mSize = 0;
	mMinElevation = 0.0f;
	mMaxElevation = 0.0f;
	mSpacing = 0.0f;
	mPages = 0;
	mPixelTolerance = 0.0f;
	mRenderer = 0;
	mCloseAssumption = false;
	mCameraRow = -1;
	mCameraCol = -1;
	mUVBias = 0.0f;
}
//----------------------------------------------------------------------------
void LODTerrain::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Node::Load(source);

	source.Read(mRowQuantity);
	source.Read(mColQuantity);
	source.Read(mSize);
	source.Read(mMinElevation);
	source.Read(mMaxElevation);
	source.Read(mSpacing);
	source.Read(mPixelTolerance);
	source.Read(mCloseAssumption);
	source.Read(mCameraRow);
	source.Read(mCameraCol);
	source.Read(mUVBias);
	source.ReadAggregate(mBorderColor);
	source.ReadPointer(mVFormat);

	mPages = new2<LODRawTerrainPagePtr>(mColQuantity, mRowQuantity);
	for (int row = 0; row < mRowQuantity; ++row)
	{
		for (int col = 0; col < mColQuantity; ++col)
		{
			source.ReadPointer(mPages[row][col]);
		}
	}

	PX2_END_DEBUG_STREAM_LOAD(LODTerrain, source);
}
//----------------------------------------------------------------------------
void LODTerrain::Link (InStream& source)
{
	Node::Link(source);

	source.ResolveLink(mVFormat);
	for (int row = 0; row < mRowQuantity; ++row)
	{
		for (int col = 0; col < mColQuantity; ++col)
		{
			source.ResolveLink(mPages[row][col]);
		}
	}
}
//----------------------------------------------------------------------------
void LODTerrain::PostLink ()
{
	Node::PostLink();
}
//----------------------------------------------------------------------------
bool LODTerrain::Register (OutStream& target) const
{
	if (Node::Register(target))
	{
		target.Register(mVFormat);
		for (int row = 0; row < mRowQuantity; ++row)
		{
			for (int col = 0; col < mColQuantity; ++col)
			{
				target.Register(mPages[row][col]);
			}
		}
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void LODTerrain::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Node::Save(target);

	target.Write(mRowQuantity);
	target.Write(mColQuantity);
	target.Write(mSize);
	target.Write(mMinElevation);
	target.Write(mMaxElevation);
	target.Write(mSpacing);
	target.Write(mPixelTolerance);
	target.Write(mCloseAssumption);
	target.Write(mCameraRow);
	target.Write(mCameraCol);
	target.Write(mUVBias);
	target.WriteAggregate(mBorderColor);
	target.WritePointer(mVFormat);

	for (int row = 0; row < mRowQuantity; ++row)
	{
		for (int col = 0; col < mColQuantity; ++col)
		{
			target.WritePointer(mPages[row][col]);
		}
	}

	PX2_END_DEBUG_STREAM_SAVE(LODTerrain, target);
}
//----------------------------------------------------------------------------
int LODTerrain::GetStreamingSize () const
{
	int size = Node::GetStreamingSize();
	size += sizeof(mRowQuantity);
	size += sizeof(mColQuantity);
	size += sizeof(mSize);
	size += sizeof(mMinElevation);
	size += sizeof(mMaxElevation);
	size += sizeof(mSpacing);
	size += sizeof(mPixelTolerance);
	size += PX2_BOOLSIZE(mCloseAssumption);
	size += sizeof(mCameraRow);
	size += sizeof(mCameraCol);
	size += sizeof(mUVBias);
	size += sizeof(mBorderColor);
	size += mRowQuantity*mColQuantity*PX2_POINTERSIZE(mPages[0][0]);

	return size;
}
//----------------------------------------------------------------------------