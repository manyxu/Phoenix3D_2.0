/*
*
* ÎÄ¼þÃû³Æ	£º	PX2MainFrame.cpp
*
*/

#include "PX2MainFrame.hpp"
#include "PX2RenderViewWindow.hpp"
#include "PX2PreViewWindow.hpp"
#include "PX2ResTreePanel.hpp"
#include "PX2InspectorWindow.hpp"
#include "PX2ObjectTree.hpp"
#include "PX2CurveEditWindow.hpp"
#include "PX2ViewCtrlInstMan.hpp"
#include "PX2DlgTerainNew.hpp"
#include "PX2EditSystem.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2Project.hpp"
#include "PX2DlgCreateProject.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_FILE_PROJECT_NEW wxID_HIGHEST + 1001
#define ID_FILE_PROJECT_OPEN wxID_HIGHEST + 1002
#define ID_FILE_PROJECT_SAVE wxID_HIGHEST + 1003
#define ID_FILE_PROJECT_SAVEAS wxID_HIGHEST + 1004
#define ID_FILE_PROJECT_CLOSE wxID_HIGHEST + 1005
#define ID_FILE_SCENE_NEW wxID_HIGHEST + 1006
#define ID_FILE_SCENE_OPEN wxID_HIGHEST + 1007
#define ID_FILE_SCENE_SAVE wxID_HIGHEST + 1008
#define ID_FILE_SCENE_SAVEAS wxID_HIGHEST + 1009
#define ID_FILE_SCENE_CLOSE wxID_HIGHEST + 1010
#define ID_FILE_EXPORTSELECTED wxID_HIGHEST + 1012
#define ID_FILE_EXIT wxID_HIGHEST + 1013

#define ID_EDIT_UNDO wxID_HIGHEST + 1101
#define ID_EDIT_REDO wxID_HIGHEST + 1102
#define ID_EDIT_COPY wxID_HIGHEST + 1103
#define ID_EDIT_CUT wxID_HIGHEST + 1104
#define ID_EDIT_PASTE wxID_HIGHEST + 1105
#define ID_EDIT_DELETE wxID_HIGHEST + 1106
#define ID_EDIT_SELECT wxID_HIGHEST + 1107
#define ID_EDIT_MOVE wxID_HIGHEST + 1108
#define ID_EDIT_ROLATE wxID_HIGHEST + 1109
#define ID_EDIT_SCALE wxID_HIGHEST + 1110
#define ID_EDIT_EDIT wxID_HIGHEST + 1111

#define ID_VIEW_STAGE wxID_HIGHEST + 1201
#define ID_VIEW_ACTORTREE wxID_HIGHEST + 1202
#define ID_VIEW_PREVIEW wxID_HIGHEST + 1203
#define ID_VIEW_RESTREE wxID_HIGHEST + 1204
#define ID_VIEW_INSPECTOR wxID_HIGHEST + 1205
#define ID_VIEW_CURVEEDIT wxID_HIGHEST + 1206
#define ID_VIEW_CENTRE wxID_HIGHEST + 1207

#define ID_CREATE_BOX wxID_HIGHEST + 1251
#define ID_CREATE_SPHERE wxID_HIGHEST + 1252
#define ID_CREATE_EFFECT wxID_HIGHEST + 1253
#define ID_CREATE_CTRL_TRANSFORM wxID_HIGHEST + 1254
#define ID_CREATE_CTRL_COLOR wxID_HIGHEST + 1255
#define ID_CREATE_CTRL_ALPHA wxID_HIGHEST + 1256

#define ID_TERRAIN_NEW wxID_HIGHEST + 1401
#define ID_TERRAIN_COMPOSEMTL wxID_HIGHEST + 1402
#define ID_TERRAIN_USELOD wxID_HIGHEST + 1403
#define ID_TERRAIN_USECOMPOSEDMTL wxID_HIGHEST + 1404

#define ID_PLAYINEDITOR wxID_HIGHEST + 1501
#define ID_PLAY wxID_HIGHEST + 1502
#define ID_PLAYCONFIG wxID_HIGHEST + 1503

