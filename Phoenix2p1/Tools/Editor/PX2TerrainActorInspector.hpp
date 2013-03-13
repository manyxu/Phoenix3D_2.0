/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainActorInspector.hpp
*
*/

#ifndef PX2TERRAININSPECTOR_HPP
#define PX2TERRAININSPECTOR_HPP

#include "PX2EditorPre.hpp"
#include "PX2TerrainActorPropertyGrid.hpp"
#include "PX2TerrainBrushPane.hpp"
#include "PX2TerrainHeightPane.hpp"
#include "PX2TerrainMaterialPane.hpp"
#include "PX2TerrainJunglerPane.hpp"
#include "PX2TerrainActor.hpp"
#include "foldpanelbar.h"

namespace PX2Editor
{

	class TerrainActorInspector : public wxScrolledWindow
	{
	public:
		TerrainActorInspector (wxWindow *parent);
		~TerrainActorInspector ();

		void OnSize(wxSizeEvent& e);
		void SetActor (PX2::TerrainActor *actor);
		void EnableEdit (bool enable);
		bool IsEditEnable () { return mEnableEdit; }
		void RefreshSelectTerrainPage ();

		void OnPageChanged( wxBookCtrlEvent &event );

	protected:
		DECLARE_EVENT_TABLE()

		TerrainActorInspector ();

		bool mInitSized;
		bool mEnableEdit;
		PX2::TerrainActorPtr mTerrainActor;
		wxFoldPanelBar *mFoldPaneBar;
		wxFoldPanel mBrushFold;
		wxFoldPanel mEditFold;
		TerrainHeightPanel *mHeightPanel;
		TerrainMaterialPanel *mMaterialPanel;
		TerrainJunglerPanel *mJunglerPanel;

		TerrainActorPropertyGrid *mTerrainActorPropGrid;
		TerrainBrushPanel *mTerrainBrush;
		wxBookCtrl *mEditBook;
	};
}

#endif