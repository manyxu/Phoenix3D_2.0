/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIFramePropGrid.cpp
*
*/

#include "PX2UIFramePropGrid.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2ObjectNameProperty.hpp"
#include "PX2MovableTransProperty.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
UIFramePropGrid::UIFramePropGrid (wxWindow *parent)
	:
ObjectPropertyGrid(parent)
{
	mPropertyGridType = PGT_UIFRAME;
}
//-----------------------------------------------------------------------------
UIFramePropGrid::~UIFramePropGrid ()
{
}
//-----------------------------------------------------------------------------
void UIFramePropGrid::OnSetObject(PX2::Object *object)
{
	Clear();

	mUIFrame = DynamicCast<UIFrame>(object);

	if (!mUIFrame)
		return;

	AddPropertyPage("General");
	PropertyPage *page = GetPropertyPage("General");

	page->AddProperty(PX2_LM.GetValue("General"), Property::PT_CATEGORY, 0);
	Property *propName = new ObjectNameProperty(page, PX2_LM.GetValue("Name"), 
		mUIFrame);
	mObjectType = mUIFrame->GetRttiType().GetName();
	Property *propType = new Property(page, PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mObjectType, false);
	Property *propTrans = new MovableTransProperty(page,
		PX2_LM.GetValue("Trans"), mUIFrame);
}
//-----------------------------------------------------------------------------
void UIFramePropGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);
}
//-----------------------------------------------------------------------------
void UIFramePropGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void UIFramePropGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void UIFramePropGrid::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void UIFramePropGrid::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void UIFramePropGrid::DoLeave ()
{
}
//-----------------------------------------------------------------------------