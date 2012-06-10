/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2TerrainInspector.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2TERRAININSPECTOR_HPP
#define PX2TERRAININSPECTOR_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2TerrainBrushPane.hpp"
#include "PX2TerrainHeightPane.hpp"
#include "PX2TerrainMaterialPane.hpp"
#include "PX2TerrainActorPropertyGrid.hpp"

namespace PX2Editor
{

	class TerrainInspector : public wxScrolledWindow, public PX2::EventHandler
	{
	public:
		TerrainInspector (wxWindow *parent);
		~TerrainInspector ();

		void OnSize(wxSizeEvent& e);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		TerrainInspector ();

		DECLARE_EVENT_TABLE()

		wxFoldPanelBar *mFoldPaneBar;
		PropertyGrid *mPropGrid;
		TerrainBrushPanel *mTerrainBrush;
		TerrainHeightPanel *mTerrainHeight;
		TerrainMaterialPanel *mTerrainMaterial;

	};

}

#endif