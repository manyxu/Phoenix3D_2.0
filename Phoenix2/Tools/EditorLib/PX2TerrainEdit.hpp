/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	TerrainEdit.hpp
*
* 版本		:	1.0 (2011/06/06)
*
* 作者		：	more
*
*/

#ifndef PX2TERRAINEDIT_HPP
#define PX2TERRAINEDIT_HPP

#include "PX2EditorLibPrerequisites.hpp"
#include "PX2TerrainBrush.hpp"
#include "PX2TerrainProcess.hpp"

namespace PX2Editor
{

	class TerrainEdit : public PX2::EventHandler
	{
	public:
		TerrainEdit ();
		~TerrainEdit ();

		void EnableEdit ();
		void DisableEdit ();

		void SetEditType (TerrainProcess::TerProType type);
		TerrainProcess::TerProType GetEditType ();

		TerrainBrush *GetBrush () { return mBrush; }

		TerrainHeightProcess *GetHeightProcess () { return mHeightProcess; }
		TerrainTextureProcess *GetTextureProcess () { return mTextureProcess; }

		PX2::Renderable *GetTerrainHelpGrid () { return mTerrainHelpGrid; }

		// Do
		void Apply ();

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

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