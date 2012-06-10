/*
*
* 文件名称	：	PX2ViewTopFrame.cpp
*
*/

#include "PX2ViewTopFrame.hpp"
#include "PX2ViewLogWindow.hpp"
#include "PX2PreViewWindow.hpp"
#include "PX2RenderViewWindow.hpp"
#include "PX2EffectEditWindow.hpp"
#include "PX2EditorOptions.hpp"
#include "PX2DlgNewTerrain.hpp"
#include "PX2ActorTree.hpp"
#include "PX2ResTree.hpp"
#include "PX2ControllerManager.hpp"
#include "PX2ControllerInstance.hpp"
#include "PX2ObjectPropertyGrid.hpp"
#include "PX2InspectorWindow.hpp"
#include "PX2TerrainInspector.hpp"
#include "PX2ModelInspector.hpp"
#include "PX2SceneSettingWindow.hpp"
using namespace PX2Editor;
using namespace PX2;

// 文件
#define ID_FRAMETIMER wxID_HIGHEST + 50
#define ID_NEW wxID_HIGHEST + 100
#define ID_OPEN wxID_HIGHEST + 101
#define ID_SAVE wxID_HIGHEST + 102
#define ID_SAVEAS wxID_HIGHEST + 103
#define ID_CLOSE wxID_HIGHEST + 104
#define ID_EXIT wxID_HIGHEST + 105

// 编辑
#define ID_UNDO wxID_HIGHEST + 200
#define ID_REDO wxID_HIGHEST + 201
#define ID_COPY wxID_HIGHEST + 202
#define ID_CUT wxID_HIGHEST + 203
#define ID_PASTE wxID_HIGHEST + 204
#define ID_DELETE wxID_HIGHEST + 205
#define ID_SELECT wxID_HIGHEST + 206
#define ID_MOVE wxID_HIGHEST + 207
#define ID_ROLATE wxID_HIGHEST + 208
#define ID_SCALE wxID_HIGHEST + 209

// 编辑模式
#define ID_EDITMODE_SCENE wxID_HIGHEST + 210
#define ID_EDITMODE_TERRAIN_HEIGHTEDIT wxID_HIGHEST + 211
#define ID_EDITMODE_TERRAIN_TEXTUREEDIT wxID_HIGHEST + 212
#define ID_EDITMODE_EFFECT wxID_HIGHEST + 213
#define ID_EDITMODE_MODELACTOR wxID_HIGHEST + 214

// 视图
#define ID_STAGEGRID wxID_HIGHEST + 230
#define ID_EFFECTPANE wxID_HIGHEST + 231

// 角色
#define ID_ACTOR_CREATE_EMPTY wxID_HIGHEST + 250
#define ID_ACTOR_CREATE wxID_HIGHEST + 251
#define ID_ACTOR_CREATE_SKYBOX wxID_HIGHEST + 252
#define ID_ACTOR_CREATE_WATER wxID_HIGHEST + 253
#define ID_ACTOR_CREATE_LIGHT wxID_HIGHEST + 254

// 地形
#define ID_TERRAIN_CREATE wxID_HIGHEST + 300
#define ID_TERRAIN_OPEN wxID_HIGHEST + 301
#define ID_TERRAIN_CLOSE wxID_HIGHEST + 302

// 特效
#define ID_EFFECT wxID_HIGHEST + 230

// 工具
#define ID_TOOLS_TEXTURECONVERT wxID_HIGHEST + 350

// EditTool
#define ID_EDIT_SELECTION_MODE wxID_HIGHEST + 450
#define ID_EDIT_TRANSLATE_MODE wxID_HIGHEST + 451
#define ID_EDIT_ROLATE_MODE wxID_HIGHEST + 452
#define ID_EDIT_SCALE_MODE wxID_HIGHEST + 453

#define ID_VIEW_EDIT_CREATEANDADDCUBE wxID_HIGHEST + 404
#define ID_VIEW_EDIT_CREATEANDADDSPHERE wxID_HIGHEST + 405
#define ID_VIEW_EDIT_CREATEANDADDPLANE wxID_HIGHEST + 406

#define ID_ENTITY wxID_HIGHEST + 507
#define ID_LIGHT wxID_HIGHEST + 508
#define ID_NODE wxID_HIGHEST + 509

#define ID_VIEWTYPE_TOP wxID_HIGHEST + 601
#define ID_VIEWTYPE_FRONT wxID_HIGHEST + 602
#define ID_VIEWTYPE_LEFT wxID_HIGHEST + 603
#define ID_VIEWTYPE_PERSPECTIVE wxID_HIGHEST + 604

// 物理
#define ID_PHYSICS_PLAY wxID_HIGHEST + 701

