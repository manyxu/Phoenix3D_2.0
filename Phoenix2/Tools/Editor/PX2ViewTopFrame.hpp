/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ViewTopFrame.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2VIEWTOPFRAME_HPP
#define PX2VIEWTOPFRAME_HPP

#include "PX2EditorPrerequisites.hpp"
#include "wxFourWaySplitter.h"

namespace PX2Editor
{

	class RenderViewWindow;
	class PreViewWindow;
	class ViewLogWindow;
	class DlgNewTerrain;
	class PropertyGrid;
	class InspectorWindow;
	class TerrainInspector;
	class ModelInspector;
	class EffectEditWindow;
	class SceneSettingWindow;

	class ViewTopFrame : public wxFrame, public PX2::EventHandler
	{
	public:
		ViewTopFrame (const wxString title, int xPos, int yPos, int width, 
			int height);
		~ViewTopFrame ();

		void Initialize ();

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

		// Event hooks
		void OnTimer (wxTimerEvent& event);
		void OnNew (wxCommandEvent &e);
		void OnOpen (wxCommandEvent &e);
		void OnSave (wxCommandEvent &e);
		void OnSaveAs (wxCommandEvent &e);
		void OnUnDo (wxCommandEvent &e);
		void OnReDo (wxCommandEvent &e);
		void OnCopy (wxCommandEvent &e);
		void OnPaste (wxCommandEvent &e);
		void OnDelete (wxCommandEvent &e);
		void OnEditSelectionModeClicked (wxCommandEvent& e);
		void OnEditTranslateClicked (wxCommandEvent& e);
		void OnEditRolateClicked (wxCommandEvent& e);
		void OnEditScaleClicked (wxCommandEvent& e);
		void OnStageGrid (wxCommandEvent &e);
		void OnEffectPane (wxCommandEvent &e);
		void OnCreateObjectClicked (wxCommandEvent& e);
		void OnCreateAndAddCubeClicked (wxCommandEvent& e);
		void OnCreateAndAddSphereClicked (wxCommandEvent& e);
		void OnCreateAndAddPlaneClicked (wxCommandEvent& e);
		void OnCreateAndAddLightClicked (wxCommandEvent& e);

		void OnEditMode_Scene (wxCommandEvent& e);
		void OnEditMode_Effect (wxCommandEvent& e);
		void OnEditMode_ModelActor (wxCommandEvent& e);

		void OnContextMenu(wxContextMenuEvent& event);
		void OnMenuViewTop(wxCommandEvent& event);
		void OnMenuViewFront(wxCommandEvent& event);
		void OnMenuViewLeft(wxCommandEvent& event);
		void OnMenuViewPerspective(wxCommandEvent& event);

		// Terrain
		void OnNewTerrain (wxCommandEvent &e);
		void OnTerrainHeightEdit (wxCommandEvent &e);
		void OnTerrainTextureEdit (wxCommandEvent &e);

		// Physics
		void OnPhysicsPlay (wxCommandEvent &e);

		// Tools
		void OnToolsTextureConvert (wxCommandEvent &e);

	protected:
		DECLARE_EVENT_TABLE ()

		void CreateMainToolbar ();
		void CreateViewToolbar ();
		void CreateEditToolbar ();
		void CreateEditModeToolbar ();
		void CreateMenu ();
		void CreatePopupMenu ();

		// 将场景设置到渲染器
		void SetRendersScene ();

		wxTimer mTimer;
		wxAuiManager* mAuiManager;
		wxAuiNotebook *mNoteBookRenderViews;
		wxFourWaySplitter* mSplitter;
		RenderViewWindow* mRenderWindows[4];
		wxMenu *mViewOptionsPopupMenu;
		PreViewWindow *mPreViewWindow;
		EffectEditWindow *mEffectEditWindow;

		wxToolBar* mMainToolbar;
		wxToolBar* mEditToolbar;
		wxToolBar* mEditModeToolbar;
		wxImageList mTreeImageList;
		wxMenu *mViewMenu;
		wxMenu *mEditModeMenu;
		wxMenu *mTerrainMenu;
		wxMenu *mPhysicsMenu;
		wxMenu *mControlMenu;
		wxScrolledWindow* mCreateVolCustomPanel;
		wxScrolledWindow* mEditVolCustomPanel;
		wxStaticText* mCreateVolDescription;

		typedef std::map<int, std::string> IDStringMap;
		IDStringMap mCreateIDtoTypeMap;
		
		// inspectors
		InspectorWindow *mInspectorWindow;
		// SceneSetting
		SceneSettingWindow *mSceneSettingWindow;
	};

}

#endif