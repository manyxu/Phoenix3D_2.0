/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectInspector.cpp
*
*/

#include "PX2EffectInspector.hpp"
#include "PX2EffectEventsPane.hpp"
#include "PX2EffectPane.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(EffectInspector, wxScrolledWindow)
	EVT_SIZE(EffectInspector::OnSize)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
EffectInspector::EffectInspector (wxWindow *parent)
:
wxScrolledWindow(parent),
mFoldPaneBar(0),
mEffectEventsPanel(0)
{
	SetScrollbars(0, 10, 0, 200 );

	mFoldPaneBar = new wxFoldPanelBar(this, wxID_ANY, 
		wxDefaultPosition, wxDefaultSize, wxFPB_DEFAULT_STYLE|wxFPB_VERTICAL,
		0);

	wxFoldPanel item = mFoldPaneBar->AddFoldPanel(_T("Effect"), false);
	mEffectPanel = new EffectPanel(item.GetParent());
	mFoldPaneBar->AddFoldPanelWindow(item, mEffectPanel);

	item = mFoldPaneBar->AddFoldPanel(_T("EffectEvents"), false);
	mEffectEventsPanel = new EffectEventsPanel(item.GetParent());
	mFoldPaneBar->AddFoldPanelWindow(item, mEffectEventsPanel);
}
//-----------------------------------------------------------------------------
EffectInspector::~EffectInspector ()
{

}
//-----------------------------------------------------------------------------
EffectInspector::EffectInspector ()
{

}
//-----------------------------------------------------------------------------
void EffectInspector::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void EffectInspector::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void EffectInspector::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::SelectEffect) ||
		EditorEventSpace::IsEqual(event, EditorEventSpace::UpdateEffect))
	{
		PX2::Movable *obj = event->GetData<PX2::Movable*>();
		if (obj && mEffectEventsPanel)
			mEffectEventsPanel->UpdateEventsOnEffect(obj);
	}
}
//-----------------------------------------------------------------------------
void EffectInspector::DoLeave ()
{

}
//-----------------------------------------------------------------------------
void EffectInspector::OnSize (wxSizeEvent& e)
{
	wxScrolledWindow::OnSize(e);

	wxSize size = GetClientSize();

	if (mFoldPaneBar)
		mFoldPaneBar->SetSize(size);
}
//-----------------------------------------------------------------------------