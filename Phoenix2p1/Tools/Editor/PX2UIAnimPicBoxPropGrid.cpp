/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIAnimPicBoxPropGrid.cpp
*
*/

#include "PX2UIAnimPicBoxPropGrid.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2ObjectNameProperty.hpp"
#include "PX2MovableTransProperty.hpp"
#include "PX2EditSystem.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
UIAnimPicBoxPropGrid::UIAnimPicBoxPropGrid (wxWindow *parent)
	:
ObjectPropertyGrid(parent)
{
	mPropertyGridType = PGT_UIANIMPICBOX;
	mIntervalTime = 0.01f;
	mRepeatType = 0;
	mColor = Float3::WHITE;
	mAlpha = 1.0f;
	mWidth = 0.0f;
	mHeight = 0.0f;
	mIsDoubleSide = false;
}
//-----------------------------------------------------------------------------
UIAnimPicBoxPropGrid::~UIAnimPicBoxPropGrid ()
{
}
//-----------------------------------------------------------------------------
void AnimButCall (Property *p)
{
	std::string name = EditSystem::GetSingleton().GetSelectedResourceName();
	if ("" == name)
		return;

	p->SetValue(name);
}
//-----------------------------------------------------------------------------
void UIAnimPicBoxPropGrid::OnSetObject(PX2::Object *object)
{
	Clear();

	mUIAnimPicBox = DynamicCast<UIAnimPicBox>(object);

	if (!mUIAnimPicBox)
		return;

	mColor = mUIAnimPicBox->GetColor();
	mAlpha = mUIAnimPicBox->GetAlpha();
	mWidth = mUIAnimPicBox->GetWidth();
	mHeight = mUIAnimPicBox->GetHeight();
	mTexPack = mUIAnimPicBox->GetFrameTexPack();
	mIsDoubleSide = mUIAnimPicBox->IsDoubleSide();

	mIntervalTime = mUIAnimPicBox->GetIntervalTime();
	mRepeatType = (int)mUIAnimPicBox->GetAPBCtrl()->Repeat;

	AddPropertyPage("General");
	PropertyPage *page = GetPropertyPage("General");

	page->AddProperty(PX2_LM.GetValue("General"), Property::PT_CATEGORY, 0);
	Property *propName = new ObjectNameProperty(page, PX2_LM.GetValue("Name"), 
		mUIAnimPicBox);
	mObjectType = mUIAnimPicBox->GetRttiType().GetName();
	Property *propType = new Property(page, PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mObjectType, false);
	Property *propTrans = new MovableTransProperty(page,
		PX2_LM.GetValue("Trans"), mUIAnimPicBox);

	page->AddProperty(PX2_LM.GetValue("Size"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("Width"), Property::PT_FLOAT, &mWidth);
	page->AddProperty(PX2_LM.GetValue("Height"), Property::PT_FLOAT, &mHeight);

	page->AddProperty(PX2_LM.GetValue("Material"), Property::PT_CATEGORY, 0);
	Property *propTexPack = page->AddProperty(PX2_LM.GetValue("TexPackFile"),
		Property::PT_STRINGBUTTON, &(mTexPack));
	propTexPack->SetButtonDownCallback(AnimButCall);
	page->AddProperty(PX2_LM.GetValue("Color"), Property::PT_COLOR3FLOAT3,
		&mColor);
	page->AddProperty(PX2_LM.GetValue("Alpha01"), Property::PT_FLOAT, &mAlpha);
	page->AddProperty(PX2_LM.GetValue("DoubleSide"), Property::PT_BOOLCHECK,
		&mIsDoubleSide);

	page->AddProperty(PX2_LM.GetValue("Animation"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("IntervalTime"), Property::PT_FLOAT, 
		&mIntervalTime);
	std::vector<std::string> repeats;
	repeats.push_back(PX2_LM.GetValue("RT_CLAMP"));
	repeats.push_back(PX2_LM.GetValue("RT_WRAP"));
	repeats.push_back(PX2_LM.GetValue("RT_CYCLE"));
	page->AddProperty(PX2_LM.GetValue("ControlRepeatType"),
		Property::PT_ENUM, &mRepeatType, true, &repeats);
}
//-----------------------------------------------------------------------------
void UIAnimPicBoxPropGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	wxPGProperty *prop = event.GetProperty();
	if (prop->GetName() == PX2_LM.GetValue("Color"))
	{
		mUIAnimPicBox->SetColor(mColor);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Alpha01"))
	{
		mUIAnimPicBox->SetAlpha(mAlpha);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Width"))
	{
		mUIAnimPicBox->SetWidth(mWidth);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Height"))
	{
		mUIAnimPicBox->SetHeight(mHeight);
	}
	else if (prop->GetName() == PX2_LM.GetValue("DoubleSide"))
	{
		mUIAnimPicBox->SetDoubleSide(mIsDoubleSide);
	}
	else if (prop->GetName() == PX2_LM.GetValue("IntervalTime"))
	{
		mUIAnimPicBox->SetIntervalTime(mIntervalTime);
	}
	else if (prop->GetName() == PX2_LM.GetValue("ControlRepeatType"))
	{
		mUIAnimPicBox->GetAPBCtrl()->Repeat = 
			(Controller::RepeatType)mRepeatType;
		mUIAnimPicBox->GetAPBCtrl()->Reset();
	}
	else if (prop->GetName() == PX2_LM.GetValue("TexPackFile"))
	{
		mUIAnimPicBox->SetFrameTexPack(mTexPack);
	}
}
//-----------------------------------------------------------------------------
void UIAnimPicBoxPropGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void UIAnimPicBoxPropGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void UIAnimPicBoxPropGrid::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void UIAnimPicBoxPropGrid::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void UIAnimPicBoxPropGrid::DoLeave ()
{
}
//-----------------------------------------------------------------------------
UIAnimPicBoxPropGrid::UIAnimPicBoxPropGrid ()
{
}
//-----------------------------------------------------------------------------