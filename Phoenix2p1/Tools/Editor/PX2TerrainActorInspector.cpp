/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ModelInspector.cpp
*
*/

#include "PX2TerrainActorInspector.hpp"
using namespace PX2Editor;
using namespace PX2;

#define ID_INS_TER_BOOK wxID_HIGHEST+5002

BEGIN_EVENT_TABLE(TerrainActorInspector, wxScrolledWindow)
EVT_SIZE(TerrainActorInspector::OnSize)
EVT_BOOKCTRL_PAGE_CHANGED(ID_INS_TER_BOOK, TerrainActorInspector::OnPageChanged)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
TerrainActorInspector::TerrainActorInspector (wxWindow *parent)
	:
wxScrolledWindow(parent),
mFoldPaneBar(0),
mHeightPanel(0),
mMaterialPanel(0),
mTerrainActorPropGrid(0),
mInitSized(false),
mEnableEdit(false),
mEditBook(0)
{
	mFoldPaneBar = new wxFoldPanelBar(this, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxFPB_DEFAULT_STYLE|wxFPB_VERTICAL, 0);
}
//-----------------------------------------------------------------------------
TerrainActorInspector::~TerrainActorInspector ()
{
}
//-----------------------------------------------------------------------------
TerrainActorInspector::TerrainActorInspector ()
{
}
//-----------------------------------------------------------------------------
void TerrainActorInspector::SetActor (PX2::TerrainActor *actor)
{
	mTerrainActor = actor;

	if (mTerrainActorPropGrid)
		mTerrainActorPropGrid->SetObject(mTerrainActor);
}
//-----------------------------------------------------------------------------
void TerrainActorInspector::EnableEdit (bool enable)
{
	if (mEnableEdit == enable)
		return;

	mEnableEdit = enable;

	if (mEnableEdit)
	{
		if (mInitSized)
		{
			mBrushFold.GetItem()->Show(true);
			mEditFold.GetItem()->Show(true);
			mTerrainActorPropGrid->EnableTerrainEdit(true);
		}
	}
	else
	{
		if (mInitSized)
		{
			mBrushFold.GetItem()->Show(false);
			mEditFold.GetItem()->Show(false);
			mTerrainActorPropGrid->EnableTerrainEdit(false);
		}
	}
}
//-----------------------------------------------------------------------------
void TerrainActorInspector::RefreshSelectTerrainPage ()
{
	if (mMaterialPanel && mEnableEdit)
	{
		mMaterialPanel->RefleshCtrls();
	}
}
//-----------------------------------------------------------------------------
void TerrainActorInspector::OnPageChanged( wxBookCtrlEvent &event )
{
	int sel = event.GetSelection();
	if (0 == sel)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->SetEditType(
			TerrainProcess::TPT_HEIGHT);

		if (mHeightPanel)
			mHeightPanel->RefleshCtrls();		
	}
	else if (1 == sel)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->SetEditType(
			TerrainProcess::TPT_TEXTURE);

		if (mMaterialPanel)
			mMaterialPanel->RefleshCtrls();
	}
}
//-----------------------------------------------------------------------------
void TerrainActorInspector::OnSize(wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	if (mFoldPaneBar)
		mFoldPaneBar->SetSize(size);

	if (!mInitSized)
	{
		wxFoldPanel item = mFoldPaneBar->AddFoldPanel(
			PX2_LM.GetValue("General"), true);
		mTerrainActorPropGrid = new TerrainActorPropertyGrid(item.GetParent());
		mTerrainActorPropGrid->SetSize(size.GetWidth(), size.GetHeight()/4);
		mFoldPaneBar->AddFoldPanelWindow(item, mTerrainActorPropGrid);
		mFoldPaneBar->Expand(item);
		mTerrainActorPropGrid->SetObject(mTerrainActor);

		mBrushFold = mFoldPaneBar->AddFoldPanel(PX2_LM.GetValue("Brush"));
		mTerrainBrush = new TerrainBrushPanel(mBrushFold.GetParent());
		mFoldPaneBar->AddFoldPanelWindow(mBrushFold, mTerrainBrush);

		mEditFold = mFoldPaneBar->AddFoldPanel(PX2_LM.GetValue("Edit"));
		mEditBook = new wxBookCtrl(mEditFold.GetParent(), ID_INS_TER_BOOK);	
		mEditBook->SetPageSize(wxSize(size.GetWidth(), 500));
		mHeightPanel = new TerrainHeightPanel(mEditBook);
		mEditBook->AddPage(mHeightPanel, PX2_LM.GetValue("High"), true);
		mMaterialPanel = new TerrainMaterialPanel(mEditBook);
		mEditBook->AddPage(mMaterialPanel, PX2_LM.GetValue("Material"));
		mFoldPaneBar->AddFoldPanelWindow(mEditFold, mEditBook);	

		mFoldPaneBar->SetSize(size);

		if (!mEnableEdit)
		{
			mBrushFold.GetItem()->Show(false);
			mEditFold.GetItem()->Show(false);
			mTerrainActorPropGrid->EnableTerrainEdit(false);
		}

		mInitSized = true;
	}
}
//-----------------------------------------------------------------------------