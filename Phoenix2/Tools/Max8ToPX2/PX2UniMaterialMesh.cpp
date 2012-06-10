/*
*
* 文件名称	：	PX2UniMaterialMesh.cpp
*
*/

#include "PX2UniMaterialMesh.hpp"
#include <algorithm>
#include <vector>
using namespace PX2;

UniMaterialMesh::UniMaterialMesh ()
{
	mVertexMapQuantity = 0;
	mVertexMap = 0;
	mNormalMap = 0;
	mColorMapQuantity = 0;
	mColorMap = 0;
	mTQuantity = 0;
	mTextureCoordMap = 0;
	mFQuantity = 0;
	mVFace = 0;
	mCFace = 0;
	mTFace = 0;
	mNumTexcoordToExport = 1;
	mExportTargentBinormal = false;
}
//----------------------------------------------------------------------------
UniMaterialMesh::~UniMaterialMesh ()
{
	delete1(mVertexMap);
	delete1(mNormalMap);
	delete1(mColorMap);
	delete1(mTextureCoordMap);
	delete1(mVFace);
	delete1(mCFace);
	delete1(mTFace);
}
//----------------------------------------------------------------------------
int &UniMaterialMesh::VQuantity()
{
	return mVertexMapQuantity;
}
//----------------------------------------------------------------------------
PX2::Float3 *&UniMaterialMesh::VertexMap ()
{
	return mVertexMap;
}
//----------------------------------------------------------------------------
PX2::Float3 *&UniMaterialMesh::NormalMap ()
{
	return mNormalMap;
}
//----------------------------------------------------------------------------
int &UniMaterialMesh::CQuantity ()
{
	return mColorMapQuantity;
}
//----------------------------------------------------------------------------
PX2::Float3 *&UniMaterialMesh::ColorMap ()
{
	return mColorMap;
}
//----------------------------------------------------------------------------
int &UniMaterialMesh::TQuantity ()
{
	return mTQuantity;
}
//----------------------------------------------------------------------------
PX2::Float2 *&UniMaterialMesh::TextureCoordMap ()
{
	return mTextureCoordMap;
}
//----------------------------------------------------------------------------
int &UniMaterialMesh::FQuantity ()
{
	return mFQuantity;
}
//----------------------------------------------------------------------------
int *&UniMaterialMesh::Face ()
{
	return mVFace;
}
//----------------------------------------------------------------------------
int *&UniMaterialMesh::CFace ()
{
	return mCFace;
}
//----------------------------------------------------------------------------
int *&UniMaterialMesh::TFace ()
{
	return mTFace;
}
//----------------------------------------------------------------------------
void UniMaterialMesh::SetShineProperty (PX2::Shine *shine)
{
	mShine = shine;
}
//----------------------------------------------------------------------------
void UniMaterialMesh::SetMaterialInstance (MaterialInstance *mi)
{
	mMaterialInstance = mi;
}
//----------------------------------------------------------------------------
void UniMaterialMesh::DuplicateGeometry()
{
	std::vector<VertexAttr> *vArray =
		new1<std::vector<VertexAttr> >(mVertexMapQuantity);

	// 每一个三角形面包含三个顶点，相邻的三角形共两个顶点。
	// 将所有组合按照面的顶点索引分类，去除完全一样的顶点。

	int i;
	for (i=0; i<3*mFQuantity; i++)
	{
		// 对每个面进行操作

		VertexAttr vertexAttr;

		// 顶点索引
		vertexAttr.V = mVFace[i];

		// 颜色索引
		if (mColorMapQuantity > 0)
		{
			vertexAttr.C = mCFace[i];
		}

		// 纹理坐标索引
		if (mTQuantity > 0)
		{
			vertexAttr.T = mTFace[i];
		}

		vArray[mVFace[i]].push_back(vertexAttr);
	}

	int newVQuantity = 0;
	for (i=0; i<mVertexMapQuantity; i++)
	{
		// 去掉顶点索引，颜色索引，贴图坐标索引完全一样的顶点
		sort(vArray[i].begin(), vArray[i].end());
		std::vector<VertexAttr>::iterator end = unique(vArray[i].begin(),
			vArray[i].end());
		vArray[i].erase(end, vArray[i].end());
		newVQuantity += (int)vArray[i].size();
	}

	Float3 *newVertex = new1<Float3>(newVQuantity);
	Float3 *newNormal = new1<Float3>(newVQuantity);

	Float3 *newColor = 0;
	if (mColorMapQuantity > 0)
	{
		newColor = new1<Float3>(newVQuantity);
	}

	Float2 *newTexture = 0;
	if (mTQuantity > 0)
	{
		newTexture = new1<Float2>(newVQuantity);
	}

	int j, k;
	for (i=0, k=0; i<mVertexMapQuantity; i++)
	{
		// 让每个顶点中，不同的颜色，纹理坐标的每个组合成为一个顶点
		std::vector<VertexAttr> &rvArray = vArray[i];
		int size = (int)rvArray.size();
		for (j=0; j<size; j++,k++)
		{
			newVertex[k] = mVertexMap[i];
			newNormal[k] = mNormalMap[i];

			VertexAttr vertexAttr = rvArray[j];

			if (newColor)
			{
				newColor[k] = mColorMap[vertexAttr.C];
			}

			if (newTexture)
			{
				newTexture[k] = mTextureCoordMap[vertexAttr.T];
			}

			vertexAttr.V = k;
			rvArray.push_back(vertexAttr);
		}
	}

	// 计算顶点索引
	for (i=0; i<mFQuantity; i++)
	{
		int threeI = 3*i;
		int *vIndex = mVFace + threeI;
		int *cIndex = (mColorMapQuantity>0 ? mCFace+threeI : 0);
		int *tIndex = (mTQuantity>0 ? mTFace+threeI : 0);
		for (j=0; j<3; j++)
		{
			VertexAttr vertexAttr;
			vertexAttr.V = vIndex[j];

			if (cIndex)
			{
				vertexAttr.C = cIndex[j];
			}

			if (tIndex)
			{
				vertexAttr.T = tIndex[j];
			}

			std::vector<VertexAttr> &rvArray = vArray[vIndex[j]]; // 共有同一空间位置的点集
			int halfSize = (int)rvArray.size()/2;
			for (k=0; k<halfSize; k++)
			{
				if (rvArray[k] == vertexAttr)
				{
					vIndex[j] = rvArray[halfSize+k].V;
					break;
				}
			}
		}
	}

	delete1(mVertexMap);
	delete1(mNormalMap);
	delete1(mColorMap);
	delete1(mTextureCoordMap);

	mVertexMapQuantity = newVQuantity;
	mVertexMap = newVertex;
	mNormalMap = newNormal;
	mColorMap = newColor;
	mTextureCoordMap = newTexture;

	delete1(vArray);
}
//----------------------------------------------------------------------------
void UniMaterialMesh::SetExportTargentBinormal (bool exp)
{
	mExportTargentBinormal = exp;
}
//----------------------------------------------------------------------------
void UniMaterialMesh::SetNumTexcoordToExport (int num)
{
	mNumTexcoordToExport = num;
}
//----------------------------------------------------------------------------s
TriMesh *UniMaterialMesh::ToTriMesh()
{
	if (mVertexMapQuantity == 0)
		return 0;

	// VertexBuffer
	VertexFormat *vFormat = new0 VertexFormat();
	vFormat->Add(VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0);
	if (mColorMap)
	{
		vFormat->Add(VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0);
	}
	if (mNormalMap)
	{
		vFormat->Add(VertexFormat::AU_NORMAL, VertexFormat::AT_FLOAT3, 0);
	}
	if (mExportTargentBinormal)
	{
		vFormat->Add(VertexFormat::AU_TANGENT, VertexFormat::AT_FLOAT3, 0);
		vFormat->Add(VertexFormat::AU_BINORMAL, VertexFormat::AT_FLOAT3, 0);
	}
	if(mTextureCoordMap)
	{
		if (1 == mNumTexcoordToExport)
		{
			vFormat->Add(VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);
		}
		else if (2 == mNumTexcoordToExport)
		{
			vFormat->Add(VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);
			vFormat->Add(VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 1);
		}
	}
	vFormat->Create();

	PX2::VertexBuffer *vBuffer = new0 PX2::VertexBuffer(mVertexMapQuantity, 
		vFormat->GetStride());

	VertexBufferAccessor vBA(vFormat, vBuffer);

	for (int i=0; i<mVertexMapQuantity; i++)
	{
		vBA.Position<Float3>(i) = mVertexMap[i];

		if (mNormalMap)
		{
			vBA.Normal<Float3>(i) = mNormalMap[i];
		}

		if (mColorMap)
		{
			vBA.Color<Float4>(0, i) = Float4(mColorMap[i][0], mColorMap[i][1],
				mColorMap[i][2], 1.0f);
		}

		if (mTextureCoordMap)
		{
			if (mNumTexcoordToExport == 1)
			{
				vBA.TCoord<Float2>(0, i) = Float2(mTextureCoordMap[i][0], 1.0f-mTextureCoordMap[i][1]);
			}
			else if (mNumTexcoordToExport == 2)
			{
				vBA.TCoord<Float2>(0, i) = Float2(mTextureCoordMap[i][0], 1.0f-mTextureCoordMap[i][1]);
				vBA.TCoord<Float2>(1, i) = Float2(mTextureCoordMap[i][0], 1.0f-mTextureCoordMap[i][1]);
			}
		}
	}
	
	// IndexBuffer
	IndexBuffer *iBuffer = new0 IndexBuffer(3*mFQuantity, (int)sizeof(int));
	int *iData = (int*)iBuffer->GetData();
	size_t size = 3*mFQuantity*sizeof(int);
	memcpy(iData, mVFace, size);

	// 创建Mesh
	TriMesh *triMesh = new0 TriMesh(vFormat, vBuffer, iBuffer);
	if (mExportTargentBinormal)
	{
		triMesh->UpdateModelSpace(Renderable::GU_USE_GEOMETRY);
	}
	triMesh->SetMaterialInstance(mMaterialInstance);

	return triMesh;
}
//----------------------------------------------------------------------------
UniMaterialMesh::VertexAttr::VertexAttr()
{
	V = -1;
	C = -1;
	T = -1;
}
//----------------------------------------------------------------------------
bool UniMaterialMesh::VertexAttr::operator == (const VertexAttr &vFormat)
const
{
	return V==vFormat.V && C==vFormat.C && T==vFormat.T;
}
//----------------------------------------------------------------------------
bool UniMaterialMesh::VertexAttr::operator < (const VertexAttr &vFormat) const
{
	if (V < vFormat.V)
		return true;

	if (V > vFormat.V)
		return false;

	if (C < vFormat.C)
		return true;

	if (C > vFormat.C)
		return false;

	return T < vFormat.T;
}
//----------------------------------------------------------------------------