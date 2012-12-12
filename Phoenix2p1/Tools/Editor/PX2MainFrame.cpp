/*
*
* ÎÄ¼þÃû³Æ	£º	PX2MainFrame.cpp
*
*/

#include "PX2MainFrame.hpp"
#include "PX2RenderViewWindow.hpp"
#include "PX2PreViewWindow.hpp"
#include "PX2ResTree.hpp"
#include "PX2InspectorWindow.hpp"
#include "PX2ViewCtrlInstMan.hpp"
#include "PX2DlgTerainNew.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_FILE_NEW wxID_HIGHEST + 1001
#define ID_FILE_OPEN wxID_HIGHEST + 1002
#define ID_FILE_CLOSE wxID_HIGHEST + 1003
#define ID_FILE_SAVE wxID_HIGHEST + 1004
#define ID_FILE_SAVEAS wxID_HIGHEST + 1005
#define ID_FILE_EXIT wxID_HIGHEST + 1006

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

#define ID_VIEW0_SCENE wxID_HIGHEST + 1201

#define ID_TERRAIN_NEW wxID_HIGHEST + 1301

#define ID_PLAYINEDITOR wxID_HIGHEST + 1401
#define ID_PLAY wxID_HIGHEST + 1402
#define ID_PLAYCONFIG wxID_HIGHEST + 1403

#define ID_FRAMETIMER wxID_HIGHEST+1999
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_TIMER(ID_FRAMETIMER, MainFrame::OnTimer)
	EVT_MENU(ID_FILE_NEW, MainFrame::OnNew)
	EVT_MENU(ID_FILE_OPEN, MainFrame::OnOpen)
	EVT_MENU(ID_FILE_SAVE, MainFrame::OnSave)
	EVT_MENU(ID_FILE_SAVEAS, MainFrame::OnSaveAs)
	EVT_MENU(ID_FILE_EXIT, MainFrame::OnExist)
	EVT_MENU(ID_EDIT_UNDO, MainFrame::OnUnDo)
	EVT_MENU(ID_EDIT_REDO, MainFrame::OnReDo)
	EVT_MENU(ID_EDIT_SELECT, MainFrame::OnEditSelect)
	EVT_MENU(ID_EDIT_MOVE, MainFrame::OnEditTranslate)
	EVT_MENU(ID_EDIT_ROLATE, MainFrame::OnEditRolate)
	EVT_MENU(ID_EDIT_SCALE, MainFrame::OnEditScale)
	EVT_MENU(ID_EDIT_EDIT, MainFrame::OnEditEdit)
	EVT_MENU(ID_TERRAIN_NEW, MainFrame::OnTerrainNew)
	EVT_MENU(ID_PLAY, MainFrame::OnGamePlay)
END_EVENT_TABLE();
//----------------------------------------------------------------------------
MainFrame::MainFrame (const wxString title, int xPos, int yPos,
	int width, int height)
	:
