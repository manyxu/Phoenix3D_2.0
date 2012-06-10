/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ModelInspector.cpp
*
*/

#include "PX2ModelInspector.hpp"
#include "PX2ModelActorPropertyGrid.hpp"
#include "PX2ModelPhysicsPropertyGrid.hpp"
#include "PX2PhysicsPanel.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(ModelInspector, wxWindow)
	EVT_SIZE(ModelInspector::OnSize)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ModelInspector::ModelInspector (wxWindow *parent)
:
wxScrolledWindow(parent),
mFoldPaneBar(0),
mModelActorPropGrid(0)
{
	SetScrollbars(0, 10, 0, 300 );

	mFoldPaneBar = new wxFoldPanelBar(this, wxID_ANY, 
		wxDefaultPosition, wxDefaultSize, wxFPB_DEFAULT_STYLE|wxFPB_VERTICAL,
		0);

	wxFoldPanel item = mFoldPaneBar->AddFoldPanel(_T("General"), true);
	mModelActorPropGrid = new ModelActorPropertyGrid(item.GetParent());
	mFoldPaneBar->AddFoldPanelWindow(item, mModelActorPropGrid);
	PX2::EventWorld::GetSingleton().ComeIn(mModelActorPropGrid);

	item = mFoldPaneBar->AddFoldPanel(_T("Material"), false);
	mMaterialPanel = new MaterialPanel(item.GetParent());
	mFoldPaneBar->AddFoldPanelWindow(item, mMaterialPanel);

	item = mFoldPaneBar->AddFoldPanel(_T("Physics"), false);
	mPhysicsPanel = new PhysicsPanel(item.GetParent());
	mFoldPaneBar->AddFoldPanelWindow(item, mPhysicsPanel);
}
//-----------------------------------------------------------------------------
ModelInspector::~ModelInspector ()
{

}
//-----------------------------------------------------------------------------
ModelInspector::ModelInspector ()
{

}
//-----------------------------------------------------------------------------
void ModelInspector::SetActor (PX2::Actor *actor)
{
	mActor = actor;
	mModelActorPropGrid->SetObject(actor);

	if (!mActor)
		return;
	
	PX2::Movable *mov = actor->GetMovable();
	PX2::Renderable *ren = DynamicCast<Renderable>(mov);

	if (ren)
	{
		mMaterialPanel->SetRenderable(ren);
	}

	if (mov)
	{
		mPhysicsPanel->SetActor(mActor);
	}
}
//-----------------------------------------------------------------------------
void ModelInspector::OnSize(wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	size.y += 100;

	if (mFoldPaneBar)
		mFoldPaneBar->SetSize(size);

	if (mModelActorPropGrid)
		mModelActorPropGrid->SetSize(size.GetWidth(), 400);
}
//-----------------------------------------------------------------------------
void ModelInspector::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void ModelInspector::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void ModelInspector::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::AddSelectActor))
	{
		int selectQuantity = ActorSelection::GetSingleton().GetActorQuantity();
		if (selectQuantity == 1)
		{
			Actor *actor = event->GetData<Actor*>();

			SetActor(actor);
		}
		else
		{
			SetActor(0);
		}
	}
	else if (EditorEventSpace::IsEqual(event, 
		EditorEventSpace::ClearSelectActor))
	{
		SetActor(0);
	}

	if (EditorEventSpace::IsEqual(event,
		EditorEventSpace::RemoveActor))
	{
		Actor *actor = event->GetData<Actor*>();

		if (actor == mActor)
			SetActor(0);
	}
}
//-----------------------------------------------------------------------------
void ModelInspector::DoLeave ()
{

}
//-----------------------------------------------------------------------------