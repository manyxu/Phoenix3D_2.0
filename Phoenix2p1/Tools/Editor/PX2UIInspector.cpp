/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIInspector.cpp
*
*/

#include "PX2UIInspector.hpp"
#include "PX2UIPicBoxPropGrid.hpp"
#include "PX2UIAnimPicBoxPropGrid.hpp"
#include "PX2UIStaticTextPropGrid.hpp"
#include "PX2UIFramePropGrid.hpp"
#include "PX2UIButtonPropGrid.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(UIInspacetor, wxScrolledWindow)
EVT_SIZE(UIInspacetor::OnSize)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
UIInspacetor::UIInspacetor (wxWindow *parent)
	:
wxScrolledWindow(parent),
mGrid(0)
{
}
//-----------------------------------------------------------------------------
UIInspacetor::~UIInspacetor ()
{
}
//-----------------------------------------------------------------------------
void UIInspacetor::SetUIObject (PX2::Movable *mov)
{
	mUIObject = mov;

	if (mGrid)
	{
		delete mGrid;
		mGrid = 0;
	}

	if (mUIObject->IsExactly(UIPicBox::TYPE))
	{
		mGrid = new UIPicBoxPropGrid(this);
	}
	else if (mUIObject->IsExactly(UIAnimPicBox::TYPE))
	{
		mGrid = new UIAnimPicBoxPropGrid(this);
	}
	else if (mUIObject->IsExactly(UIFrame::TYPE))
	{
		mGrid = new UIFramePropGrid(this);
	}
	else if (mUIObject->IsExactly(UIButton::TYPE))
	{
		mGrid = new UIButtonPropGrid(this);
	}
	else if (mUIObject->IsExactly(UIStaticText::TYPE))
	{
		mGrid = new UIStaticTextPropGrid(this);
	}

	if (mGrid)
	{
		mGrid->SetObject(mUIObject);
	}
}
//-----------------------------------------------------------------------------
void UIInspacetor::OnSize(wxSizeEvent& e)
{
	wxSize size = GetClientSize();

	if (mGrid)
		mGrid->SetSize(size);
}
//-----------------------------------------------------------------------------