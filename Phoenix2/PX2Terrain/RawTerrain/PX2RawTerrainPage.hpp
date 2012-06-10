/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2RawTerrainPage.hpp
*
* 版本		:	1.0 (2011/05/12)
*
* 作者		：	more
*
*/

#ifndef PX2RAWTERRAINPAGE_HPP
#define PX2RAWTERRAINPAGE_HPP

#include "PX2TerrainPrerequisites.hpp"
#include "PX2TriMesh.hpp"

namespace PX2
{

	class TerrainMaterial;

	class PX2_TERRAIN_ENTRY RawTerrainPage : public TriMesh
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(RawTerrainPage);

	public:
		// size = 2^p + 1, p <= 7 (size = 3, 5, 9, 17, 33, 65, 129)
		RawTerrainPage (VertexFormat* vformat, int size, float* heights,
			const Float2& origin, float spacing);

		virtual ~RawTerrainPage ();

		// 高程访问
		inline int GetSize () const;
		inline const float* GetHeights () const;
		inline const Float2& GetOrigin () const;
		inline float GetMinElevation () const;
		inline float GetMaxElevation () const;
		inline float GetSpacing () const;

		/// 获得高度
		/**
		* 如果方位不再地形页中，返回MAX_REAL
		*/
		float GetHeight (float x, float y) const;


		/// 将顶点高度信息保存到高程数据mHeights中
		/**
		* 在编辑器中修改顶点后将顶点高度转换到高程mHeights中
		*/
		void UpdateToHighField ();

		// 贴图
		void SetTexture (int index, std::string filename);
		void SetTexture0 (std::string filename);
		void SetTextureAlpha (std::string filename);
		void SetTexture1 (std::string filename);
		void SetTexture2 (std::string filename);
		void SetTexture3 (std::string filename);
		void SetTexture4 (std::string filename);
		void SetTexture (int index, Texture2D *texture); // 0-4
		void SetTexture0 (Texture2D *texture);
		void SetTextureAlpha (Texture2D *texture);
		void SetTexture1 (Texture2D *texture);
		void SetTexture2 (Texture2D *texture);
		void SetTexture3 (Texture2D *texture);
		void SetTexture4 (Texture2D *texture);

		Texture2D *GetTexture(int index); //0,1,2,3,4
		Texture2D *GetTexture0 ();
		Texture2D *GetTextureAlpha ();
		Texture2D *GetTexture1 ();
		Texture2D *GetTexture2 ();
		Texture2D *GetTexture3 ();
		Texture2D *GetTexture4 ();

		void SetUV (int index, Float2 uv);
		void SetUV0 (Float2 uv);
		void SetUV1 (Float2 uv);
		void SetUV2 (Float2 uv);
		void SetUV3 (Float2 uv);
		void SetUV4 (Float2 uv);
		Float2 GetUV (int index);
		Float2 GetUV0 ();
		Float2 GetUV1 ();
		Float2 GetUV2 ();
		Float2 GetUV3 ();
		Float2 GetUV4 ();

		void CreateInstancePerVertex (TerrainMaterial *material, Shine *shine);
		void CreateInstancePerPixel (TerrainMaterial *material, Shine *shine);

	protected:
		virtual void UpdateWorldData (double applicationTime);
		inline float GetX (int x) const;
		inline float GetY (int y) const;
		inline float GetHeight (int index) const;

		// 高程参数及数据
		int mSize, mSizeM1;
		float* mHeights;
		Float2 mOrigin;
		float mSpacing;
		float mInvSpacing;

		PX2::LightPtr mDirLight; // 不用保存
		MaterialInstancePtr mMaterialInstance;
		Texture2DPtr mTextureDefault;
		Texture2DPtr mTexture0;
		Texture2DPtr mTextureAlpha;
		Texture2DPtr mTexture1;
		Texture2DPtr mTexture2;
		Texture2DPtr mTexture3;
		Texture2DPtr mTexture4;
		Float4 mUV01;
		Float4 mUV23;
		Float4 mUV4;
		ShaderFloatPtr mUV01Float;
		ShaderFloatPtr mUV23Float;
		ShaderFloatPtr mUV4Float;
	};

	PX2_REGISTER_STREAM(RawTerrainPage);
	typedef Pointer0<RawTerrainPage> RawTerrainPagePtr;
#include "PX2RawTerrainPage.inl"

}

#endif