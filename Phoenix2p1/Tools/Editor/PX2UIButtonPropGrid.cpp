/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIButtonPropGrid.cpp
*
*/

#include "PX2UIButtonPropGrid.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
UIButtonPropGrid::UIButtonPropGrid (wxWindow *parent)
	:
UIFramePropGrid(parent)
{
	mWidth = 0.0f;
	mHeight = 0.0f;
}
//-----------------------------------------------------------------------------
UIButtonPropGrid::~UIButtonPropGrid ()
{
}
//-----------------------------------------------------------------------------
void UIButtonPropGrid::OnSetObject(PX2::Object *object)
{
	UIFramePropGrid::OnSetObject(object);

	PropertyPage *page = GetPropertyPage("General");
	page->AddProperty(PX2_LM.GetValue("Size"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("Width"), Property::PT_FLOAT, &mWidth);
	page->AddProperty(PX2_LM.GetValue("Height"), Property::PT_FLOAT, &mHeight);
}
//-----------------------------------------------------------------------------
void UIButtonPropGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	UIFramePropGrid::OnPropertyGridChange(event);
}
//-----------------------------------------------------------------------------
void UIButtonPropGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
	UIFramePropGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void UIButtonPropGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	UIFramePropGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void UIButtonPropGrid::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void UIButtonPropGrid::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void UIButtonPropGrid::DoLeave ()
{
}
//-----------------------------------------------------------------------------