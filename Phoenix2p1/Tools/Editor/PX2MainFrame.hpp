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
	class ObjectTree;
	class PreViewWindow;
	class ResTreePanel;
	class InspectorWindow;
	class CurveEditWindow;
	
	class MainFrame : public wxFrame
	{
	public:
		MainFrame (const wxString title, int xPos, int yPos, int width,
			int height);
		virtual ~MainFrame ();

		void OnTimer (wxTimerEvent& event);
		void OnNewProject (wxCommandEvent &e);
		void OnOpenProject (wxCommandEvent &e);
		void OnSaveProject (wxCommandEvent &e);
		void OnSaveProjectAs (wxCommandEvent &e);
		void OnCloseProject (wxCommandEvent &e);
		void OnNewScene (wxCommandEvent &e);
		void OnOpenScene (wxCommandEvent &e);
		void OnSaveScene (wxCommandEvent &e);
		void OnSaveSceneAs (wxCommandEvent &e);
		void OnCloseScene (wxCommandEvent &e);
		void OnImport (wxCommandEvent &e);
		void OnExportSelected (wxCommandEvent &e);
		void OnSave (wxCommandEvent &e);
		void OnExist (wxCommandEvent &e);
		void OnUnDo (wxCommandEvent &e);
		void OnReDo (wxCommandEvent &e);
		void OnEditSelect (wxCommandEvent& e);
		void OnEditTranslate (wxCommandEvent& e);
		void OnEditRolate (wxCommandEvent& e);
		void OnEditScale (wxCommandEvent& e);
		void OnEditEdit (wxCommandEvent& e);
		void OnEditDelete (wxCommandEvent& e);
		void OnViewStage (wxCommandEvent& e);
		void OnViewActorTree (wxCommandEvent& e);
		void OnViewPreView (wxCommandEvent& e);
		void OnViewResTree (wxCommandEvent& e);
		void OnViewInspector (wxCommandEvent& e);
		void OnViewCurveEdit (wxCommandEvent& e);
		void OnViewCentre (wxCommandEvent& e);
		void OnCreateBox (wxCommandEvent& e);
		void OnCreateSphere (wxCommandEvent& e);
		void OnCreateEffect (wxCommandEvent& e);
		void OnCreateCtrlTransform (wxCommandEvent& e);
		void OnCreateCtrlColor (wxCommandEvent& e);
		void OnCreateCtrlAlpha (wxCommandEvent& e);
		void OnTerrainNew (wxCommandEvent &e);
		void OnTerrainComposeMtl (wxCommandEvent &e);
		void OnTerrainUseLod (wxCommandEvent &e);
		void OnTerrainUseComposeMtl (wxCommandEvent &e);
		void OnGamePlay (wxCommandEvent& e);

	protected:
		DECLARE_EVENT_TABLE ()

		bool Initlize ();
		void CreateMenu();
		void CreateMainToolbar ();
		void EnableEditAll (bool enable);

		bool mInited;
		wxTimer mTimer;
		wxMenuBar *mMainMenu;
		wxAuiManager *mAuiManager;
		wxToolBar* mMainToolbar;
		RenderViewWindow *mRenderView;
		PreViewWindow *mPreView;
		ObjectTree *mObjectTree;
		ResTreePanel *mResTreePanel;
		InspectorWindow *mInspector;
		CurveEditWindow *mCurveEditWindow;
	};

}

#endif