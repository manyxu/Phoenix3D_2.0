/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerInspector.cpp
*
*/

#include "PX2ControllerInspector.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(ControllerInspector, wxScrolledWindow)
EVT_SIZE(ControllerInspector::OnSize)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ControllerInspector::ControllerInspector (wxWindow *parent)
:
wxScrolledWindow(parent),
mFoldPaneBar(0),
mPropertyGrid(0),
mKeyPointsPanel(0),
mInitSized(false)
{
	mFoldPaneBar = new wxFoldPanelBar(this, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxFPB_DEFAULT_STYLE|wxFPB_VERTICAL, 0);
}
//-----------------------------------------------------------------------------
ControllerInspector::~ControllerInspector ()
{
}
//-----------------------------------------------------------------------------
void ControllerInspector::SetController (PX2::Controller *ctrl)
{
	mController = ctrl;
	if (mPropertyGrid)
		mPropertyGrid->SetObject(ctrl);
}
//-----------------------------------------------------------------------------
void ControllerInspector::OnSize(wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	if (!mInitSized)
	{
		wxFoldPanel	item = mFoldPaneBar->AddFoldPanel(
			PX2_LM.GetValue("Property"), true);
		mPropertyGrid = new ControllerPropertyGrid(item.GetParent());
		mPropertyGrid->SetSize(size.GetWidth(), size.GetHeight()/4);
		mFoldPaneBar->AddFoldPanelWindow(item, mPropertyGrid);
		mFoldPaneBar->Expand(item);
		mPropertyGrid->SetObject(mController);

		wxFoldPanel	itemKeyPoints = mFoldPaneBar->AddFoldPanel(
			PX2_LM.GetValue("KeyPoints"), true);
		mKeyPointsPanel = new ControllerKeyPointsPanel(itemKeyPoints.GetParent());
		mFoldPaneBar->AddFoldPanelWindow(itemKeyPoints, mKeyPointsPanel);
		mFoldPaneBar->Expand(itemKeyPoints);

		wxFoldPanel	itemKeyPointsValue = mFoldPaneBar->AddFoldPanel(
			PX2_LM.GetValue("KeyPointsValue"), true);

		mInitSized = true;
	}

	if (mFoldPaneBar)
	{
		mFoldPaneBar->SetSize(size.GetWidth(), size.GetHeight());
		mFoldPaneBar->Layout();
	}
}
//-----------------------------------------------------------------------------
ControllerInspector::ControllerInspector ()
{

}
//-----------------------------------------------------------------------------