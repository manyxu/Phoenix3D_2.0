/*
*
* ÎÄ¼þÃû³Æ	£º	PX2SceneSettingWindow.cpp
*
*/

#include "PX2SceneSettingWindow.hpp"
#include "PX2SceneSettingPropertyGrid.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(SceneSettingWindow, wxWindow)
	EVT_SIZE(SceneSettingWindow::OnSize)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
SceneSettingWindow::SceneSettingWindow (wxWindow *parent)
:
wxWindow(parent, wxID_ANY)
{
	mSettingPropertyGrid = new SceneSettingPropertyGrid(this);
}
//----------------------------------------------------------------------------
SceneSettingWindow::~SceneSettingWindow ()
{

}
//----------------------------------------------------------------------------
void SceneSettingWindow::OnSize(wxSizeEvent& e)
{
	if (mSettingPropertyGrid)
		mSettingPropertyGrid->SetSize(e.GetSize());
}
//----------------------------------------------------------------------------
void SceneSettingWindow::DoEnter ()
{

}
//----------------------------------------------------------------------------
void SceneSettingWindow::DoUpdate ()
{

}
//----------------------------------------------------------------------------
void SceneSettingWindow::DoExecute (PX2::Event *event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
void SceneSettingWindow::DoLeave ()
{

}
//----------------------------------------------------------------------------