wxFrame((wxFrame*)0, -1, title, wxPoint(xPos, yPos), wxSize(width, height)),
	mAuiManager(0),
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
void MainFrame::OnNew (wxCommandEvent &e)
{
	EditMap *map = EditSystem::GetSingleton().GetEditMap();
	map->NewScene();

	mRenderView->SetScene(map->GetScene()->GetSceneNode());

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->SetInteractionMode(IM_GENERAL);
}
//----------------------------------------------------------------------------
void MainFrame::OnOpen (wxCommandEvent &e)
{
	wxFileDialog dlg(mRenderView,
		wxT("Open Map"),
		wxEmptyString,
		wxEmptyString,
		wxT("map (*.pxof)|*.pxof"));

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		EditSystem::GetSingleton().GetEditMap()->LoadScene(dlg.GetPath());
	}

	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->SetInteractionMode(IM_GENERAL);
}
//----------------------------------------------------------------------------
void MainFrame::OnSave (wxCommandEvent &e)
{
	std::string path = EditSystem::GetSingleton().GetEditMap()->GetLoadedScenePath();

	if (path != "")
	{
		EditSystem::GetSingleton().GetEditMap()->SaveScene(path.c_str());
	}
	else
	{
		wxFileDialog dlg(mRenderView,
			wxT("Save Map"),
			wxEmptyString,
			wxEmptyString,
			wxT("map (*.pxof)|*.pxof"),
			wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

		dlg.CenterOnParent();

		if (dlg.ShowModal() == wxID_OK)
		{
			EditSystem::GetSingleton().GetEditMap()->SaveScene(dlg.GetPath());
		}
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnSaveAs (wxCommandEvent &e)
{
	wxFileDialog dlg(mRenderView,
		wxT("Save Map"),
		wxEmptyString,
		wxEmptyString,
		wxT("map (*.pxof)|*.pxof"),
		wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

	dlg.CenterOnParent();

	if (dlg.ShowModal() == wxID_OK)
	{
		EditSystem::GetSingleton().GetEditMap()->SaveSceneAs(dlg.GetPath());
	}
}
//----------------------------------------------------------------------------
void MainFrame::OnExist (wxCommandEvent &e)
{
	//if (wxID_OK == wxMessageBox(PX2_LM.GetValue("Tip1"),
	//	PX2_LM.GetValue("Tip0"), wxYES_NO))
	//{
	//}
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
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_SELECT);
}
//----------------------------------------------------------------------------
void MainFrame::OnEditTranslate (wxCommandEvent& e)
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_TRANSLATE);
}
//----------------------------------------------------------------------------
void MainFrame::OnEditRolate (wxCommandEvent& e)
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_ROLATE);
}
//----------------------------------------------------------------------------
void MainFrame::OnEditScale (wxCommandEvent& e)
{
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
void MainFrame::OnTerrainNew (wxCommandEvent &e)
{
	DlgTerrainNew dlg(mRenderView);
	if( dlg.ShowModal() == wxID_OK )
	{
		EditSystem::GetSingleton().GetEditMap()->CreateTerrain(
			dlg.mValue_TerrainName, dlg.mValue_TerrainWidth,
			dlg.mValue_PageWidth+1, dlg.mValue_GridSpace);
	}
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
	mAuiManager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);

	CreateMenu();
	CreateStatusBar();
	
	mRenderView = new RenderViewWindow(this);
	mAuiManager->AddPane(mRenderView, wxAuiPaneInfo().Name(wxT("RenderView"))
		.Caption(wxT("")).DefaultPane().Center()
		.CloseButton(false).Floatable(false));
	mRenderView->Initlize();
	EventWorld::GetSingleton().ComeIn(mRenderView);

	mPreView = new PreViewWindow(this);
	mAuiManager->AddPane(mPreView, wxAuiPaneInfo().Name(wxT("PreView"))
		.Caption(PX2_LM.GetValue("PreView")).DefaultPane().Right()
		.CloseButton(false).FloatingSize(220, 150).MinSize(200, 150));
	mPreView->Initlize();
	EventWorld::GetSingleton().ComeIn(mPreView);

	ResTree *resTree = new ResTree(this);
	resTree->UpdateOnPath("Data/");
	mAuiManager->AddPane(resTree, wxAuiPaneInfo().Name(wxT("ResTree"))
		.Caption(PX2_LM.GetValue("Asserts")).DefaultPane().Right()
		.CloseButton(false).FloatingSize(220, 150).MinSize(220, 100));

	InspectorWindow *insp = new InspectorWindow(this);
	mAuiManager->AddPane(insp, wxAuiPaneInfo().Name(wxT("Inspector"))
		.Caption(PX2_LM.GetValue("Inspector")).DefaultPane().Right()
		.CloseButton(false).FloatingSize(220, 150).MinSize(220, 100));
	EventWorld::GetSingleton().ComeIn(insp);

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
	wxMenuBar* menubar = new wxMenuBar();
	wxMenu* menu = new wxMenu();
	menubar->Append(menu, PX2_LM.GetValue("File"));
	menu->Append(ID_FILE_NEW, PX2_LM.GetValue("New")+wxT("\tCtrl-N"));
	menu->Append(ID_FILE_OPEN, PX2_LM.GetValue("Open")+wxT("\tCtrl-O"));
	menu->Append(ID_FILE_CLOSE, PX2_LM.GetValue("Close"));
	menu->AppendSeparator();
	menu->Append(ID_FILE_SAVE, PX2_LM.GetValue("Save")+wxT("\tCtrl-S"));
	menu->Append(ID_FILE_SAVEAS, PX2_LM.GetValue("SaveAs")+wxT("\tCtrl-A"));
	menu->AppendSeparator();
	menu->Append(ID_FILE_EXIT, PX2_LM.GetValue("Exist")+wxT("\tAlt-X"));

	menu = new wxMenu();
	menubar->Append(menu, PX2_LM.GetValue("Edit"));
	menu->Append(ID_EDIT_UNDO, PX2_LM.GetValue("Undo")+wxT("\tCtrl-Z"));
	menu->Append(ID_EDIT_REDO, PX2_LM.GetValue("Redo")+wxT("\tCtrl-Y"));
	menu->AppendSeparator();
	menu->Append(ID_EDIT_SELECT, PX2_LM.GetValue("Select")+wxT("\t1"));
	menu->Append(ID_EDIT_MOVE, PX2_LM.GetValue("Move")+wxT("\t2"));
	menu->Append(ID_EDIT_ROLATE, PX2_LM.GetValue("Rolate")+wxT("\t3"));
	menu->Append(ID_EDIT_SCALE, PX2_LM.GetValue("Scale")+wxT("\t4"));
	menu->AppendSeparator();
	menu->Append(ID_EDIT_EDIT, PX2_LM.GetValue("Edit")+wxT("\tCtrl-E"));

	menu = new wxMenu();
	menubar->Append(menu, PX2_LM.GetValue("View"));
	menu ->Append(ID_VIEW0_SCENE, PX2_LM.GetValue("Scene"));

	menu = new wxMenu();
	menubar->Append(menu, PX2_LM.GetValue("Terrain"));
	menu->Append(ID_TERRAIN_NEW, PX2_LM.GetValue("TerrainNew"));

	menu = new wxMenu();
	menubar->Append(menu, PX2_LM.GetValue("Game"));
	menu->Append(ID_PLAYINEDITOR, PX2_LM.GetValue("PlayInEditor"));
	menu->Append(ID_PLAY, PX2_LM.GetValue("Play")+wxT("\tCtrl-G"));
	menu->Append(ID_PLAYCONFIG, PX2_LM.GetValue("PlayConfig"));

	menu = new wxMenu();
	menubar->Append(menu, PX2_LM.GetValue("Help"));

	SetMenuBar(menubar);
}
//----------------------------------------------------------------------------
void MainFrame::CreateMainToolbar ()
{
	mMainToolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, 
		wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
	mMainToolbar->SetToolBitmapSize(wxSize(16, 16));

	mMainToolbar->AddTool(ID_FILE_NEW, _("New"), 
		wxBitmap( wxT("./ToolRes/Icons/page_world.png"), wxBITMAP_TYPE_PNG), 
		wxNullBitmap, wxITEM_NORMAL, 
		wxEmptyString, wxEmptyString );

	mMainToolbar->AddTool(ID_FILE_OPEN, _("Open"), 
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