/*
*
* ÎÄ¼þÃû³Æ	£º	PX2EffectActorInspector.cpp
*
*/

#include "PX2EffectActorInspector.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2EditSystem.hpp"
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
	mEffectPropGrid(0),
	mEffectNodePanel(0),
	mInitSized(false)
{
	mFoldPaneBar = new wxFoldPanelBar(this, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxFPB_DEFAULT_STYLE|wxFPB_VERTICAL, 0);
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
void EffectInspector::OnSize (wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	if (!mInitSized)
	{
		wxFoldPanel item = mFoldPaneBar->AddFoldPanel(
			PX2_LM.GetValue("EffectsAndModules"), true);
		mEffectNodePanel = new EffectNodePanel(item.GetParent());
		mEffectNodePanel->SetActor(mEffectActor);
		mEffectNodePanel->SetSize(size.GetWidth(), (int)((float)size.GetHeight()/2.3f));
		mEffectNodePanel->SetParent1(this);
		mFoldPaneBar->AddFoldPanelWindow(item, mEffectNodePanel);
		mFoldPaneBar->Expand(item);

		item = mFoldPaneBar->AddFoldPanel(
			PX2_LM.GetValue("Property"), true);
		mEffectPropGrid = new EffectPropertyGrid(item.GetParent());
		mEffectPropGrid->SetSize(size.GetWidth(), (int)((float)size.GetHeight()));
		mFoldPaneBar->AddFoldPanelWindow(item, mEffectPropGrid);
		mFoldPaneBar->Expand(item);
		mEffectPropGrid->SetObject(mEffectActor);

		mInitSized = true;
	}

	if (mFoldPaneBar)
	{
		mFoldPaneBar->SetSize(size);
		mFoldPaneBar->Layout();
	}
}
//-----------------------------------------------------------------------------
void EffectInspector::SetActor (PX2::EffectActor *actor)
{
	mEffectActor = actor;

	if (mEffectPropGrid)
		mEffectPropGrid->SetObject(mEffectActor);
}
//-----------------------------------------------------------------------------
void EffectInspector::TryRefreshModule (void *pointer)
{
	if (mEffectPropGrid)
	{
		mEffectPropGrid->TryRefreshModule(pointer);
	}
}
//-----------------------------------------------------------------------------
void EffectInspector::TryRefreshModulePoints (void *pointer)
{
	if (mEffectPropGrid)
	{
		mEffectPropGrid->TryRefreshModulePoints(pointer);
	}
}
//-----------------------------------------------------------------------------