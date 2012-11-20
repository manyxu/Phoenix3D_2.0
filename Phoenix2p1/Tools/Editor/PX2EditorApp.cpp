/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EditorApp.cpp
*
*/

#include "PX2EditorApp.hpp"
#include "PX2MainFrame.hpp"
#include "PX2ViewCtrlInstMan.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
EditorApp::EditorApp ()
{
}
//-----------------------------------------------------------------------------
EditorApp::~EditorApp ()
{
}
//-----------------------------------------------------------------------------
bool EditorApp::OnInit ()
{
	EditSystem *editSystem = new EditSystem();
	if (editSystem)
	{
		editSystem->Initlize();
	}

	PX2_LM.Load("ToolRes/UILanguage/UILanguageANSI.csv");
	PX2_LM.SetLanguage(0);

	ViewCtrlInstMan *ctrlMan = new0 ViewCtrlInstMan();

	wxImage::AddHandler(new wxPNGHandler());
	wxImage::AddHandler(new wxGIFHandler());

	wxFileSystem::AddHandler(new wxArchiveFSHandler()); 
	wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->Load(wxT("ToolRes/wxFBP/*.xrc"));

	int displayWidth, displayHeight;
	wxDisplaySize(&displayWidth, &displayHeight);
	mMainFrame = new MainFrame(wxT("PX2EditorDx9"), 0, 0, wxMin(1024,
		displayWidth), wxMin(748, displayHeight));
	mMainFrame->Show(true);
	SetTopWindow(mMainFrame);

	return true;
}
//-----------------------------------------------------------------------------
void EditorApp::AddHandlers()
{
	// supported images
	wxImage::AddHandler(new wxPNGHandler());
	wxImage::AddHandler(new wxGIFHandler());

	// resource system
	wxFileSystem::AddHandler(new wxArchiveFSHandler()); 
	wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->Load(wxT("ToolRes/wxFBP/*.xrc"));
}
//-----------------------------------------------------------------------------
int EditorApp::OnExit()
{
	ViewCtrlInstMan *ctrlMan = ViewCtrlInstMan::GetSingletonPtr();
	if (ctrlMan)
	{
		delete0(ctrlMan);
		ViewCtrlInstMan::Set(0);
	}

	EditSystem *editSystem = EditSystem::GetSingletonPtr();
	if (editSystem)
	{
		editSystem->Terminate();

		delete editSystem;

		EditSystem::Set(0);
	}

	return 0;
}
//-----------------------------------------------------------------------------
IMPLEMENT_APP(PX2Editor::EditorApp)