#define ID_FRAMETIMER wxID_HIGHEST+1999
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_TIMER(ID_FRAMETIMER, MainFrame::OnTimer)
	EVT_MENU(ID_FILE_PROJECT_NEW, MainFrame::OnNewProject)
	EVT_MENU(ID_FILE_PROJECT_OPEN, MainFrame::OnOpenProject)
	EVT_MENU(ID_FILE_PROJECT_SAVE, MainFrame::OnSaveProject)
	EVT_MENU(ID_FILE_PROJECT_SAVEAS, MainFrame::OnSaveProjectAs)
	EVT_MENU(ID_FILE_PROJECT_CLOSE, MainFrame::OnCloseProject)
	EVT_MENU(ID_FILE_SCENE_NEW, MainFrame::OnNewScene)
	EVT_MENU(ID_FILE_SCENE_OPEN, MainFrame::OnOpenScene)
	EVT_MENU(ID_FILE_SCENE_SAVE, MainFrame::OnSaveScene)
	EVT_MENU(ID_FILE_SCENE_SAVEAS, MainFrame::OnSaveSceneAs)
	EVT_MENU(ID_FILE_SCENE_CLOSE, MainFrame::OnCloseScene)
	EVT_MENU(ID_EDIT_UNDO, MainFrame::OnUnDo)
	EVT_MENU(ID_EDIT_REDO, MainFrame::OnReDo)
	EVT_MENU(ID_EDIT_SELECT, MainFrame::OnEditSelect)
	EVT_MENU(ID_EDIT_MOVE, MainFrame::OnEditTranslate)
	EVT_MENU(ID_EDIT_ROLATE, MainFrame::OnEditRolate)
	EVT_MENU(ID_EDIT_SCALE, MainFrame::OnEditScale)
	EVT_MENU(ID_EDIT_EDIT, MainFrame::OnEditEdit)
	EVT_MENU(ID_EDIT_DELETE, MainFrame::OnEditDelete)
	EVT_MENU(ID_VIEW_STAGE, MainFrame::OnViewStage)
	EVT_MENU(ID_VIEW_ACTORTREE, MainFrame::OnViewActorTree)
	EVT_MENU(ID_VIEW_PREVIEW, MainFrame::OnViewPreView)
	EVT_MENU(ID_VIEW_RESTREE, MainFrame::OnViewResTree)
	EVT_MENU(ID_VIEW_INSPECTOR, MainFrame::OnViewInspector)
	EVT_MENU(ID_VIEW_CURVEEDIT, MainFrame::OnViewCurveEdit)
	EVT_MENU(ID_VIEW_CENTRE, MainFrame::OnViewCentre)
	EVT_MENU(ID_CREATE_BOX, MainFrame::OnCreateBox)
	EVT_MENU(ID_CREATE_SPHERE, MainFrame::OnCreateSphere)
	EVT_MENU(ID_CREATE_EFFECT, MainFrame::OnCreateEffect)
	EVT_MENU(ID_CREATE_CTRL_TRANSFORM, MainFrame::OnCreateCtrlTransform)
	EVT_MENU(ID_CREATE_CTRL_COLOR, MainFrame::OnCreateCtrlColor)
	EVT_MENU(ID_CREATE_CTRL_ALPHA, MainFrame::OnCreateCtrlAlpha)
	EVT_MENU(ID_TERRAIN_NEW, MainFrame::OnTerrainNew)
	EVT_MENU(ID_TERRAIN_COMPOSEMTL, MainFrame::OnTerrainComposeMtl)
	EVT_MENU(ID_TERRAIN_USELOD, MainFrame::OnTerrainUseLod)
	EVT_MENU(ID_TERRAIN_USECOMPOSEDMTL, MainFrame::OnTerrainUseComposeMtl)
	EVT_MENU(ID_PLAY, MainFrame::OnGamePlay)
END_EVENT_TABLE();
//----------------------------------------------------------------------------
MainFrame::MainFrame (const wxString title, int xPos, int yPos,
	int width, int height)
	:
