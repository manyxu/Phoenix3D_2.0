/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainProcess.hpp
*
*/

#ifndef PX2TERRAINPROCESS_HPP
#define PX2TERRAINPROCESS_HPP

#include "PX2EditorLibPre.hpp"
#include "PX2TerrainBrush.hpp"

namespace PX2Editor
{

	class TerrainProcess
	{
	public:
		~TerrainProcess ();

		enum TerProType
		{
			TPT_HEIGHT,
			TPT_TEXTURE,
			TPT_MAX_TYPE
		};

		TerProType GetTerProType();

		virtual void SetBrush (TerrainBrush *brush) { mBrush = brush; }
		TerrainBrush *GetBrush () { return mBrush; }

		void SetTerrain (PX2::RawTerrain *terrain) { mTerrain = terrain; }

		virtual void Apply ();

	protected:
		TerrainProcess ();
		TerrainProcess (TerProType type);

		TerrainBrush *mBrush;
		TerProType mTerProType;
		PX2::RawTerrainPtr mTerrain;
	};

	class TerrainHeightProcess : public TerrainProcess
	{
	public:
		TerrainHeightProcess ();
		virtual ~TerrainHeightProcess ();

		enum HeightMode
		{
			HM_RAISE,
			HM_LOWER,
			HM_FLATTEN,
			HM_SMOOTH,
			HM_ZERO,
			HM_MAX_MODE
		};

		void SetHeightMode (HeightMode mode) { mHeightMode = mode; }
		HeightMode GetHeightMode () { return mHeightMode; }

		virtual void Apply ();

	protected:
		HeightMode mHeightMode;
	};

	class TerrainTextureProcess : public TerrainProcess
	{
	public:
		TerrainTextureProcess ();
		virtual ~TerrainTextureProcess ();

		enum TextureMode
		{
			TM_INCREASE,
			TM_DECREASE,
			TM_APPLY,
			TM_SMOOTH,
			TM_NOISE,
			TM_MAX_MODE
		};

		void SetTextureMode (TextureMode textureMode) { mTextureMode = textureMode; }
		TextureMode GetTextureMode () { return mTextureMode; }

		void SetSelectedLayer (int index) { mSelectedLayerIndex = index; }
		int GetSelectedLayer () { return mSelectedLayerIndex; }

		void SetLayerUsingTexture (int layerIndex, PX2::Texture2D *texture);
		PX2::Texture2D *GetLayerUsingTexture (int layerIndex);
		void SetSelectedLayerUsingTexture (PX2::Texture2D *texture);
		PX2::Texture2D *GetSelectedLayerUsingTexture ();

		virtual void Apply ();

	protected:
		TextureMode mTextureMode;
		int mSelectedLayerIndex;
		std::map<int, PX2::Texture2DPtr> mLayerTextures;
	};

}


#endif