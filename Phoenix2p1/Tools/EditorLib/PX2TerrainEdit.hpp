/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainEdit.hpp
*
*/

#ifndef PX2TERRAINEDIT_HPP
#define PX2TERRAINEDIT_HPP

#include "PX2EditorLibPre.hpp"
#include "PX2TerrainBrush.hpp"
#include "PX2TerrainProcess.hpp"

namespace PX2Editor
{

	class TerrainEdit
	{
	public:
		TerrainEdit ();
		~TerrainEdit ();

		void EnableEdit ();
		void DisableEdit ();
		void ShowPageLine (bool show);
		bool IsPageLineShow ();

		void SetEditType (TerrainProcess::TerProType type);
		TerrainProcess::TerProType GetEditType ();

		TerrainBrush *GetBrush () { return mBrush; }

		TerrainHeightProcess *GetHeightProcess () { return mHeightProcess; }
		TerrainTextureProcess *GetTextureProcess () { return mTextureProcess; }

		PX2::Renderable *GetTerrainHelpGrid () { return mTerrainHelpGrid; }

		// Do
		void Apply ();

	protected:
		void SetTerrain (PX2::RawTerrain *terrain);
		void CreateTerrainHelpGrid ();
		void DestoryTerrainHelpGrid ();

		PX2::RawTerrainPtr mTerrain;
		TerrainBrush *mBrush;
		TerrainProcess *mActiveProcess;
		TerrainHeightProcess *mHeightProcess;
		TerrainTextureProcess *mTextureProcess;
		PX2::RenderablePtr mTerrainHelpGrid;
	};

}

#endif