BEGIN_EVENT_TABLE(ViewTopFrame, wxFrame)
	EVT_TIMER(ID_FRAMETIMER, ViewTopFrame::OnTimer)
	EVT_MENU(ID_NEW, ViewTopFrame::OnNew)
	EVT_MENU(ID_OPEN, ViewTopFrame::OnOpen)
	EVT_MENU(ID_SAVE, ViewTopFrame::OnSave)
	EVT_MENU(ID_SAVEAS, ViewTopFrame::OnSaveAs)
	EVT_MENU(ID_UNDO, ViewTopFrame::OnUnDo)
	EVT_MENU(ID_REDO, ViewTopFrame::OnReDo)
	EVT_MENU(ID_COPY, ViewTopFrame::OnCopy)
	EVT_MENU(ID_PASTE, ViewTopFrame::OnPaste)
	EVT_MENU(ID_DELETE, ViewTopFrame::OnDelete)
	EVT_MENU(ID_EDIT_SELECTION_MODE, ViewTopFrame::OnEditSelectionModeClicked)
	EVT_MENU(ID_EDIT_TRANSLATE_MODE, ViewTopFrame::OnEditTranslateClicked)
	EVT_MENU(ID_EDIT_ROLATE_MODE, ViewTopFrame::OnEditRolateClicked)
	EVT_MENU(ID_EDIT_SCALE_MODE, ViewTopFrame::OnEditScaleClicked)
	EVT_MENU(ID_STAGEGRID, ViewTopFrame::OnStageGrid)
	EVT_MENU(ID_EFFECTPANE, ViewTopFrame::OnEffectPane)

	EVT_MENU(ID_EDITMODE_SCENE, ViewTopFrame::OnEditMode_Scene)
	EVT_MENU(ID_EDITMODE_TERRAIN_HEIGHTEDIT, ViewTopFrame::OnTerrainHeightEdit)
	EVT_MENU(ID_EDITMODE_TERRAIN_TEXTUREEDIT, ViewTopFrame::OnTerrainTextureEdit)
	EVT_MENU(ID_EDITMODE_EFFECT, ViewTopFrame::OnEditMode_Effect)
	EVT_MENU(ID_EDITMODE_MODELACTOR, ViewTopFrame::OnEditMode_ModelActor)

	EVT_MENU(ID_VIEW_EDIT_CREATEANDADDCUBE, ViewTopFrame::OnCreateAndAddCubeClicked)
	EVT_MENU(ID_VIEW_EDIT_CREATEANDADDSPHERE, ViewTopFrame::OnCreateAndAddSphereClicked)
	EVT_MENU(ID_VIEW_EDIT_CREATEANDADDPLANE, ViewTopFrame::OnCreateAndAddPlaneClicked)
	EVT_MENU(ID_ACTOR_CREATE_LIGHT, ViewTopFrame::OnCreateAndAddLightClicked)

	EVT_MENU(ID_TERRAIN_CREATE, ViewTopFrame::OnNewTerrain)


	EVT_MENU(ID_PHYSICS_PLAY, ViewTopFrame::OnPhysicsPlay)

	EVT_MENU(ID_TOOLS_TEXTURECONVERT, ViewTopFrame::OnToolsTextureConvert)

	EVT_CONTEXT_MENU(ViewTopFrame::OnContextMenu)
	EVT_MENU(ID_VIEWTYPE_TOP, ViewTopFrame::OnMenuViewTop)
	EVT_MENU(ID_VIEWTYPE_FRONT, ViewTopFrame::OnMenuViewFront)
	EVT_MENU(ID_VIEWTYPE_LEFT, ViewTopFrame::OnMenuViewLeft)
	EVT_MENU(ID_VIEWTYPE_PERSPECTIVE, ViewTopFrame::OnMenuViewPerspective)
END_EVENT_TABLE()

//----------------------------------------------------------------------------
ViewTopFrame::ViewTopFrame (const wxString title, int xPos, int yPos,
							int width, int height)
							:
