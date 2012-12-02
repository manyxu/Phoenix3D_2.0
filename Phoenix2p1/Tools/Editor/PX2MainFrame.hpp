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

		void OnTimer (wxTimerEvent& event);
		void OnNew (wxCommandEvent &e);
		void OnOpen (wxCommandEvent &e);
		void OnSave (wxCommandEvent &e);
		void OnSaveAs (wxCommandEvent &e);
		void OnExist (wxCommandEvent &e);
		void OnEditSelect (wxCommandEvent& e);
		void OnEditTranslate (wxCommandEvent& e);
		void OnEditRolate (wxCommandEvent& e);
		void OnEditScale (wxCommandEvent& e);
		void OnGamePlay (wxCommandEvent& e);

	protected:
		DECLARE_EVENT_TABLE ()

		bool Initlize ();
		void CreateMenu();
		void CreateMainToolbar ();

		bool mInited;
		wxTimer mTimer;
		wxAuiManager *mAuiManager;
		wxToolBar* mMainToolbar;
		RenderViewWindow *mRenderView;
		PreViewWindow *mPreView;
	};

}

#endif