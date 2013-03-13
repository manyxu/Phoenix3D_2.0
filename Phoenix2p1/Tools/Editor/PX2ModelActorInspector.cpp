/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ModelInspector.cpp
*
*/

#include "PX2ModelActorInspector.hpp"
#include "PX2ModelActorPropertyGrid.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(ModelActorInspector, wxScrolledWindow)
EVT_SIZE(ModelActorInspector::OnSize)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ModelActorInspector::ModelActorInspector (wxWindow *parent)
	:
wxScrolledWindow(parent),
	mFoldPaneBar(0),
	mModelActorPropGrid(0),
	mInitSized(false)
{
	mFoldPaneBar = new wxFoldPanelBar(this, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxFPB_DEFAULT_STYLE|wxFPB_VERTICAL, 0);
}
//-----------------------------------------------------------------------------
ModelActorInspector::~ModelActorInspector ()
{
}
//-----------------------------------------------------------------------------
ModelActorInspector::ModelActorInspector ()
{

}
//-----------------------------------------------------------------------------
void ModelActorInspector::SetActor (PX2::Actor *actor)
{
	mActor = actor;
	if (mModelActorPropGrid)
		mModelActorPropGrid->SetObject(mActor);
}
//-----------------------------------------------------------------------------
void ModelActorInspector::OnSize(wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	if (mFoldPaneBar)
		mFoldPaneBar->SetSize(size);

	if (!mInitSized)
	{
		wxFoldPanel item = mFoldPaneBar->AddFoldPanel(
			PX2_LM.GetValue("General"), true);
		mModelActorPropGrid = new ModelActorPropertyGrid(item.GetParent());
		mModelActorPropGrid->SetSize(size.GetWidth(), size.GetHeight()/2);
		mFoldPaneBar->AddFoldPanelWindow(item, mModelActorPropGrid);
		mFoldPaneBar->Expand(item);

		if (mModelActorPropGrid)
			mModelActorPropGrid->SetObject(mActor);

		mInitSized = true;
	}
}
//-----------------------------------------------------------------------------