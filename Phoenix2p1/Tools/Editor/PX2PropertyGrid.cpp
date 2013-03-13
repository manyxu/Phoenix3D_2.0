/*
*
* ÎÄ¼þÃû³Æ	£º	PX2Inspector.cpp
*
*/

#include "PX2PropertyGrid.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(PX2Editor::PropertyGrid, wxWindow)
BEGIN_EVENT_TABLE(PropertyGrid, wxWindow)
	EVT_SIZE(PropertyGrid::OnSize)
	EVT_MOVE(PropertyGrid::OnMove)
	EVT_PG_CHANGED(PGT_MAX_TYPE, PropertyGrid::OnPropertyGridChange)
	EVT_PG_CHANGING(PGT_MAX_TYPE, PropertyGrid::OnPropertyGridChanging)
	EVT_PG_SELECTED(PGT_MAX_TYPE, PropertyGrid::OnPropertyGridSelect)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
PropertyGrid::PropertyGrid ()
:
wxWindow(NULL, -1),
mPropGridManager(0)
{
}
//-----------------------------------------------------------------------------
PropertyGrid::PropertyGrid (wxWindow *parent, PropertyGridType type)
	:
wxWindow(parent, -1),
mPropertyGridType(type),
mPropGridManager(0)
{
	Create(
		wxPG_BOLD_MODIFIED |
		wxPG_SPLITTER_AUTO_CENTER |
		wxPG_TOOLBAR |
		wxPG_DESCRIPTION,
		wxPG_EX_MODE_BUTTONS
		| wxPG_EX_ENABLE_TLP_TRACKING
		| wxPG_EX_MULTIPLE_SELECTION
		);

	mPropGridManager->RegisterAdditionalEditors();
}
//-----------------------------------------------------------------------------
PropertyGrid::~PropertyGrid ()
{
	mActivePage = 0;
	for (int i=0; i<(int)mPages.size(); i++)
	{
		mPages[i] = 0;
	}

	if (mPropGridManager)
		mPropGridManager->Clear();
}
//-----------------------------------------------------------------------------
void PropertyGrid::Create (int style, int extraStyle)
{
	if (style == -1)
		style =
		wxPG_BOLD_MODIFIED |
		wxPG_SPLITTER_AUTO_CENTER |
		wxPG_AUTO_SORT |
		wxPG_TOOLBAR |
		wxPG_DESCRIPTION;

	if (extraStyle == -1)
		extraStyle = wxPG_EX_MODE_BUTTONS
		| wxPG_EX_MULTIPLE_SELECTION;

	mPropGridManager = new wxPropertyGridManager(this, mPropertyGridType,
		wxDefaultPosition, wxDefaultSize, style);

	mPropGrid = mPropGridManager->GetGrid();

	mPropGridManager->SetExtraStyle(extraStyle);
	mPropGridManager->SetValidationFailureBehavior(
		wxPG_VFB_BEEP|wxPG_VFB_MARK_CELL|wxPG_VFB_SHOW_MESSAGE);
	mPropGridManager->GetGrid()->SetVerticalSpacing(2);

	wxPGCell cell;
	cell.SetText(wxT("Unspecified"));
	cell.SetFgCol(*wxLIGHT_GREY);
	mPropGrid->SetUnspecifiedValueAppearance(cell);

	mPropGridManager->SetDescBoxHeight(40);
}
//-----------------------------------------------------------------------------
void PropertyGrid::Clear ()
{
	mPages.clear();
	mPropGridManager->Clear();
}
//-----------------------------------------------------------------------------
PropertyPage *PropertyGrid::AddPropertyPage (std::string name)
{
	PropertyPage *page = new0 PropertyPage(this, name);
	mPages.push_back(page);

	return page;
}
//-----------------------------------------------------------------------------
PropertyPage *PropertyGrid::GetPropertyPage (std::string name)
{
	for (int i=0; i<(int)mPages.size(); i++)
	{
		if (name == mPages[i]->GetName())
			return mPages[i];
	}

	return 0;
}
//-----------------------------------------------------------------------------
PropertyPage *PropertyGrid::GetPropertyPage (wxPGProperty *prop)
{
	for (int i=0; i<(int)mPages.size(); i++)
	{
		if (mPages[i]->HasProperty(prop))
			return mPages[i];
	}

	return 0;
}
//-----------------------------------------------------------------------------
void PropertyGrid::RemovePropertyPage (std::string name)
{
	std::vector<PropertyPagePtr>::iterator it = mPages.begin();
	for (; it!=mPages.end(); it++)
	{
		if ((*it)->GetName() == name)
		{
			mPages.erase(it);
			return;
		}
	}
}
//-----------------------------------------------------------------------------
void PropertyGrid::RemoveAll ()
{
	mPages.clear();
}
//-----------------------------------------------------------------------------
void PropertyGrid::ActivatePropertyPage (std::string name)
{
	PropertyPage *page = GetPropertyPage(name);
	mActivePage = page;
}
//-----------------------------------------------------------------------------
void PropertyGrid::ActivatePropertyPage (PropertyPage *page)
{
	mActivePage = page;
}
//-----------------------------------------------------------------------------
PropertyPage *PropertyGrid::GetActivatePage ()
{
	return mActivePage;
}
//-----------------------------------------------------------------------------
void PropertyGrid::OnSize(wxSizeEvent& e)
{
	wxSize size = e.GetSize();
	mPropGridManager->SetSize(size);
}
//-----------------------------------------------------------------------------
void PropertyGrid::OnMove(wxMoveEvent& e)
{

}
//-----------------------------------------------------------------------------
void PropertyGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	for (int i=0; i<(int)mPages.size(); i++)
	{
		mPages[i]->OnPropertyGridChange(event);
	}
}
//-----------------------------------------------------------------------------
void PropertyGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
	for (int i=0; i<(int)mPages.size(); i++)
	{
		mPages[i]->OnPropertyGridChanging(event);
	}
}
//-----------------------------------------------------------------------------
void PropertyGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	for (int i=0; i<(int)mPages.size(); i++)
	{
		mPages[i]->OnPropertyGridSelect(event);
	}
}
//-----------------------------------------------------------------------------
void PropertyGrid::DoEnter ()
{

}
//-----------------------------------------------------------------------------
void PropertyGrid::DoExecute (PX2::Event *event)
{

}
//-----------------------------------------------------------------------------
void PropertyGrid::DoLeave ()
{

}
//-----------------------------------------------------------------------------