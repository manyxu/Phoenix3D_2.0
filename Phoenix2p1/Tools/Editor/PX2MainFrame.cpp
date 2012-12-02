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
using namespace PX2Editor;
using namespace PX2;

#define ID_NEW wxID_HIGHEST + 1001
#define ID_OPEN wxID_HIGHEST + 1002
#define ID_CLOSE wxID_HIGHEST + 1003
#define ID_SAVE wxID_HIGHEST + 1004
#define ID_SAVEAS wxID_HIGHEST + 1005
#define ID_EXIT wxID_HIGHEST + 1006

#define ID_UNDO wxID_HIGHEST + 1101
#define ID_REDO wxID_HIGHEST + 1102
#define ID_COPY wxID_HIGHEST + 1103
#define ID_CUT wxID_HIGHEST + 1104
#define ID_PASTE wxID_HIGHEST + 1105
#define ID_DELETE wxID_HIGHEST + 1106
#define ID_SELECT wxID_HIGHEST + 1107
#define ID_MOVE wxID_HIGHEST + 1108
#define ID_ROLATE wxID_HIGHEST + 1109
#define ID_SCALE wxID_HIGHEST + 1110

#define ID_PLAYINEDITOR wxID_HIGHEST + 1201
#define ID_PLAY wxID_HIGHEST + 1202
#define ID_PLAYCONFIG wxID_HIGHEST + 1203

#define ID_FRAMETIMER wxID_HIGHEST+1999
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_TIMER(ID_FRAMETIMER, MainFrame::OnTimer)
	EVT_MENU(ID_NEW, MainFrame::OnNew)
	EVT_MENU(ID_OPEN, MainFrame::OnOpen)
	EVT_MENU(ID_SAVE, MainFrame::OnSave)
	EVT_MENU(ID_SAVEAS, MainFrame::OnSaveAs)
	EVT_MENU(ID_EXIT, MainFrame::OnExist)
	EVT_MENU(ID_SELECT, MainFrame::OnEditSelect)
	EVT_MENU(ID_MOVE, MainFrame::OnEditTranslate)
	EVT_MENU(ID_ROLATE, MainFrame::OnEditRolate)
	EVT_MENU(ID_SCALE, MainFrame::OnEditScale)
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
		->SetInteractionMode(IM_SELECT);
}
//----------------------------------------------------------------------------
void MainFrame::OnOpen (wxCommandEvent &e)
{
	wxFileDialog dlg(this,
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
		->SetInteractionMode(IM_SELECT);
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
		wxFileDialog dlg(this,
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
	wxFileDialog dlg(this,
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

}
//----------------------------------------------------------------------------
void MainFrame::OnEditSelect (wxCommandEvent& e)
{
	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->SetInteractionMode(IM_SELECT);
}
//----------------------------------------------------------------------------
void MainFrame::OnEditTranslate (wxCommandEvent& e)
{
	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->SetInteractionMode(IM_TRANSLATE);
}
//----------------------------------------------------------------------------
void MainFrame::OnEditRolate (wxCommandEvent& e)
{
	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->SetInteractionMode(IM_ROLATE);
}
//----------------------------------------------------------------------------
void MainFrame::OnEditScale (wxCommandEvent& e)
{
	ViewCtrlInstMan::GetSingleton().GetCurViewCtrlInst()
		->SetInteractionMode(IM_SCALE);
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
	wxMenu* mnu = new wxMenu();
	menubar->Append(mnu, PX2_LM.GetValue("File"));
	mnu->Append(ID_NEW, PX2_LM.GetValue("New")+wxT("\tCtrl-N"));
	mnu->Append(ID_OPEN, PX2_LM.GetValue("Open")+wxT("\tCtrl-O"));
	mnu->Append(ID_CLOSE, PX2_LM.GetValue("Close"));
	mnu->AppendSeparator();
	mnu->Append(ID_SAVE, PX2_LM.GetValue("Save")+wxT("\tCtrl-S"));
	mnu->Append(ID_SAVEAS, PX2_LM.GetValue("SaveAs")+wxT("\tCtrl-A"));
	mnu->AppendSeparator();
	mnu->Append(ID_EXIT, PX2_LM.GetValue("Exist")+wxT("\tAlt-X"));

	mnu = new wxMenu();
	menubar->Append(mnu, PX2_LM.GetValue("Edit"));
	mnu->Append(ID_UNDO, PX2_LM.GetValue("Undo")+wxT("\tCtrl-Z"));
	mnu->Append(ID_REDO, PX2_LM.GetValue("Redo")+wxT("\tCtrl-Y"));
	mnu->AppendSeparator();
	mnu->Append(ID_SELECT, PX2_LM.GetValue("Select")+wxT("\t1"));
	mnu->Append(ID_MOVE, PX2_LM.GetValue("Move")+wxT("\t2"));
	mnu->Append(ID_ROLATE, PX2_LM.GetValue("Rolate")+wxT("\t3"));
	mnu->Append(ID_SCALE, PX2_LM.GetValue("Scale")+wxT("\t4"));

	mnu = new wxMenu();
	menubar->Append(mnu, PX2_LM.GetValue("Game"));
	mnu->Append(ID_PLAYINEDITOR, PX2_LM.GetValue("PlayInEditor"));
	mnu->Append(ID_PLAY, PX2_LM.GetValue("Play")+wxT("\tCtrl-R"));
	mnu->Append(ID_PLAYCONFIG, PX2_LM.GetValue("PlayConfig"));

	mnu = new wxMenu();
	menubar->Append(mnu, PX2_LM.GetValue("Help"));

	SetMenuBar(menubar);
}
//----------------------------------------------------------------------------
void MainFrame::CreateMainToolbar ()
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