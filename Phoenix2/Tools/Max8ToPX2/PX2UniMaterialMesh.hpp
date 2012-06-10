/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2UniMaterialMesh.hpp
*
* 版本		:	1.0 (2011/05/22)
*
* 作者		：	more
*
*/

#ifndef PX2UNIMATERIALMESH_HPP
#define PX2UNIMATERIALMESH_HPP

#include "PX2Max9ToTdPluginPrerequisites.hpp"

class UniMaterialMesh
{
public:
	UniMaterialMesh ();
	~UniMaterialMesh ();

	int &VQuantity ();
	PX2::Float3 *&VertexMap ();
	PX2::Float3 *&NormalMap ();
	int &CQuantity ();
	PX2::Float3 *&ColorMap ();
	int &TQuantity ();
	PX2::Float2 *&TextureCoordMap ();
	int &FQuantity ();
	int *&Face ();
	int *&CFace ();
	int *&TFace ();

	void SetShineProperty (PX2::Shine *shine);
	void SetMaterialInstance (PX2::MaterialInstance *mi);

	// 一个Max顶点可以拥有多个UVW坐标。Phoenix2只支持一个UV坐标（W被忽略掉），
	// 所以Max顶点拥有的N个UVW坐标必须被复制到N个Phoenix2的顶点数组中，每个顶
	// 点只拥有一个UV坐标。
	void DuplicateGeometry ();

	void SetExportTargentBinormal (bool exp);
	void SetNumTexcoordToExport (int num);
	PX2::TriMesh *ToTriMesh ();

	class VertexAttr
	{
	public:
		VertexAttr ();
		bool operator== (const VertexAttr &vFormat) const;
		bool operator< (const VertexAttr &vFormat) const;
		int V, C, T;
	};

private:

	// --
	int mVertexMapQuantity;
	PX2::Float3 *mVertexMap;
	PX2::Float3 *mNormalMap;

	int mColorMapQuantity;
	PX2::Float3 *mColorMap;

	int mTQuantity;
	PX2::Float2 *mTextureCoordMap;
	// --

	int mFQuantity;
	int *mVFace;	// 每个元素代表一个面上，一个顶点的顶点索引
	int *mCFace;	// 每个元素代表一个面上，一个顶点的颜色索引
	int *mTFace;	// 每个元素代表一个面上，一个顶点的贴图坐标索引

	bool mExportTargentBinormal;
	int mNumTexcoordToExport;

	PX2::ShinePtr mShine;
	PX2::MaterialInstancePtr mMaterialInstance;
};

#endif