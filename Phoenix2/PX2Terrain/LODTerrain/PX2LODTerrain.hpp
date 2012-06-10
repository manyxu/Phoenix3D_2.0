/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2LODTerrain.hpp
*
* 版本		:	1.0 (2011/03/05)
*
* 作者		：	more
*
*/

#ifndef PX2LODTERRAIN_HPP
#define PX2LODTERRAIN_HPP

#include "PX2TerrainPrerequisites.hpp"
#include "PX2LODTerrainPage.hpp"

namespace PX2
{

	/// Level Of Detail地形
	class PX2_TERRAIN_ENTRY LODTerrain : public Node
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(LODTerrain);

	public:
		LODTerrain (const char* heightName, const char* imageName,
			VertexFormat *vertexFormat, Renderer *renderer, float uvBias,
			Float4 *borderColor);

		virtual ~LODTerrain ();

		void SetRenderer (Renderer* renderer);

		// 地形成员
		int GetRowQuantity () const;
		int GetColQuantity () const;
		int GetSize () const;
		float GetMinElevation () const;
		float GetMaxElevation () const;
		float GetSpacing () const;
		void SetPixelTolerance (float fTolerance);
		float GetPixelTolerance () const;
		bool &CloseAssumption ();
		float &GetUVBias ();
		Float4 &GetBorderColor ();

		// 地形页管理
		LODTerrainPage *GetPage (int row, int col);
		LODTerrainPage *GetCurrentPage (float x, float y) const;
		float GetHeight (float x, float y) const;

		/// 估算位置(fX,fY)的法线
		AVector GetNormal (float x, float y) const;

		/// 地形页替换
		/**
		* 解除缝合就的地形页，加载新的地形页并且缝合到一起。返回旧的地形页，以备
		* 再次复用。
		*/
		LODRawTerrainPagePtr ReplacePage (int row, int col,
			const char *heightName, const char *heightSuffix,
			const char *imageName, const char *imageSuffix);

		LODRawTerrainPagePtr ReplacePage (int row, int col,
			LODTerrainPage *newPage);

		void UseLOD (bool use);
		bool UsingLOD ();

		/// 简化地形
		void Simplify ();

	protected:
		LODTerrain ();

		void LoadHeader (const char *heightPrefix);
		void LoadPage (int row, int col, const char *heightName,
			const char *heightSuffix, const char *imageName,
			const char *imageSuffix);
		void StitchAll (); //< 将所有地形页缝合在一起

		// 地形页顶点格式
		VertexFormatPtr mVFormat;

		// 地形页信息
		int mRowQuantity, mColQuantity;
		int mSize; //< 一个地形页的大小
		float mMinElevation, mMaxElevation, mSpacing;
		LODRawTerrainPagePtr **mPages;

		// simplification
		float mPixelTolerance;
		Renderer *mRenderer;
		bool mCloseAssumption;

		// 相机当前所在地形页
		int mCameraRow, mCameraCol;

		// 纹理参数
		float mUVBias;
		Float4 mBorderColor;

		bool mUseLOD;
	};

	PX2_REGISTER_STREAM(LODTerrain);
	typedef Pointer0<LODTerrain> LODTerrainPtr;
#include "PX2LODTerrain.inl"

}

#endif