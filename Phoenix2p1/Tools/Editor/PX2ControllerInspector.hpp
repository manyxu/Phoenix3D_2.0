/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerInspector.hpp
*
*/

#ifndef PX2CONTROLLERINSPECTOR_HPP
#define PX2CONTROLLERINSPECTOR_HPP

#include "PX2EditorPre.hpp"
#include "foldpanelbar.h"
#include "PX2ControllerPropertyGrid.hpp"
#include "PX2ControllerKeyPointsPanel.hpp"
#include "PX2ControllerKeyPointsValuePropertyGrid.hpp"

namespace PX2Editor
{
	
	class ControllerInspector : public wxScrolledWindow
	{
	public:
		ControllerInspector (wxWindow *parent);
		virtual ~ControllerInspector ();

		void SetController (PX2::Controller *ctrl);
		void OnSize(wxSizeEvent& e);

	protected:
		ControllerInspector ();
		DECLARE_EVENT_TABLE()

		PX2::ControllerPtr mController;

		bool mInitSized;
		wxFoldPanelBar *mFoldPaneBar;
		ControllerPropertyGrid *mPropertyGrid;
		ControllerKeyPointsPanel *mKeyPointsPanel;
		ControllerKeyPointsValuePropertyGrid *mKPVPropertyGrid;
	};

}

#endif