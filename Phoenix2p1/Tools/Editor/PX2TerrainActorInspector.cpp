/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ModelInspector.cpp
*
*/

#include "PX2TerrainActorInspector.hpp"
#include "PX2EditSystem.hpp"
#include "PX2LanguageManager.hpp"
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
mJunglerPanel(0),
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
			if (mBrushFold.GetItem())
				mBrushFold.GetItem()->Show(true);
			if (mEditFold.GetItem())
				mEditFold.GetItem()->Show(true);
			mTerrainActorPropGrid->EnableTerrainEdit(true);
		}
	}
	else
	{
		if (mInitSized)
		{
			if (mBrushFold.GetItem())
				mBrushFold.GetItem()->Show(false);
			if (mEditFold.GetItem())
				mEditFold.GetItem()->Show(false);
			mTerrainActorPropGrid->EnableTerrainEdit(false);
		}
	}
}
//-----------------------------------------------------------------------------
void TerrainActorInspector::RefreshSelectTerrainPage ()
{
	if (mEnableEdit)
	{
		TerrainProcess::TerProType proType = 
			EditSystem::GetSingleton().GetTerrainEdit()->GetEditType();
		if (proType == TerrainProcess::TPT_TEXTURE)
		{
			mMaterialPanel->RefleshCtrls();
		}
		else if (proType == TerrainProcess::TPT_JUNGLER)
		{
			mJunglerPanel->RefleshCtrls();
		}
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
	else if (2 == sel)
	{
		EditSystem::GetSingleton().GetTerrainEdit()->SetEditType(
			TerrainProcess::TPT_JUNGLER);

		if (mJunglerPanel)
			mJunglerPanel->RefleshCtrls();
	}
}
//-----------------------------------------------------------------------------
void TerrainActorInspector::OnSize(wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	if (!mInitSized)
	{
		mFoldPaneBar->SetSize(size);

		wxFoldPanel item = mFoldPaneBar->AddFoldPanel(
			PX2_LM.GetValue("General"), true);

		mTerrainActorPropGrid = new TerrainActorPropertyGrid(item.GetParent());
		mTerrainActorPropGrid->SetSize(size.GetWidth(), size.GetHeight()/3);
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
		mJunglerPanel = new TerrainJunglerPanel(mEditBook);
		mEditBook->AddPage(mJunglerPanel, PX2_LM.GetValue("Junglers"));
		mFoldPaneBar->AddFoldPanelWindow(mEditFold, mEditBook);	

		if (!mEnableEdit)
		{
			mBrushFold.GetItem()->Show(false);
			mEditFold.GetItem()->Show(false);
			mTerrainActorPropGrid->EnableTerrainEdit(false);
		}

		mInitSized = true;
	}
	else
	{
		if (mFoldPaneBar)
			mFoldPaneBar->SetSize(size);
	}
}
//-----------------------------------------------------------------------------