wxFrame((wxFrame*)0, -1, title, wxPoint(xPos, yPos), wxSize(width, height)),
	mMainMenu(0),
	mAuiManager(0),
	mMainToolbar(0),
	mRenderView(0),
	mPreView(0),
	mObjectTree(0),
	mResTreePanel(0),
	mInspector(0),
	mInited(false)
{
	Initlize();

	Maximize();
}
//----------------------------------------------------------------------------
MainFrame::~MainFrame ()
{
	wxFileConfig config("PX2EditorConfig");
	wxString Perspective = mAuiManager->SavePerspective();
	config.Write("Perspective", Perspective);

	if (mAuiManager)
	{
		mAuiManager->UnInit();
		delete mAuiManager;
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnTimer (wxTimerEvent& event)
{
	if (mInited)
	{
		int ival = event.GetInterval();
		double dIval = ival/1000.0;

		EditSystem::GetSingleton().Update(dIval);
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnNewProject (wxCommandEvent &e)
{
	DlgCreateProject dlg(mRenderView);
	if (wxID_OK == dlg.ShowModal())
	{
		std::string name = dlg.mProjName;
		std::string projPath = dlg.mProjPath;
		int width = dlg.mProjWidth;
		int height = dlg.mProjHeight;

		std::string path = projPath + "/" + name + ".px2proj";

		EditSystem::GetSingleton().GetEditMap()->NewProject(path.c_str(),
			name.c_str(), width, height);

		EnableEditAll(true);
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnOpenProject (wxCommandEvent &e)
{
	wxFileDialog dlg(mRenderView,
		wxT("Open project"),
		wxEmptyString,
		wxEmptyString,
		wxT("Project (*.px2proj)|*.px2proj"));

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		if (EditSystem::GetSingleton().GetEditMap()->LoadProject(dlg.GetPath()))
		{
			EnableEditAll(true);

			ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
				->SetInteractionMode(IM_GENERAL);
		}
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnSaveProject (wxCommandEvent &e)
{
	EditMap *map = EditSystem::GetSingleton().GetEditMap();
	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		if (proj->GetScene())
		{
			OnSaveScene(wxCommandEvent());
		}
	}

	map->SaveProject();
}
//----------------------------------------------------------------------------
void MainFrame::OnSaveProjectAs (wxCommandEvent &e)
{
	// save scene first
	EditMap *map = EditSystem::GetSingleton().GetEditMap();
	Project *proj = Project::GetSingletonPtr();
	if (proj)
	{
		if (proj->GetScene() && proj->GetSceneFilename()=="")
		{
			OnSaveSceneAs(wxCommandEvent());
		}
	}

	wxFileDialog dlg(mRenderView,
		wxT("Save project"),
		wxEmptyString,
		wxEmptyString,
		wxT("Project (*.px2proj)|*.px2proj"),
		wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		map->SaveProjectAs(dlg.GetPath());
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnCloseProject (wxCommandEvent &e)
{
	EditSystem::GetSingleton().GetEditMap()->CloseProject();
	EnableEditAll(false);
}
//----------------------------------------------------------------------------
void MainFrame::OnNewScene (wxCommandEvent &e)
{
	EditMap *map = EditSystem::GetSingleton().GetEditMap();
	map->NewScene();

	if (Project::GetSingletonPtr())
		mRenderView->SetScene(
		Project::GetSingleton().GetScene()->GetSceneNode());

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->SetInteractionMode(IM_GENERAL);
}
//----------------------------------------------------------------------------
void MainFrame::OnOpenScene (wxCommandEvent &e)
{
	wxFileDialog dlg(mRenderView,
		wxT("Open scene"),
		wxEmptyString,
		wxEmptyString,
		wxT("scene (*.px2scene)|*.px2scene"));

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		EditSystem::GetSingleton().GetEditMap()->LoadScene(dlg.GetPath());
	}

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->SetInteractionMode(IM_GENERAL);
}
//----------------------------------------------------------------------------
void MainFrame::OnSaveScene (wxCommandEvent &e)
{
	std::string path;
	if (Project::GetSingletonPtr())
		path = Project::GetSingleton().GetSceneFilename();

	if (path != "")
	{
		EditSystem::GetSingleton().GetEditMap()->SaveScene(path.c_str());
	}
	else
	{
		wxFileDialog dlg(mRenderView,
			wxT("Save scene"),
			wxEmptyString,
			wxEmptyString,
			wxT("scene (*.px2scene)|*.px2scene"),
			wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

		dlg.CenterOnParent();

		if (dlg.ShowModal() == wxID_OK)
		{
			EditSystem::GetSingleton().GetEditMap()->SaveScene(dlg.GetPath());
		}
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnSaveSceneAs (wxCommandEvent &e)
{
	wxFileDialog dlg(mRenderView,
		wxT("Save scene"),
		wxEmptyString,
		wxEmptyString,
		wxT("scene (*.px2scene)|*.px2scene"),
		wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		EditSystem::GetSingleton().GetEditMap()->SaveSceneAs(dlg.GetPath());
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnCloseScene (wxCommandEvent &e)
{
	EditMap *map = EditSystem::GetSingleton().GetEditMap();
	if (map)
	{
		map->CloseScene();
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnImport (wxCommandEvent &e)
{

}
//----------------------------------------------------------------------------
void MainFrame::OnExportSelected (wxCommandEvent &e)
{

}
//----------------------------------------------------------------------------
void MainFrame::OnSave (wxCommandEvent &e)
{

}
//----------------------------------------------------------------------------
void MainFrame::OnExist (wxCommandEvent &e)
{
	if (wxYES == wxMessageBox(PX2_LM.GetValue("Tip2"),
		PX2_LM.GetValue("Tip0"), wxYES_NO))
	{
		wxExit();
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnUnDo (wxCommandEvent &e)
{
	EditSystem::GetSingleton().GetCM()->UnDo();
}
//----------------------------------------------------------------------------
void MainFrame::OnReDo (wxCommandEvent &e)
{
	EditSystem::GetSingleton().GetCM()->ReDo();
}
//----------------------------------------------------------------------------
void MainFrame::OnEditSelect (wxCommandEvent& e)
{
	if (EditSystem::EM_TERRAIN == EditSystem::GetSingleton().GetEditMode())
		return;

	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_SELECT);
}
//----------------------------------------------------------------------------
void MainFrame::OnEditTranslate (wxCommandEvent& e)
{
	if (EditSystem::EM_TERRAIN == EditSystem::GetSingleton().GetEditMode())
		return;

	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_TRANSLATE);
}
//----------------------------------------------------------------------------
void MainFrame::OnEditRolate (wxCommandEvent& e)
{
	if (EditSystem::EM_TERRAIN == EditSystem::GetSingleton().GetEditMode())
		return;

	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_ROLATE);
}
//----------------------------------------------------------------------------
void MainFrame::OnEditScale (wxCommandEvent& e)
{
	if (EditSystem::EM_TERRAIN == EditSystem::GetSingleton().GetEditMode())
		return;

	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_SCALE);
}
//----------------------------------------------------------------------------
void MainFrame::OnEditEdit (wxCommandEvent& e)
{
	EditSystem::GetSingleton().EnableSelectEdit(!EditSystem::GetSingleton()
		.IsSelectEditEnable());

	EditSystem::EditMode mode = EditSystem::GetSingleton().GetEditMode();
	if (EditSystem::EM_TERRAIN == mode)
	{
		ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
			->SetInteractionMode(IM_TEREDIT);
	}
	else
	{
		ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
			->SetInteractionMode(IM_GENERAL);
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnEditDelete (wxCommandEvent& e)
{
	if (!EditSystem::GetSingleton().DeleteSelection())
	{
		wxMessageBox(PX2_LM.GetValue("Tip3"),PX2_LM.GetValue("Tip0"), wxOK);
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnViewCentre (wxCommandEvent& e)
{
	mAuiManager->GetPane(mRenderView).Dock().Centre();
	mAuiManager->Update();
}
//----------------------------------------------------------------------------
void MainFrame::OnViewStage (wxCommandEvent& e)
{
	wxAuiPaneInfo &info = mAuiManager->GetPane(mRenderView);
	info.Show(!info.IsShown());
	mAuiManager->Update();

	if (info.IsShown())
	{
		info.window->SetFocus();
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnViewActorTree (wxCommandEvent& e)
{
	wxAuiPaneInfo &info = mAuiManager->GetPane(mObjectTree);
	info.Show(!info.IsShown());
	mAuiManager->Update();

	if (info.IsShown())
	{
		info.window->SetFocus();
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnViewPreView (wxCommandEvent& e)
{
	wxAuiPaneInfo &info = mAuiManager->GetPane(mPreView);
	info.Show(!info.IsShown());
	mAuiManager->Update();

	if (info.IsShown())
	{
		info.window->SetFocus();
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnViewResTree (wxCommandEvent& e)
{
	wxAuiPaneInfo &info = mAuiManager->GetPane(mResTreePanel);
	info.Show(!info.IsShown());
	mAuiManager->Update();

	if (info.IsShown())
	{
		info.window->SetFocus();
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnViewInspector (wxCommandEvent& e)
{
	wxAuiPaneInfo &info = mAuiManager->GetPane(mInspector);
	info.Show(!info.IsShown());
	mAuiManager->Update();

	if (info.IsShown())
	{
		info.window->SetFocus();
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnViewCurveEdit (wxCommandEvent& e)
{
	wxAuiPaneInfo &info = mAuiManager->GetPane(mCurveEditWindow);
	info.Show(!info.IsShown());
	mAuiManager->Update();

	if (info.IsShown())
	{
		info.window->SetFocus();
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnCreateBox (wxCommandEvent& e)
{
	PX2_UNUSED(e);
	EditSystem::GetSingleton().GetEditMap()->CreateBox(APoint::ORIGIN);
}
//----------------------------------------------------------------------------
void MainFrame::OnCreateSphere (wxCommandEvent& e)
{
	PX2_UNUSED(e);
	EditSystem::GetSingleton().GetEditMap()->CreateSphere(APoint::ORIGIN);
}
//----------------------------------------------------------------------------
void MainFrame::OnCreateEffect (wxCommandEvent& e)
{
	PX2_UNUSED(e);
	EditSystem::GetSingleton().GetEditMap()->CreateEffect(APoint::ORIGIN);
}
//----------------------------------------------------------------------------
void MainFrame::OnCreateCtrlTransform (wxCommandEvent& e)
{
	ObjectSelection *objSelection = EditSystem::GetSingleton().GetSelection();
	int numObjects = objSelection->GetNumObjects();
	if (1 != numObjects)
		return;

	Movable *mov = DynamicCast<Movable>(objSelection->GetObjectAt(0));
	if (mov)
	{
		EditSystem::GetSingleton().GetEditMap()->CreateCurveTransCtrl(mov);
	}
	else
	{
		wxMessageBox(PX2_LM.GetValue("Tip6"),PX2_LM.GetValue("Tip0"), wxOK);
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnCreateCtrlColor (wxCommandEvent& e)
{

}
//----------------------------------------------------------------------------
void MainFrame::OnCreateCtrlAlpha (wxCommandEvent& e)
{

}
//----------------------------------------------------------------------------
void MainFrame::OnTerrainNew (wxCommandEvent &e)
{
	DlgTerrainNew dlg(mRenderView);
	if (dlg.ShowModal() == wxID_OK)
	{
		EditSystem::GetSingleton().GetEditMap()->CreateTerrain(
			dlg.mValue_TerrainName, dlg.mValue_TerrainWidth,
			dlg.mValue_PageWidth+1, dlg.mValue_GridSpace);
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnTerrainComposeMtl (wxCommandEvent &e)
{

}
//----------------------------------------------------------------------------
void MainFrame::OnTerrainUseLod (wxCommandEvent &e)
{
	bool useLod = EditSystem::GetSingleton().GetTerrainEdit()
		->IsUseLodTerrain();

	EditSystem::GetSingleton().GetTerrainEdit()->UseLodTerrain(!useLod);
	mMainMenu->Check(ID_TERRAIN_USELOD, !useLod);
}
//----------------------------------------------------------------------------
void MainFrame::OnTerrainUseComposeMtl (wxCommandEvent &e)
{

}
//----------------------------------------------------------------------------
void MainFrame::OnGamePlay (wxCommandEvent& e)
{
#if defined(_WIN32) || defined(WIN32)

#ifdef _DEBUG
	WinExec("GamePlayDx9D.exe", SW_SHOW);
#else
	WinExec("GamePlayDx9.exe", SW_SHOW);
#endif

#endif
}
//----------------------------------------------------------------------------
bool MainFrame::Initlize ()
{
	mAuiManager = new wxAuiManager(this, wxAUI_MGR_DEFAULT
		|wxAUI_MGR_TRANSPARENT_DRAG);

	CreateMenu();
	CreateStatusBar();
	
	mRenderView = new RenderViewWindow(this);
	mAuiManager->AddPane(mRenderView,
		wxAuiPaneInfo().Name(wxT("RenderView")).Caption(PX2_LM.GetValue("Stage"))
		.DefaultPane().Centre().Dockable(true)
		.FloatingSize(800, 600).MinSize(200, 150)
		.CloseButton(true).MaximizeButton(true).MinimizeButton(true).PinButton(true));
	mRenderView->Initlize();
	EventWorld::GetSingleton().ComeIn(mRenderView);

	mPreView = new PreViewWindow(this);
	mAuiManager->AddPane(mPreView, wxAuiPaneInfo().Name(wxT("PreView"))
		.Caption(PX2_LM.GetValue("PreView")).DefaultPane().Right()
		.CloseButton(true).MaximizeButton(true).MinimizeButton(true).PinButton(true)
		.FloatingSize(220, 150).MinSize(200, 150));
	mPreView->Initlize();
	EventWorld::GetSingleton().ComeIn(mPreView);

	mResTreePanel = new ResTreePanel(this);
	mResTreePanel->GetResTree()->UpdateOnPath("Data/");
	mAuiManager->AddPane(mResTreePanel, wxAuiPaneInfo().Name(wxT("ResTree"))
		.Caption(PX2_LM.GetValue("Asserts")).DefaultPane().Right()
		.CloseButton(true).MaximizeButton(true).MinimizeButton(true).PinButton(true)
		.FloatingSize(220, 150).MinSize(200, 150));

	mInspector = new InspectorWindow(this);
	mAuiManager->AddPane(mInspector, wxAuiPaneInfo().Name(wxT("Inspector"))
		.Caption(PX2_LM.GetValue("Inspector")).DefaultPane().Right()
		.CloseButton(true).MaximizeButton(true).MinimizeButton(true).PinButton(true)
		.FloatingSize(220, 150).MinSize(200, 150));
	EventWorld::GetSingleton().ComeIn(mInspector);

	mObjectTree = new ObjectTree(this);
	mAuiManager->AddPane(mObjectTree, wxAuiPaneInfo().Name(wxT("Project"))
		.Caption(PX2_LM.GetValue("Project")).DefaultPane().Left()
		.CloseButton(true).MaximizeButton(true).MinimizeButton(true).PinButton(true)
		.FloatingSize(220, 150).MinSize(200, 150));
	EventWorld::GetSingleton().ComeIn(mObjectTree);

	mCurveEditWindow = new CurveEditWindow(this);
	mAuiManager->AddPane(mCurveEditWindow, wxAuiPaneInfo().Name(wxT("CurveEdit"))
		.Caption(PX2_LM.GetValue("CurveEdit")).DefaultPane().Bottom()
		.CloseButton(true).MaximizeButton(true).MinimizeButton(true).PinButton(true)
		.FloatingSize(220, 150).MinSize(200, 150));
	EventWorld::GetSingleton().ComeIn(mCurveEditWindow);

	wxFileConfig config("PX2EditorConfig");
	wxString Perspective;
	if (config.Read(wxString("Perspective"), &Perspective))
	{
		mAuiManager->LoadPerspective(Perspective);
	}

	mAuiManager->Update();

	mTimer.SetOwner(this, ID_FRAMETIMER);
	mTimer.Start(10);

	mInited = true;

	return true;
}
//----------------------------------------------------------------------------
void MainFrame::CreateMenu()
{
	mMainMenu = new wxMenuBar();
	wxMenu* menu = new wxMenu();
	mMainMenu->Append(menu, PX2_LM.GetValue("File"));
	menu->Append(ID_FILE_PROJECT_NEW, PX2_LM.GetValue("NewProject")+wxT("\tCtrl-N"));
	menu->Append(ID_FILE_PROJECT_OPEN, PX2_LM.GetValue("Open")+wxT("\tCtrl-O"));
	menu->Append(ID_FILE_PROJECT_SAVE, PX2_LM.GetValue("Save")+wxT("\tCtrl-S"));
	menu->Append(ID_FILE_PROJECT_SAVEAS, PX2_LM.GetValue("SaveAs"));
	menu->Append(ID_FILE_PROJECT_CLOSE, PX2_LM.GetValue("Close"));
	menu->AppendSeparator();
	menu->Append(ID_FILE_SCENE_NEW, PX2_LM.GetValue("NewScene"));
	menu->Append(ID_FILE_SCENE_OPEN, PX2_LM.GetValue("Open"));
	menu->Append(ID_FILE_SCENE_SAVE, PX2_LM.GetValue("Save"));
	menu->Append(ID_FILE_SCENE_SAVEAS, PX2_LM.GetValue("SaveAs"));
	menu->Append(ID_FILE_SCENE_CLOSE, PX2_LM.GetValue("Close"));
	menu->AppendSeparator();
	menu->Append(ID_FILE_EXPORTSELECTED, PX2_LM.GetValue("ExportSelected")+wxT("\tCtrl-O"));
	menu->AppendSeparator();
	menu->Append(ID_FILE_EXIT, PX2_LM.GetValue("Exist")+wxT("\tAlt-X"));

	menu = new wxMenu();
	mMainMenu->Append(menu, PX2_LM.GetValue("Edit"));
	menu->Append(ID_EDIT_UNDO, PX2_LM.GetValue("Undo")+wxT("\tCtrl-Z"));
	menu->Append(ID_EDIT_REDO, PX2_LM.GetValue("Redo")+wxT("\tCtrl-Y"));
	menu->AppendSeparator();
	menu->Append(ID_EDIT_DELETE, PX2_LM.GetValue("Delete")+wxT("\tDelete"));
	menu->AppendSeparator();
	menu->Append(ID_EDIT_SELECT, PX2_LM.GetValue("Select")+wxT("\tF1"));
	menu->Append(ID_EDIT_MOVE, PX2_LM.GetValue("Move")+wxT("\tF2"));
	menu->Append(ID_EDIT_ROLATE, PX2_LM.GetValue("Rolate")+wxT("\tF3"));
	menu->Append(ID_EDIT_SCALE, PX2_LM.GetValue("Scale")+wxT("\tF4"));
	menu->AppendSeparator();
	menu->Append(ID_EDIT_EDIT, PX2_LM.GetValue("Edit")+wxT("\tCtrl-E"));

	menu = new wxMenu();
	mMainMenu->Append(menu, PX2_LM.GetValue("View"));
	wxMenu *windowsMenu = new wxMenu();
	menu->AppendSubMenu(windowsMenu, PX2_LM.GetValue("Windows"));
	windowsMenu->Append(ID_VIEW_STAGE, PX2_LM.GetValue("Stage"));
	windowsMenu->Append(ID_VIEW_ACTORTREE, PX2_LM.GetValue("Scene"));
	windowsMenu->Append(ID_VIEW_PREVIEW, PX2_LM.GetValue("PreView"));
	windowsMenu->Append(ID_VIEW_RESTREE, PX2_LM.GetValue("Asserts"));
	windowsMenu->Append(ID_VIEW_INSPECTOR, PX2_LM.GetValue("Inspector"));
	windowsMenu->Append(ID_VIEW_CURVEEDIT, PX2_LM.GetValue("CurveEdit"));
	menu ->Append(ID_VIEW_CENTRE, 
		PX2_LM.GetValue("StageCentreDock")+wxT("\tCtrl-Enter"));

	menu = new wxMenu();
	mMainMenu->Append(menu, PX2_LM.GetValue("Create"));
	menu->Append(ID_CREATE_BOX, PX2_LM.GetValue("Box"));
	menu->Append(ID_CREATE_SPHERE, PX2_LM.GetValue("Sphere"));
	menu->Append(ID_CREATE_EFFECT, PX2_LM.GetValue("Effect"));

	wxMenu *ctrlMenu = new wxMenu();
	menu->AppendSubMenu(ctrlMenu, PX2_LM.GetValue("Control"));
	ctrlMenu->Append(ID_CREATE_CTRL_TRANSFORM, PX2_LM.GetValue("TransformCurveControl"));
	ctrlMenu->Append(ID_CREATE_CTRL_COLOR, PX2_LM.GetValue("ColorCurveControl"));
	ctrlMenu->Append(ID_CREATE_CTRL_ALPHA, PX2_LM.GetValue("AlphaCurveControl"));

	menu = new wxMenu();
	mMainMenu->Append(menu, PX2_LM.GetValue("Terrain"));
	menu->Append(ID_TERRAIN_NEW, PX2_LM.GetValue("TerrainNew"));
	menu->Append(ID_TERRAIN_COMPOSEMTL, PX2_LM.GetValue("TerrainComposeMtl"));
	menu->AppendSeparator();
	menu->Append(ID_TERRAIN_USELOD, PX2_LM.GetValue("TerrainUseLod"), "", true);
	bool useLod = EditSystem::GetSingleton().GetTerrainEdit()->IsUseLodTerrain();
	menu->Check(ID_TERRAIN_USELOD, useLod);
	menu->Append(ID_TERRAIN_USECOMPOSEDMTL, PX2_LM.GetValue("TerrainUseComposedMtl"), "", true);

	menu = new wxMenu();
	mMainMenu->Append(menu, PX2_LM.GetValue("Game"));
	menu->Append(ID_PLAYINEDITOR, PX2_LM.GetValue("PlayInEditor"));
	menu->Append(ID_PLAY, PX2_LM.GetValue("Play")+wxT("\tCtrl-G"));
	menu->Append(ID_PLAYCONFIG, PX2_LM.GetValue("PlayConfig"));

	menu = new wxMenu();
	mMainMenu->Append(menu, PX2_LM.GetValue("Help"));

	SetMenuBar(mMainMenu);

	EnableEditAll(false);
}
//----------------------------------------------------------------------------
void MainFrame::CreateMainToolbar ()
{
	mMainToolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, 
		wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
	mMainToolbar->SetToolBitmapSize(wxSize(16, 16));

	mMainToolbar->AddTool(ID_FILE_SCENE_NEW, _("New"), 
		wxBitmap( wxT("./ToolRes/Icons/page_world.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddTool(ID_FILE_SCENE_OPEN, _("Open"), 
		wxBitmap( wxT("./ToolRes/Icons/folder_page.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddSeparator();

	mMainToolbar->AddTool(ID_EDIT_COPY, _("Copy"), 
		wxBitmap( wxT("./ToolRes/Icons/page_copy.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddTool(ID_EDIT_CUT, _("Cut"), 
		wxBitmap( wxT("./ToolRes/Icons/cut.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddTool(ID_EDIT_PASTE, _("Paste"), 
		wxBitmap( wxT("./ToolRes/Icons/page_paste.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddSeparator();

	mMainToolbar->AddTool(ID_EDIT_UNDO, _("Undo"), 
		wxBitmap( wxT("./ToolRes/Icons/arrow_turn_left.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );
	mMainToolbar->EnableTool(ID_EDIT_UNDO, false);

	mMainToolbar->AddTool(ID_EDIT_REDO, _("Redo"), 
		wxBitmap( wxT("./ToolRes/Icons/arrow_turn_right.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );
	mMainToolbar->EnableTool(ID_EDIT_REDO, false);

	mMainToolbar->Realize();

	mAuiManager->AddPane(mMainToolbar, wxAuiPaneInfo().
		Name(wxT("tb1")).Caption(wxT("Main Toolbar")).
		ToolbarPane().Top().LeftDockable(false).RightDockable(false));
}
//----------------------------------------------------------------------------
void MainFrame::EnableEditAll (bool enable)
{
	wxMenuBar *menuBar = GetMenuBar();
	if (!menuBar)
		return;

	menuBar->Enable(ID_FILE_PROJECT_SAVE, enable);
	menuBar->Enable(ID_FILE_PROJECT_SAVEAS, enable);
	menuBar->Enable(ID_FILE_PROJECT_CLOSE, enable);
	menuBar->Enable(ID_FILE_SCENE_NEW, enable);
	menuBar->Enable(ID_FILE_SCENE_OPEN, enable);
	menuBar->Enable(ID_FILE_SCENE_SAVE, enable);
	menuBar->Enable(ID_FILE_SCENE_SAVEAS, enable);
	menuBar->Enable(ID_FILE_SCENE_CLOSE, enable);
	menuBar->Enable(ID_FILE_EXPORTSELECTED, enable);
}
//----------------------------------------------------------------------------