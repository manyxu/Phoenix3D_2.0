/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIPicBoxPropGrid.cpp
*
*/

#include "PX2UIPicBoxPropGrid.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2ObjectNameProperty.hpp"
#include "PX2MovableTransProperty.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
UIPicBoxPropGrid::UIPicBoxPropGrid (wxWindow *parent)
	:
ObjectPropertyGrid(parent)
{
	mPropertyGridType = PGT_UIPICBOX;
	mColor = Float3::WHITE;
	mAlpha = 1.0f;
	mWidth = 0.0f;
	mHeight = 0.0f;
	mIsDoubleSide = false;
}
//-----------------------------------------------------------------------------
UIPicBoxPropGrid::~UIPicBoxPropGrid ()
{
}
//-----------------------------------------------------------------------------
void UIPicBoxPropGrid::OnSetObject(PX2::Object *object)
{
	Clear();

	mUIPicBox = DynamicCast<UIPicBox>(object);

	if (!mUIPicBox)
		return;

	mColor = mUIPicBox->GetColor();
	mAlpha = mUIPicBox->GetAlpha();
	mWidth = mUIPicBox->GetWidth();
	mHeight = mUIPicBox->GetHeight();
	Texture2D *tex = mUIPicBox->GetTexture();
	if (tex)
	{
		mTexResPath = tex->GetResourcePath();
	}
	mIsDoubleSide = mUIPicBox->IsDoubleSide();

	AddPropertyPage("General");
	PropertyPage *page = GetPropertyPage("General");

	page->AddProperty(PX2_LM.GetValue("General"), Property::PT_CATEGORY, 0);
	Property *propName = new ObjectNameProperty(page, PX2_LM.GetValue("Name"), 
		mUIPicBox);
	mObjectType = mUIPicBox->GetRttiType().GetName();
	Property *propType = new Property(page, PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mObjectType, false);
	Property *propTrans = new MovableTransProperty(page,
		PX2_LM.GetValue("Trans"), mUIPicBox);

	page->AddProperty(PX2_LM.GetValue("Size"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("Width"), Property::PT_FLOAT, &mWidth);
	page->AddProperty(PX2_LM.GetValue("Height"), Property::PT_FLOAT, &mHeight);

	page->AddProperty(PX2_LM.GetValue("Material"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("Texture"), Property::PT_STRING,
		&(mTexResPath));
	page->AddProperty(PX2_LM.GetValue("Color"), Property::PT_COLOR3FLOAT3,
		&mColor);
	page->AddProperty(PX2_LM.GetValue("Alpha01"), Property::PT_FLOAT, &mAlpha);
	page->AddProperty(PX2_LM.GetValue("DoubleSide"), Property::PT_BOOLCHECK,
		&mIsDoubleSide);
}
//-----------------------------------------------------------------------------
void UIPicBoxPropGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	wxPGProperty *prop = event.GetProperty();
	if (prop->GetName() == PX2_LM.GetValue("Color"))
	{
		mUIPicBox->SetColor(mColor);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Alpha01"))
	{
		mUIPicBox->SetAlpha(mAlpha);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Width"))
	{
		mUIPicBox->SetWidth(mWidth);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Height"))
	{
		mUIPicBox->SetHeight(mHeight);
	}
	else if (prop->GetName() == PX2_LM.GetValue("DoubleSide"))
	{
		mUIPicBox->SetDoubleSide(mIsDoubleSide);
	}
}
//-----------------------------------------------------------------------------
void UIPicBoxPropGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);

	wxPGProperty *prop = event.GetProperty();
	if (prop->GetName() == PX2_LM.GetValue("Color"))
	{
		mUIPicBox->SetColor(mColor);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Alpha01"))
	{
		mUIPicBox->SetAlpha(mAlpha);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Width"))
	{
		mUIPicBox->SetWidth(mWidth);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Height"))
	{
		mUIPicBox->SetHeight(mHeight);
	}
	else if (prop->GetName() == PX2_LM.GetValue("DoubleSide"))
	{
		mUIPicBox->SetDoubleSide(mIsDoubleSide);
	}
}
//-----------------------------------------------------------------------------
void UIPicBoxPropGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void UIPicBoxPropGrid::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void UIPicBoxPropGrid::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void UIPicBoxPropGrid::DoLeave ()
{
}
//-----------------------------------------------------------------------------
UIPicBoxPropGrid::UIPicBoxPropGrid ()
{
}
//-----------------------------------------------------------------------------