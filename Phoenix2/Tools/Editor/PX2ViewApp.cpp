/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ViewApp.cpp
*
*/

#include "PX2ViewApp.hpp"
#include "PX2ViewTopFrame.hpp"
#include "PX2ControllerManager.hpp"
#include "PX2SystemManager.hpp"
using namespace PX2Editor;
using namespace PX2;

ViewApp::ViewApp ()
:
mControllerManager(0)
{
	SystemManager::Initialize();
}
//-----------------------------------------------------------------------------
ViewApp::~ViewApp ()
{
	if (mControllerManager)
		delete mControllerManager;

	mEditorOptions->Save("PX2EditorOptions.px2eo");
	if (mEditorOptions)
		delete mEditorOptions;

	SystemManager::Terminate();
}
//-----------------------------------------------------------------------------
bool ViewApp::OnInit ()
{
	// options
	mEditorOptions = new EditorOptions();
	mEditorOptions->Load("PX2EditorOptions.px2eo");

	// ControlManager
	mControllerManager = new ControllerManager();

	// handles
	AddHandlers();

	// MainFrame
	int displayWidth, displayHeight;
	wxDisplaySize(&displayWidth, &displayHeight);
	mMainFrame = new ViewTopFrame(wxT("Phoenix2 Editor"), 0, 0, min(1024, 
		displayWidth), min(748, displayHeight));
	mMainFrame->Initialize();
	mMainFrame->Show(true);
	SetTopWindow(mMainFrame);

	// PX2 Event Handlers
	EditSystem::GetSingleton().GetEventWorld()->ComeIn(mMainFrame);

	return true;
}
//-----------------------------------------------------------------------------
void ViewApp::AddHandlers()
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
IMPLEMENT_APP(PX2Editor::ViewApp)