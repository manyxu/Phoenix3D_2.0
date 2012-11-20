/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditorFrame.hpp
*
*/

#ifndef PX2MAINFRAME_HPP
#define PX2MAINFRAME_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class RenderViewWindow;
	class PreViewWindow;

	class MainFrame : public wxFrame
	{
	public:
		MainFrame (const wxString title, int xPos, int yPos, int width,
			int height);
		virtual ~MainFrame ();

	protected:
		DECLARE_EVENT_TABLE ()

		bool Initlize ();
		void CreateMenu();
		void CreateMainToolbar ();

		wxAuiManager *mAuiManager;
		wxToolBar* mMainToolbar;
		RenderViewWindow *mRenderView;
		PreViewWindow *mPreView;
	};

}

#endif