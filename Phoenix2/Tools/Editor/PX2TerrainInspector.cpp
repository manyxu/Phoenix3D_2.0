/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerrainInspector.cpp
*
*/

#include "PX2TerrainInspector.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(TerrainInspector, wxScrolledWindow)
EVT_SIZE(TerrainInspector::OnSize)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
TerrainInspector::TerrainInspector (wxWindow *parent)
:
wxScrolledWindow(parent),
mFoldPaneBar(0),
mPropGrid(0)
{
	SetScrollbars(0, 10, 0, 200 );

	mFoldPaneBar = new wxFoldPanelBar(this, wxID_ANY, 
		wxDefaultPosition, wxDefaultSize, wxFPB_DEFAULT_STYLE|wxFPB_VERTICAL,
		0);

	wxFoldPanel item = mFoldPaneBar->AddFoldPanel(_T("Property"), true);
	mPropGrid = new TerrainActorPropertyGrid(item.GetParent());
	mFoldPaneBar->AddFoldPanelWindow(item, mPropGrid);
	PX2::EventWorld::GetSingleton().ComeIn(mPropGrid);

	item = mFoldPaneBar->AddFoldPanel(_T("Brush"), false);
	mTerrainBrush = new TerrainBrushPanel(item.GetParent());
	mFoldPaneBar->AddFoldPanelWindow(item, mTerrainBrush);

	item = mFoldPaneBar->AddFoldPanel(_T("Height"), false);
	mTerrainHeight = new TerrainHeightPanel(item.GetParent());
	mFoldPaneBar->AddFoldPanelWindow(item, mTerrainHeight);

	item = mFoldPaneBar->AddFoldPanel(_T("Material"), false);
	mTerrainMaterial = new TerrainMaterialPanel(item.GetParent());
	mFoldPaneBar->AddFoldPanelWindow(item, mTerrainMaterial);
}
//-----------------------------------------------------------------------------
TerrainInspector::~TerrainInspector ()
{
}
//-----------------------------------------------------------------------------
TerrainInspector::TerrainInspector ()
{

}
//-----------------------------------------------------------------------------
void TerrainInspector::OnSize (wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	size.y += 100;

	if (mFoldPaneBar)
		mFoldPaneBar->SetSize(size);

	if (mPropGrid)
		mPropGrid->SetSize(size.GetWidth(), 400);
}
//-----------------------------------------------------------------------------
void TerrainInspector::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void TerrainInspector::DoUpdate ()
{

}
//-----------------------------------------------------------------------------
void TerrainInspector::DoExecute (PX2::Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::AddSelectActor))
	{
		int selectQuantity = ActorSelection::GetSingleton().GetActorQuantity();
		if (selectQuantity == 1)
		{
			Actor *actor = event->GetData<Actor*>();
			if (actor->IsDerived(RawTerrainActor::TYPE))
			{
				mTerrainBrush->RefleshCtrls();
				mTerrainHeight->RefleshCtrls();
				mTerrainMaterial->RefleshCtrls();
			}
		}
	}
	else if (EditorEventSpace::IsEqual(event, 
		EditorEventSpace::SelectTerrainPage))
	{
		mTerrainMaterial->RefleshCtrls();
	}
}
//-----------------------------------------------------------------------------
void TerrainInspector::DoLeave ()
{

}
//-----------------------------------------------------------------------------