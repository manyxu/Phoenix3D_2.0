/*
*
* ÎÄ¼þÃû³Æ	£º	PX2LightInspector.cpp
*
*/

#include "PX2LightInspector.hpp"
using namespace PX2Editor;

BEGIN_EVENT_TABLE(LightInspector, wxWindow)
	EVT_SIZE(LightInspector::OnSize)
END_EVENT_TABLE()

LightInspector::LightInspector (wxWindow *parent)
:
wxWindow(parent, wxID_ANY),
mFoldPaneBar(0),
mPropGrid(0)
{
	mFoldPaneBar = new wxFoldPanelBar(this, wxID_ANY, 
		wxDefaultPosition, wxDefaultSize, wxFPB_DEFAULT_STYLE|wxFPB_VERTICAL,
		0);

	wxFoldPanel item = mFoldPaneBar->AddFoldPanel(_T("Property"), true);
	mPropGrid = new LightActorPropertyGrid(item.GetParent());
	mFoldPaneBar->AddFoldPanelWindow(item, mPropGrid);
	PX2::EventWorld::GetSingleton().ComeIn(mPropGrid);
}
//-----------------------------------------------------------------------------
LightInspector::~LightInspector ()
{

}
//-----------------------------------------------------------------------------
void LightInspector::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void LightInspector::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void LightInspector::DoExecute (PX2::Event *event)
{
	PX2_UNUSED(event);
}
//-----------------------------------------------------------------------------
void LightInspector::DoLeave ()
{

}
//-----------------------------------------------------------------------------
LightInspector::LightInspector ()
{

}
//-----------------------------------------------------------------------------
void LightInspector::OnSize (wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	if (mFoldPaneBar)
		mFoldPaneBar->SetSize(size);

	if (mPropGrid)
		mPropGrid->SetSize(size);
}
//-----------------------------------------------------------------------------