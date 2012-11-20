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
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
END_EVENT_TABLE();
//----------------------------------------------------------------------------
MainFrame::MainFrame (const wxString title, int xPos, int yPos,
	int width, int height)
	:
wxFrame((wxFrame*)0, -1, title, wxPoint(xPos, yPos), wxSize(width, height)),
	mAuiManager(0)
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

	mPreView = new PreViewWindow(this);
	mAuiManager->AddPane(mPreView, wxAuiPaneInfo().Name(wxT("PreView"))
		.Caption(PX2_LM.GetValue("PreView")).DefaultPane().Right()
		.CloseButton(false).FloatingSize(220, 150).MinSize(200, 150));
	mPreView->Show();

	ResTree *resTree = new ResTree(this);
	resTree->UpdateOnPath("Data/");
	mAuiManager->AddPane(resTree, wxAuiPaneInfo().Name(wxT("ResTree"))
		.Caption(PX2_LM.GetValue("Asserts")).DefaultPane().Right()
		.CloseButton(false).FloatingSize(220, 150).MinSize(220, 100));
	resTree->Show();

	InspectorWindow *insp = new InspectorWindow(this);
	mAuiManager->AddPane(insp, wxAuiPaneInfo().Name(wxT("Inspector"))
		.Caption(PX2_LM.GetValue("Inspector")).DefaultPane().Right()
		.CloseButton(false).FloatingSize(220, 150).MinSize(220, 100));
	insp->Show();

	wxFileConfig config("PX2EditorConfig");
	wxString Perspective;
	if (config.Read(wxString("Perspective"), &Perspective))
	{
		mAuiManager->LoadPerspective(Perspective);
	}

	mAuiManager->Update();

	return true;
}
//----------------------------------------------------------------------------
void MainFrame::CreateMenu()
{
	wxMenuBar* menubar = new wxMenuBar();
	wxMenu* mnu = new wxMenu();
	menubar->Append(mnu, PX2_LM.GetValue("File"));
	mnu->Append(ID_NEW, PX2_LM.GetValue("New"));
	mnu->Append(ID_OPEN, PX2_LM.GetValue("Open"));
	mnu->Append(ID_CLOSE, PX2_LM.GetValue("Close"));
	mnu->AppendSeparator();
	mnu->Append(ID_SAVE, PX2_LM.GetValue("Save"));
	mnu->Append(ID_SAVEAS, PX2_LM.GetValue("SaveAs"));
	mnu->AppendSeparator();
	mnu->Append(ID_EXIT, PX2_LM.GetValue("Exist"));

	mnu = new wxMenu();
	menubar->Append(mnu, PX2_LM.GetValue("Edit"));
	mnu->Append(ID_UNDO, PX2_LM.GetValue("Undo"));
	mnu->Append(ID_REDO, PX2_LM.GetValue("Redo"));
	mnu->AppendSeparator();
	mnu->Append(ID_SELECT, PX2_LM.GetValue("Select"));
	mnu->Append(ID_MOVE, PX2_LM.GetValue("Move"));
	mnu->Append(ID_ROLATE, PX2_LM.GetValue("Rolate"));
	mnu->Append(ID_SCALE, PX2_LM.GetValue("Scale"));

	mnu = new wxMenu();
	menubar->Append(mnu, PX2_LM.GetValue("Game"));
	mnu->Append(ID_PLAYINEDITOR, PX2_LM.GetValue("PlayInEditor"));
	mnu->Append(ID_PLAY, PX2_LM.GetValue("Play"));
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