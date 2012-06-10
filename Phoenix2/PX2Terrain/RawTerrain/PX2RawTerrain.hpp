/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2RawTerrain.h
*
* 版本		:	1.0 (2011/05/14)
*
* 作者		：	more
*
*/

#ifndef PX2RAWTERRAIN_HPP
#define PX2RAWTERRAIN_HPP

#include "PX2TerrainPrerequisites.hpp"
#include "PX2Node.hpp"
#include "PX2Camera.hpp"
#include "PX2RawTerrainPage.hpp"
#include "PX2TerrainMaterial.hpp"

namespace PX2
{

	class PX2_TERRAIN_ENTRY RawTerrain : public Node
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(RawTerrain);

	public:
		RawTerrain (); //< 通过编辑器创建地形时使用
		RawTerrain (const std::string& heightName, VertexFormat* vformat,
			Camera* camera, int mode = FileIO::FM_DEFAULT_READ);

		virtual ~RawTerrain ();

		// 材质
		TerrainMaterial *GetTerrainMaterial ();
		Shine *GetShine ();

		// 创建地形时，设置地形属性
		/*
		* 这些接口，在编辑器中创建地形使用
		*/
		void SetRowQuantity (int numRows);
		void SetColQuantity (int numCols);
		void SetSize (int size);
		void SetSpacing (float spacing);
		void AllocateRawTerrainPages ();
		void UpdateToHighField ();

		// 成员访问
		inline int GetRowQuantity () const;
		inline int GetColQuantity () const;
		inline int GetSize () const;
		inline float GetSpacing () const;
		float GetHeight (float x, float y) const;
		AVector GetNormal (float x, float y) const;

		// 地形页管理
		RawTerrainPage* GetPage (int row, int col);
		RawTerrainPage* GetCurrentPage (float x, float y) const;
		bool GetPageIndex (int &outRow, int &outCol, RawTerrainPage *page);
		RawTerrainPagePtr ReplacePage (int row, int col,
			const std::string& heightName, const std::string& heightSuffix);
		RawTerrainPagePtr ReplacePage (int row, int col, RawTerrainPage* newPage);

		// Update of active set of terrain pages.
		void OnCameraMotion ();

	protected:
		void LoadHeader (const std::string& heightName);

		void CreatePage (int row, int col);
		void LoadPage (int row, int col, const std::string& heightName,
			const std::string& heightSuffix);

		// Read mode for the height header file and the terrain page data.
		int mMode;

		// Shared by the pages.
		VertexFormatPtr mVFormat;

		// Page information.
		int mNumRows, mNumCols;
		int mSize;
		float mMinElevation, mMaxElevation, mSpacing;
		RawTerrainPagePtr** mPages;

		// Current page containing the camera.
		int mCameraRow, mCameraCol;
		CameraPtr mCamera;

		// Terrain Material
		TerrainMaterialPtr mTerrainMaterial;
		ShinePtr mShine;
	};

	PX2_REGISTER_STREAM(RawTerrain);
	typedef Pointer0<RawTerrain> RawTerrainPtr;
#include "PX2RawTerrain.inl"

}

#endif