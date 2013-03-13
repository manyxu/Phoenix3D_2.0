/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIStaticTextPropGrid.cpp
*
*/

#include "PX2UIStaticTextPropGrid.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2ObjectNameProperty.hpp"
#include "PX2MovableTransProperty.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
UIStaticTextPropGrid::UIStaticTextPropGrid (wxWindow *parent)
	:
ObjectPropertyGrid(parent)
{
	mPropertyGridType = PGT_UISTATICTEXT;
	mFontWidth = 0;
	mFontHeight = 0;
	mIsItalic = false;
	mIsUnderLine = false;
	mColor = Float3::WHITE;
	mAlpha = 1.0f;
	mIsDoubleSide = false;
}
//-----------------------------------------------------------------------------
UIStaticTextPropGrid::~UIStaticTextPropGrid ()
{
}
//-----------------------------------------------------------------------------
void UIStaticTextPropGrid::OnSetObject(PX2::Object *object)
{
	Clear();

	mStaticText = DynamicCast<UIStaticText>(object);

	if (!mStaticText)
		return;

	AddPropertyPage("General");
	PropertyPage *page = GetPropertyPage("General");

	page->AddProperty(PX2_LM.GetValue("General"), Property::PT_CATEGORY, 0);
	Property *propName = new ObjectNameProperty(page, PX2_LM.GetValue("Name"), 
		mStaticText);
	mObjectType = mStaticText->GetRttiType().GetName();
	Property *propType = new Property(page, PX2_LM.GetValue("Type"),
		Property::PT_STRING, &mObjectType, false);

	Property *propTrans = new MovableTransProperty(page,
		PX2_LM.GetValue("Trans"), mStaticText);
	
	mFontWidth = mStaticText->GetFontWidth();
	mFontHeight = mStaticText->GetFontWidth();

	mText = mStaticText->GetText();
	mColor = mStaticText->GetColor();
	mAlpha = mStaticText->GetAlpha();
	mIsItalic = (mStaticText->GetFontStyle()&FES_ITALIC)!=0;
	mIsUnderLine = (mStaticText->GetFontStyle()&FES_UNDERLINE)!=0;
	mDrawStyle = mStaticText->GetDrawStyle();
	mIsDoubleSide = mStaticText->IsDoubleSide();

	page->AddProperty(PX2_LM.GetValue("StaticText"), Property::PT_CATEGORY, 0);
	page->AddProperty(PX2_LM.GetValue("FontWidth"), Property::PT_INT, &mFontWidth);
	page->AddProperty(PX2_LM.GetValue("FontHeight"), Property::PT_INT, &mFontHeight);
	page->AddProperty(PX2_LM.GetValue("UnderLine"), Property::PT_BOOLCHECK, &mIsUnderLine);

	std::vector<std::string> drawStyles;
	drawStyles.push_back(PX2_LM.GetValue("FD_NORMAL"));
	drawStyles.push_back(PX2_LM.GetValue("FD_SHADOW"));
	drawStyles.push_back(PX2_LM.GetValue("FD_BORDER"));
	page->AddProperty(PX2_LM.GetValue("DrawStyle"),
		Property::PT_ENUM, &mDrawStyle, true, &drawStyles);

	page->AddProperty(PX2_LM.GetValue("Text"), Property::PT_STRING, &mText);
	page->AddProperty(PX2_LM.GetValue("Color"), Property::PT_COLOR3FLOAT3,
		&mColor);
	page->AddProperty(PX2_LM.GetValue("Alpha01"), Property::PT_FLOAT, &mAlpha);
	page->AddProperty(PX2_LM.GetValue("DoubleSide"), Property::PT_BOOLCHECK,
		&mIsDoubleSide);
}
//-----------------------------------------------------------------------------
void UIStaticTextPropGrid::OnPropertyGridChange (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChange(event);

	wxPGProperty *prop = event.GetProperty();
	if (prop->GetName() == PX2_LM.GetValue("Text"))
	{
		mStaticText->SetText(mText);
	}
	else if (prop->GetName() == PX2_LM.GetValue("FontWidth"))
	{
		mStaticText->SetFontWidth(mFontWidth);
	}
	else if (prop->GetName() == PX2_LM.GetValue("FontHeight"))
	{
		mStaticText->SetFontHeight(mFontHeight);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Italic") 
		|| prop->GetName() == PX2_LM.GetValue("UnderLine"))
	{
		int fontStyle = FES_NORMAL;
		if (mIsItalic)
		{
			fontStyle |= FES_ITALIC;
		}

		if (mIsUnderLine)
		{
			fontStyle |= FES_UNDERLINE;
		}

		mStaticText->SetFontStyle(fontStyle);
	}
	else if (prop->GetName() == PX2_LM.GetValue("DrawStyle"))
	{
		mStaticText->SetDrawStyle(mDrawStyle);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Color"))
	{
		mStaticText->SetColor(mColor);
	}
	else if (prop->GetName() == PX2_LM.GetValue("Alpha01"))
	{
		mStaticText->SetAlpha(mAlpha);
	}
	else if (prop->GetName() == PX2_LM.GetValue("DoubleSide"))
	{
		mStaticText->SetDoubleSide(mIsUnderLine);
	}
}
//-----------------------------------------------------------------------------
void UIStaticTextPropGrid::OnPropertyGridChanging (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridChanging(event);
}
//-----------------------------------------------------------------------------
void UIStaticTextPropGrid::OnPropertyGridSelect (wxPropertyGridEvent &event)
{
	ObjectPropertyGrid::OnPropertyGridSelect(event);
}
//-----------------------------------------------------------------------------
void UIStaticTextPropGrid::DoEnter ()
{
}
//-----------------------------------------------------------------------------
void UIStaticTextPropGrid::DoExecute (PX2::Event *event)
{
}
//-----------------------------------------------------------------------------
void UIStaticTextPropGrid::DoLeave ()
{
}
//-----------------------------------------------------------------------------
UIStaticTextPropGrid::UIStaticTextPropGrid ()
{
}
//-----------------------------------------------------------------------------