wxFrame((wxFrame*)0, -1, title, wxPoint(xPos, yPos), wxSize(width, height)),
mTreeImageList(16, 16),
mViewOptionsPopupMenu(0),
mPhysicsMenu(0),
mEffectEditWindow(0)
{
	// AUI
	mAuiManager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
//	mAuiManager->GetArtProvider()->SetMetric(wxAUI_DOCKART_SASH_SIZE, 2);

	// Toolbar
	CreateMainToolbar();
	CreateViewToolbar();
	CreateEditToolbar();
	CreateEditModeToolbar();

	// Status bar
	wxStatusBar *statusbar = this->CreateStatusBar();
	PX2_UNUSED(statusbar);

	// Menu bar
	CreateMenu();
	CreatePopupMenu();

	// ImageList
	mTreeImageList.Add(wxIcon(wxT("./ToolRes/Icons/chart_organisation.png"), wxBITMAP_TYPE_PNG));
	mTreeImageList.Add(wxIcon(wxT("./ToolRes/Icons/brick.png"), wxBITMAP_TYPE_PNG));
	mTreeImageList.Add(wxIcon(wxT("./ToolRes/Icons/lightbulb.png"), wxBITMAP_TYPE_PNG));

	// Notebook
	wxNotebook* noteBook = new wxNotebook(this, wxID_ANY);
	noteBook->SetImageList(&mTreeImageList);

	// ActorTree
	ActorTree *actorTree = new ActorTree(noteBook);
	actorTree->SetImageList(&mTreeImageList);
	actorTree->RefleshScene();
	EventWorld::GetSingleton().ComeIn(actorTree);
	noteBook->AddPage(actorTree, wxEmptyString, true, 1);

	// PreView
	mPreViewWindow = new PreViewWindow(this);
	mAuiManager->AddPane(mPreViewWindow, wxAuiPaneInfo().
		Name(wxT("PreView")).Caption(wxT("PreView")).
		DefaultPane().TopDockable(false).BottomDockable(false).
		CloseButton(false).Layer(0).FloatingSize(220, 150).MinSize(200, 150));
	EventWorld::GetSingleton().ComeIn(mPreViewWindow);

	// ResTree
	ResTree *resTree = new ResTree(noteBook);
	resTree->SetImageList(&mTreeImageList);
	EventWorld::GetSingleton().ComeIn(resTree);
	resTree->UpdateOnPath("Data/");
	noteBook->AddPage(resTree, wxEmptyString, false, 1);
 
	noteBook->AddPage(new wxPanel(noteBook), wxEmptyString, false, 0);

	mAuiManager->AddPane(noteBook, wxAuiPaneInfo().
		Name(wxT("Left")).Caption(wxT("Left")).
		DefaultPane().Left().FloatingPosition(0, 150).TopDockable(false)
		.BottomDockable(false).CloseButton(false).Layer(0).MinSize(220, 100));

	// right book
	wxNotebook *rightBook = new wxNotebook(this, wxID_ANY);

	// terrain inspector
	mInspectorWindow = new InspectorWindow(rightBook);
	EventWorld::GetSingleton().ComeIn(mInspectorWindow);
	rightBook->AddPage(mInspectorWindow, "Inspector", true, 1);

	// scene setting
	mSceneSettingWindow = new SceneSettingWindow(rightBook);
	EventWorld::GetSingleton().ComeIn(mSceneSettingWindow);
	rightBook->AddPage(mSceneSettingWindow, "SceneSetting", false, 0);

	//rightBook->AddPage(mTerInspec, "PropertyGrid", true, 1);

	rightBook->SetImageList(&mTreeImageList);

	mAuiManager->AddPane(rightBook, wxAuiPaneInfo().
		Name(wxT("Right")).Caption(wxT("Right")).
		DefaultPane().Right().TopDockable(false).BottomDockable(false).
		CloseButton(false).Layer(0).MinSize(220, 100));

	// EffectEditWindow
	mEffectEditWindow = new EffectEditWindow(this);
	EventWorld::GetSingleton().ComeIn(mEffectEditWindow);
	if (EditorOptions::GetSingleton().mShowEffectEditorBar)
	{
		EditorOptions::GetSingleton().mShowEffectEditorBar = true;
		mAuiManager->AddPane(mEffectEditWindow, wxAuiPaneInfo().
			Name(wxT("EffectEdit")).Caption(wxT("EffectEdit")).
			DefaultPane().Bottom().PinButton(true).
			CloseButton(true).Layer(0).MinimizeButton(true));
		mAuiManager->Update();
		mEffectEditWindow->Show(true);
	}

	wxFileConfig config("PX2EditorConfig");
	wxString Perspective;
	if (config.Read(wxString("Perspective"), &Perspective))
	{
	//	mAuiManager->LoadPerspective(Perspective);
	}

	// spliter
	mSplitter = new wxFourWaySplitter(this,
		-1, wxDefaultPosition, wxDefaultSize, wxSP_3D);
	mSplitter->SetBackgroundColour(wxColour(128, 128, 128));
	mSplitter->Show();
	mAuiManager->AddPane(mSplitter, wxCENTER);

	// Timer
	mTimer.SetOwner(this, ID_FRAMETIMER);
	mTimer.Start(33);
}
//----------------------------------------------------------------------------
ViewTopFrame::~ViewTopFrame ()
{
	wxFileConfig config("PX2EditorConfig");
	wxString Perspective = mAuiManager->SavePerspective();
	config.Write("Perspective", Perspective);

	if (mViewOptionsPopupMenu)
		delete mViewOptionsPopupMenu;

	mAuiManager->UnInit();
	delete mAuiManager;
}
//----------------------------------------------------------------------------
void ViewTopFrame::Initialize ()
{
	// RenderViewWindow
	for (int i=0; i<4; ++i)
	{
		mRenderWindows[i] = new RenderViewWindow(mSplitter);
		mRenderWindows[i]->SetWindowIndex(i);
		mRenderWindows[i]->Initialize();
		mSplitter->SetWindow(i, mRenderWindows[i]);
		switch(i)
		{
		case 0:
			mRenderWindows[i]->SetViewType(RenderViewWindow::VT_TOP);
			break;
		case 1:
			mRenderWindows[i]->SetViewType(RenderViewWindow::VT_FRONT);
			break;
		case 2:
			mRenderWindows[i]->SetViewType(RenderViewWindow::VT_LEFT);
			break;
		case 3:
			mRenderWindows[i]->SetViewType(RenderViewWindow::VT_PERSPECTIVE);
			break;
		default:
			break;
		};

		EventWorld::GetSingleton().ComeIn(mRenderWindows[i]);
	}

	mAuiManager->Update();

	for (int i=0; i<4; ++i)
	{
		mRenderWindows[i]->InitExpand();
	}

	// SetParticleCamera
	GraphicsRoot::GetSingleton().SetCamera(mRenderWindows[3]->GetCamera());

	SetRendersScene();

	// PreView
	if (mPreViewWindow)
		mPreViewWindow->Initialize();
}
//----------------------------------------------------------------------------
void ViewTopFrame::DoEnter ()
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::DoExecute (Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::NewScene)
		|| EditorEventSpace::IsEqual(event, EditorEventSpace::LoadedScene)
		|| EditorEventSpace::IsEqual(event, EditorEventSpace::SavedScene))
	{
		SetRendersScene();
	}

	if (EditorEventSpace::IsEqual(event, EditorEventSpace::PushUnDo))
	{
		mMainToolbar->EnableTool(ID_UNDO, true);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::UnDo))
	{
		mMainToolbar->EnableTool(ID_REDO, true);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::ReDo))
	{
		mMainToolbar->EnableTool(ID_UNDO, true);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::NoUnDo))
	{
		mMainToolbar->EnableTool(ID_UNDO, false);
	}
	else if (EditorEventSpace::IsEqual(event, EditorEventSpace::NoReDo))
	{
		mMainToolbar->EnableTool(ID_REDO, false);
	}
}
//----------------------------------------------------------------------------
void ViewTopFrame::DoLeave ()
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::OnTimer (wxTimerEvent& event)
{
	EditSystem::GetSingleton().GetEventWorld()->Update();
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnNew(wxCommandEvent &e)
{
	EditSystem::GetSingleton().GetEditMap()->NewScene();

	SetRendersScene();

	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->SetInteractionMode(IM_SELECT);
	mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_HEIGHTEDIT)->Check(false);
	mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_TEXTUREEDIT)->Check(false);
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnOpen (wxCommandEvent &e)
{
	wxFileDialog dlg(this,
		wxT("Open Map"),
		wxEmptyString,
		wxEmptyString,
		wxT("map (*.pxof)|*.pxof"));

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		EditSystem::GetSingleton().GetEditMap()->LoadScene(dlg.GetPath().ToAscii());
	}

	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->SetInteractionMode(IM_SELECT);
	mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_HEIGHTEDIT)->Check(false);
	mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_TEXTUREEDIT)->Check(false);
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnSave (wxCommandEvent &e)
{
	std::string path = EditSystem::GetSingleton().GetEditMap()->GetLoadedScenePath();

	if (path != "")
	{
		EditSystem::GetSingleton().GetEditMap()->SaveScene(path);
	}
	else
	{
		wxFileDialog dlg(this,
			wxT("Save Map"),
			wxEmptyString,
			wxEmptyString,
			wxT("map (*.pxof)|*.pxof"),
			wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

		dlg.CenterOnParent();

		if (dlg.ShowModal() == wxID_OK)
		{
			EditSystem::GetSingleton().GetEditMap()->SaveScene(dlg.GetPath().ToAscii());
		}
	}
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnSaveAs (wxCommandEvent &e)
{
	wxFileDialog dlg(this,
		wxT("Save Map"),
		wxEmptyString,
		wxEmptyString,
		wxT("map (*.pxof)|*.pxof"),
		wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		EditSystem::GetSingleton().GetEditMap()->SaveSceneAs(dlg.GetPath().ToAscii());
	}
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnUnDo (wxCommandEvent &e)
{
	EditCommandManager::GetSingleton().UnDo();
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnReDo (wxCommandEvent &e)
{
	EditCommandManager::GetSingleton().ReDo();
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnCopy (wxCommandEvent &e)
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::OnPaste (wxCommandEvent &e)
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::OnDelete (wxCommandEvent &e)
{
	EditSystem::GetSingleton().GetEditMap()->RemoveSelection();
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnEditSelectionModeClicked(wxCommandEvent& e)
{
	mEditToolbar->ToggleTool(ID_EDIT_SELECTION_MODE, true);

	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->SetInteractionMode(IM_SELECT);
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnEditTranslateClicked(wxCommandEvent& e)
{
	mEditToolbar->ToggleTool(ID_EDIT_TRANSLATE_MODE, true);

	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->SetInteractionMode(IM_TRANSLATE);
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnEditRolateClicked(wxCommandEvent& e)
{
	mEditToolbar->ToggleTool(ID_EDIT_ROLATE_MODE, true);

	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->SetInteractionMode(IM_ROLATE);
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnEditScaleClicked(wxCommandEvent& e)
{
	mEditToolbar->ToggleTool(ID_EDIT_SCALE_MODE, true);

	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->SetInteractionMode(IM_SCALE);
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnStageGrid (wxCommandEvent &e)
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::OnEffectPane (wxCommandEvent &e)
{
	if (EditorOptions::GetSingleton().mShowEffectEditorBar)
	{
		EditorOptions::GetSingleton().mShowEffectEditorBar = false;
		mAuiManager->DetachPane(mEffectEditWindow);
		mAuiManager->Update();
		mEffectEditWindow->Show(false);
	}
	else
	{
		EditorOptions::GetSingleton().mShowEffectEditorBar = true;
		mAuiManager->AddPane(mEffectEditWindow, wxAuiPaneInfo().
			Name(wxT("EffectEdit")).Caption(wxT("EffectEdit")).
			DefaultPane().Bottom().PinButton(true).
			CloseButton(true).Layer(0).MinimizeButton(true));
		mAuiManager->Update();
		mEffectEditWindow->Show(true);
	}
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnCreateObjectClicked(wxCommandEvent& e)
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::OnCreateAndAddCubeClicked (wxCommandEvent& e)
{
	EditSystem::GetSingleton().GetEditMap()->NewAndAddCube("NoName");
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnCreateAndAddSphereClicked (wxCommandEvent& e)
{
	EditSystem::GetSingleton().GetEditMap()->NewAndAddSphere("NoName");
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnCreateAndAddPlaneClicked (wxCommandEvent& e)
{
	EditSystem::GetSingleton().GetEditMap()->NewAndAddPlane("NoName");
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnCreateAndAddLightClicked (wxCommandEvent& e)
{
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnContextMenu(wxContextMenuEvent& event)
{
	//wxPoint popupPos = wxGetMousePosition();
	//popupPos = ScreenToClient(popupPos);
	//if (mViewOptionsPopupMenu)
	//	this->PopupMenu(mViewOptionsPopupMenu, popupPos.x, popupPos.y);
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnMenuViewTop(wxCommandEvent& event)
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::OnMenuViewFront(wxCommandEvent& event)
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::OnMenuViewLeft(wxCommandEvent& event)
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::OnMenuViewPerspective(wxCommandEvent& event)
{

}
//----------------------------------------------------------------------------
void ViewTopFrame::OnNewTerrain (wxCommandEvent &e)
{
	DlgNewTerrain dlg(this);
	if( dlg.ShowModal() == wxID_OK )
	{
		EditSystem::GetSingleton().GetEditMap()->NewAndAddTerrain(
			dlg.mValue_TerrainName, dlg.mValue_TerrainWidth, 
			dlg.mValue_PageWidth+1, dlg.mValue_GridSpace);
	}
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnTerrainHeightEdit (wxCommandEvent &e)
{
	InteractionMode mode = ControllerManager::GetSingleton()
		.GetCurrentControllerInstance()->GetInteractionMode();

	if (mode != IM_TERRAINHEIGHT)
	{
		mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_TEXTUREEDIT)->Check(false);

		PX2::ScenePtr scene = EditSystem::GetSingleton().GetEditMap()->GetScene();

		if (scene)
		{ 
			PX2::RawTerrainActorPtr terActor = scene->GetRawTerrainActor();
			if (terActor)
			{
				ControllerManager::GetSingleton().GetCurrentControllerInstance()
					->SetInteractionMode(IM_TERRAINHEIGHT);
				EditSystem::GetSingleton().SetEditMode(EditSystem::EM_TERRAIN_HEIGHT);

				ActorSelection::GetSingleton().Clear();
				ActorSelection::GetSingleton().AddActor(terActor);

				mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_HEIGHTEDIT)->Check();
			}
			else
			{
				mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_HEIGHTEDIT)->Check(false);
			}
		}
		else
		{
			mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_HEIGHTEDIT)->Check(false);
		}
	}
	else
	{
		ControllerManager::GetSingleton().GetCurrentControllerInstance()
			->SetInteractionMode(IM_SELECT);

		mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_HEIGHTEDIT)->Check(false);
	}
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnTerrainTextureEdit (wxCommandEvent &e)
{
	InteractionMode mode = ControllerManager::GetSingleton()
		.GetCurrentControllerInstance()->GetInteractionMode();

	if (mode != IM_TERRAINTEXTURE)
	{
		mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_HEIGHTEDIT)->Check(false);

		PX2::ScenePtr scene = EditSystem::GetSingleton().GetEditMap()->GetScene();

		if (scene)
		{ 
			PX2::RawTerrainActorPtr terActor = scene->GetRawTerrainActor();
			if (terActor)
			{
				ControllerManager::GetSingleton().GetCurrentControllerInstance()
					->SetInteractionMode(IM_TERRAINTEXTURE);
				EditSystem::GetSingleton().SetEditMode(EditSystem::EM_TERRAIN_TEXTURE);

				ActorSelection::GetSingleton().Clear();
				ActorSelection::GetSingleton().AddActor(terActor);

				mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_TEXTUREEDIT)->Check();
			}
			else
			{
				mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_TEXTUREEDIT)->Check(false);
			}
		}
		else
		{
			mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_TEXTUREEDIT)->Check(false);
		}
	}
	else
	{
		ControllerManager::GetSingleton().GetCurrentControllerInstance()
			->SetInteractionMode(IM_SELECT);

		mEditModeMenu->FindItem(ID_EDITMODE_TERRAIN_TEXTUREEDIT)->Check(false);
	}
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnEditMode_Scene (wxCommandEvent& e)
{
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->SetInteractionMode(IM_SELECT);
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_SELECT);
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnEditMode_Effect (wxCommandEvent& e)
{
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->SetInteractionMode(IM_SELECT);
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_EFFECT);
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnEditMode_ModelActor (wxCommandEvent& e)
{
	ControllerManager::GetSingleton().GetCurrentControllerInstance()
		->SetInteractionMode(IM_SELECT);
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_SELECT);
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnPhysicsPlay (wxCommandEvent &e)
{
	PX2::Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();
	if (scene)
	{
		bool enable = scene->IsPhysicsSimulateion();
		enable = !enable;
		scene->EnablePhysicsSimulation(enable);

		mPhysicsMenu->FindItem(ID_PHYSICS_PLAY)->Check(enable);

		if (enable)
			EditSystem::GetSingleton().SetEditMode(EditSystem::EM_PHYSICSPLAY);
		else
			EditSystem::GetSingleton().SetEditMode(EditSystem::EM_NONE);
	}
}
//----------------------------------------------------------------------------
void ViewTopFrame::OnToolsTextureConvert (wxCommandEvent &e)
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_TEXTURECONVERT);
}
//----------------------------------------------------------------------------
void ViewTopFrame::CreateMainToolbar ()
{
	mMainToolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, 
		wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
	mMainToolbar->SetToolBitmapSize(wxSize(16, 16));

	mMainToolbar->AddTool(ID_NEW, _("New"), 
		wxBitmap( wxT("./ToolRes/Icons/page_world.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddTool(ID_OPEN, _("Open"), 
		wxBitmap( wxT("./ToolRes/Icons/folder_page.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddSeparator();

	mMainToolbar->AddTool(ID_COPY, _("Copy"), 
		wxBitmap( wxT("./ToolRes/Icons/page_copy.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddTool(ID_CUT, _("Cut"), 
		wxBitmap( wxT("./ToolRes/Icons/cut.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddTool(ID_PASTE, _("Paste"), 
		wxBitmap( wxT("./ToolRes/Icons/page_paste.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddSeparator();

	mMainToolbar->AddTool(ID_UNDO, _("Undo"), 
		wxBitmap( wxT("./ToolRes/Icons/arrow_turn_left.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );
	mMainToolbar->EnableTool(ID_UNDO, false);

	mMainToolbar->AddTool(ID_REDO, _("Redo"), 
		wxBitmap( wxT("./ToolRes/Icons/arrow_turn_right.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );
	mMainToolbar->EnableTool(ID_REDO, false);

	mMainToolbar->Realize();

	mAuiManager->AddPane(mMainToolbar, wxAuiPaneInfo().
		Name(wxT("tb1")).Caption(wxT("Main Toolbar")).
		ToolbarPane().Top().LeftDockable(false).RightDockable(false));
}
//----------------------------------------------------------------------------
void ViewTopFrame::CreateViewToolbar ()
{
	//mViewToolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, 
	//	wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
	//mViewToolbar->SetToolBitmapSize(wxSize(16, 16));
	////mViewToolbar->AddRadioTool(ID_EDIT_SELECTION_MODE, _("Selection Mode"), 
	////	wxBitmap( wxT("./ToolRes/Icons/pointer.gif"), wxBITMAP_TYPE_GIF), 
	////	wxNullBitmap, _("Selection Mode"));
	//mViewToolbar->AddRadioTool(ID_EDIT_SCALE_MODE, _("Edit Object Mode"), 
	//	wxBitmap( wxT("./ToolRes/Icons/shape_square_edit.png"), wxBITMAP_TYPE_PNG), 
	//	wxNullBitmap, _("Edit Object Mode"));
	//mViewToolbar->AddRadioTool(ID_EDIT_TRANSLATE_MODE, _("Targetted Camera Mode"), 
	//	wxBitmap( wxT("./ToolRes/Icons/camera_targetted.png"), wxBITMAP_TYPE_PNG), 
	//	wxNullBitmap, _("Targetted Camera Mode"));
	//mViewToolbar->AddRadioTool(ID_EDIT_ROLATE_MODE, _("First-person Camera Mode"), 
	//	wxBitmap( wxT("./ToolRes/Icons/camera_direct.png"), wxBITMAP_TYPE_PNG), 
	//	wxNullBitmap, _("First-person Camera Mode"));

	//mViewToolbar->Realize();

	//mAuiManager->AddPane(mViewToolbar, wxAuiPaneInfo().
	//	Name(wxT("tb2")).Caption(wxT("View Toolbar")).
	//	ToolbarPane().Top().LeftDockable(false).RightDockable(false));
}
//----------------------------------------------------------------------------
void ViewTopFrame::CreateEditToolbar ()
{
	mEditToolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, 
		wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
	mEditToolbar->SetToolBitmapSize(wxSize(16, 16));
	
	mEditToolbar->AddTool(ID_EDIT_SELECTION_MODE, _("Select"), 
		wxBitmap(wxT("./ToolRes/Icons/select.png"), wxBITMAP_TYPE_PNG),
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);

	mEditToolbar->AddTool(ID_EDIT_TRANSLATE_MODE, _("Translate"), 
		wxBitmap(wxT("./ToolRes/Icons/translate.bmp"), wxBITMAP_TYPE_BMP),
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);

	mEditToolbar->AddTool(ID_EDIT_ROLATE_MODE, _("Rolate"), 
		wxBitmap(wxT("./ToolRes/Icons/rolate.bmp"), wxBITMAP_TYPE_BMP),
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);

	mEditToolbar->AddTool(ID_EDIT_SCALE_MODE, _("Scale"), 
		wxBitmap(wxT("./ToolRes/Icons/scale.bmp"), wxBITMAP_TYPE_BMP),
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);

	mEditToolbar->AddTool(ID_VIEW_EDIT_CREATEANDADDCUBE, _("Cube"),
		wxBitmap(wxT("./ToolRes/Icons/scenenode_cube.bmp"), wxBITMAP_TYPE_BMP), 
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
	mEditToolbar->AddTool(ID_VIEW_EDIT_CREATEANDADDSPHERE, _("Sphere"),
		wxBitmap(wxT("./ToolRes/Icons/scenenode_sphere.bmp"), wxBITMAP_TYPE_BMP), 
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
	mEditToolbar->AddTool(ID_VIEW_EDIT_CREATEANDADDPLANE, _("Plane"),
		wxBitmap(wxT("./ToolRes/Icons/sceneNode_plane.bmp"), wxBITMAP_TYPE_BMP), 
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);

	mEditToolbar->Realize();

	mAuiManager->AddPane(mEditToolbar, wxAuiPaneInfo().
		Name(wxT("tb3")).Caption(wxT("Object Toolbar")).
		ToolbarPane().Top().LeftDockable(false).RightDockable(false));
}
//----------------------------------------------------------------------------
void ViewTopFrame::CreateEditModeToolbar ()
{
	mEditModeToolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, 
		wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
	mEditModeToolbar->SetToolBitmapSize(wxSize(16, 16));

	mEditModeToolbar->AddTool(ID_EDITMODE_SCENE, _("EditScene"), 
		wxBitmap(wxT("./ToolRes/Icons/select.png"), wxBITMAP_TYPE_PNG),
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);

	mEditModeToolbar->AddTool(ID_EDITMODE_TERRAIN_HEIGHTEDIT, _("EditTerrainHeight"), 
		wxBitmap(wxT("./ToolRes/Icons/editmode_terrainheight.png"), wxBITMAP_TYPE_PNG),
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);

	mEditModeToolbar->AddTool(ID_EDITMODE_TERRAIN_TEXTUREEDIT, _("EditTerrainTexture"), 
		wxBitmap(wxT("./ToolRes/Icons/editmode_terraintexture.png"), wxBITMAP_TYPE_PNG),
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);

	mEditModeToolbar->AddTool(ID_EDITMODE_EFFECT, _("EditEffect"), 
		wxBitmap(wxT("./ToolRes/Icons/editmode_effect.png"), wxBITMAP_TYPE_PNG),
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);

	mEditModeToolbar->AddTool(ID_EDITMODE_EFFECT, _("EditModelActor"), 
		wxBitmap(wxT("./ToolRes/Icons/editmode_modelactor.png"), wxBITMAP_TYPE_PNG),
		wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);

	mEditModeToolbar->Realize();

	mAuiManager->AddPane(mEditModeToolbar, wxAuiPaneInfo().
		Name(wxT("EditModeTooBar")).Caption(wxT("EditModeTooBar")).
		ToolbarPane().Top().LeftDockable(false).RightDockable(false));
}
//----------------------------------------------------------------------------
void ViewTopFrame::CreateMenu ()
{
	wxMenuBar* menubar = new wxMenuBar();
	wxMenu* mnu = new wxMenu();
	menubar->Append(mnu, _("File"));
	mnu->Append(ID_NEW,_("New"));
	mnu->Append(ID_OPEN,_("Open"));
	mnu->Append(ID_SAVE,_("Save"));
	mnu->Append(ID_SAVEAS,_("Save as"));
	mnu->Append(ID_EXIT, _("Exist"));

	mnu = new wxMenu();
	menubar->Append(mnu, _("Edit"));
	mnu->Append(ID_UNDO, _("Undo"));
	mnu->Append(ID_REDO, _("Redo"));
	mnu->AppendSeparator();
	mnu->Append(ID_COPY, _("Copy"));
	mnu->Append(ID_CUT, _("Cut"));
	mnu->Append(ID_PASTE, _("Paste"));
	mnu->Append(ID_DELETE, _("Cut"));
	mnu->AppendSeparator();
	mnu->Append(ID_SELECT, "Select");
	mnu->Append(ID_MOVE, "Move");
	mnu->Append(ID_ROLATE, "Rolate");
	mnu->Append(ID_SCALE, "Scale");
	mnu->AppendSeparator();
	
	mEditModeMenu = new wxMenu();
	menubar->Append(mEditModeMenu, _("Mode"));
	mEditModeMenu->Append(ID_EDITMODE_SCENE, "Scene");
	mEditModeMenu->Append(ID_EDITMODE_EFFECT, "Effect");
	mEditModeMenu->Append(ID_EDITMODE_MODELACTOR, "ModelActor");
	mEditModeMenu->AppendSeparator();
	wxMenuItem *heightItem = mEditModeMenu->Append(
		ID_EDITMODE_TERRAIN_HEIGHTEDIT, "TerrainHeight");
	heightItem->SetCheckable(true);
	wxMenuItem *textureItem = mEditModeMenu->Append(
		ID_EDITMODE_TERRAIN_TEXTUREEDIT, "TerrainTexture");
	textureItem->SetCheckable(true);

	mViewMenu = new wxMenu();
	menubar->Append(mViewMenu, _("View"));
	mViewMenu->Append(ID_STAGEGRID, _("StageGrid"));
	mViewMenu->Append(ID_EFFECTPANE, _("EffectEditBar"));

	mnu = new wxMenu();
	menubar->Append(mnu, _("Actor"));
	mnu->Append(ID_ACTOR_CREATE_EMPTY, _("Empty"));
	wxMenu *subActorCreate = new wxMenu();
	subActorCreate->Append(ID_ACTOR_CREATE_SKYBOX, _("Sky"));
	subActorCreate->Append(ID_ACTOR_CREATE_WATER, _("Water"));
	subActorCreate->Append(ID_ACTOR_CREATE_LIGHT, _("Light"));
	mnu->Append(ID_ACTOR_CREATE, _("Create"), subActorCreate);
	
	mTerrainMenu = new wxMenu();
	menubar->Append(mTerrainMenu, _("Terrain"));
	mTerrainMenu->Append(ID_TERRAIN_CREATE, "Create");
	mTerrainMenu->Append(ID_TERRAIN_OPEN, "Open");
	mTerrainMenu->Append(ID_TERRAIN_CLOSE, "Save");

	mPhysicsMenu = new wxMenu();
	menubar->Append(mPhysicsMenu, _("Physics"));
	wxMenuItem *physicsPlayItem = mPhysicsMenu->Append(ID_PHYSICS_PLAY, "Run");
	physicsPlayItem->SetCheckable(true);

	mnu = new wxMenu();
	menubar->Append(mnu, _("Tools"));
	mnu->Append(ID_TOOLS_TEXTURECONVERT, _("TextureConvert"));
	
	mnu = new wxMenu();
	menubar->Append(mnu, _("Help"));

	this->SetMenuBar(menubar);
}
//----------------------------------------------------------------------------
void ViewTopFrame::CreatePopupMenu()
{
	mViewOptionsPopupMenu = new wxMenu();	mViewOptionsPopupMenu->Append(ID_VIEWTYPE_TOP, _("Top"));	mViewOptionsPopupMenu->Append(ID_VIEWTYPE_FRONT, _("Front"));	mViewOptionsPopupMenu->Append(ID_VIEWTYPE_LEFT, _("Left"));	mViewOptionsPopupMenu->Append(ID_VIEWTYPE_PERSPECTIVE, _("Perspective"));
}
//----------------------------------------------------------------------------
void ViewTopFrame::SetRendersScene ()
{
	for (int i=0; i<4; i++)
	{
		Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();
		Node *sceneNode = scene->GetSceneNode();

		PX2::Node *helpScene = EditSystem::GetSingleton().GetHelpScene();

		if (sceneNode)
		{
			mRenderWindows[i]->SetScene(sceneNode);
			mRenderWindows[i]->SetHelpScene(helpScene);
		}
	}
}
//----------------------------------------------------------------------------