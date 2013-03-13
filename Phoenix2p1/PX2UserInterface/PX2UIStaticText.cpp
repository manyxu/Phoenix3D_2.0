/*
*
* 文件名称	：	PX2StaticText.cpp
*
*/

#include "PX2UIStaticText.hpp"
#include "PX2UIManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, TriMesh, UIStaticText);
PX2_IMPLEMENT_STREAM(UIStaticText);
PX2_IMPLEMENT_FACTORY(UIStaticText);
PX2_IMPLEMENT_DEFAULT_NAMES(TriMesh, UIStaticText);

//----------------------------------------------------------------------------
UIStaticText::UIStaticText ()
{
	SetName("UIStaticText");

	SetRenderLayer(Renderable::RL_FRONT);

	mDrawStyle = FD_NORMAL;
	mColor = Float3::BLACK;
	mAlpha = 1.0f;
	mIsDoubleSide = false;

	SetVertexFormat(UIManager::GetSingleton().GetVertexFormat());

	mMtl = UIManager::GetSingleton().GetUIMaterial();
	mFont = UIManager::GetSingleton().GetFontManager()->GetDefaultFont();
	mFontFilename = mFont->GetFontFilename();
	mFontStyle = mFont->GetFontExtStyle();
	mFont->GetFontSize(mFontWidth, mFontHeight);

	mText = "DefaultText";
	SetFont(mFontFilename, mFontWidth, mFontHeight, mFontStyle);
}
//----------------------------------------------------------------------------
UIStaticText::~UIStaticText ()
{
}
//----------------------------------------------------------------------------
void UIStaticText::SetFont (const std::string &fontFilename, int fontWidth,
	int fontHeight,	unsigned int fontStyle)
{
	mFontFilename = fontFilename;
	mFontWidth = fontWidth;
	mFontHeight = fontHeight;
	mFontStyle = fontStyle;

	ReCreate();
}
//----------------------------------------------------------------------------
void UIStaticText::SetText (std::string text)
{
	mText = text;

	mFont->TextOutM(this, mText.c_str(), 0.0f, 0.0f, Float4(mColor[0], 
		mColor[1], mColor[2], mAlpha), mDrawStyle, true);

	mFontTex = mFont->GetTexture();
	if (mMtlInst)
	{
		mMtlInst->SetPixelTexture(0, "gDiffuseSampler", mFontTex);
	}
	else
	{
		mMtlInst = mMtl->CreateInstance(mFontTex);
		SetMaterialInstance(mMtlInst);
	}
}
//----------------------------------------------------------------------------
void UIStaticText::SetFontStyle (int style)
{
	if (mFontStyle == style)
		return;

	mFontStyle = style;
	ReCreate();
}
//----------------------------------------------------------------------------
void UIStaticText::SetDrawStyle (int style)
{
	if (style == mDrawStyle)
		return;

	mDrawStyle = style;
	ReCreate();
}
//----------------------------------------------------------------------------
void UIStaticText::SetColor (Float3 color)
{
	if (color == mColor)
		return;

	mColor = color;
	SetText(mText);
}
//----------------------------------------------------------------------------
void UIStaticText::SetAlpha (float alpha)
{
	if (alpha == mAlpha)
		return;

	mAlpha = alpha;
	SetText(mText);
}
//----------------------------------------------------------------------------
void UIStaticText::SetFontWidth (int width)
{
	if (width == mFontWidth || width<=0 || width>512)
		return;

	mFontWidth = width;

	ReCreate();
}
//----------------------------------------------------------------------------
void UIStaticText::SetFontHeight (int height)
{
	if (height == mFontHeight || height<=0 || height>512)
		return;

	mFontHeight = height;

	ReCreate();
}
//----------------------------------------------------------------------------
void UIStaticText::SetDoubleSide (bool d)
{
	if (mIsDoubleSide == d)
		return;

	mIsDoubleSide = d;

	if (d)
	{
		mMtl = UIManager::GetSingleton().GetUIMaterialDoubleSide();
	}
	else
	{
		mMtl = UIManager::GetSingleton().GetUIMaterial();
	}

	mMtlInst = mMtl->CreateInstance(mFontTex);
	SetMaterialInstance(mMtlInst);
}
//----------------------------------------------------------------------------
void UIStaticText::ReCreate ()
{
	mFont = UIManager::GetSingleton().GetFontManager()->CreateTypeFont(
		mFontWidth, mFontHeight, mFontFilename.c_str(), CCT_UTF8, mFontStyle);

	SetText(mText);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIStaticText::UIStaticText (LoadConstructor value)
	:
TriMesh(value)
{
}
//----------------------------------------------------------------------------
void UIStaticText::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	TriMesh::Load(source);

	source.ReadString(mText);
	source.Read(mFontStyle);
	source.Read(mDrawStyle);
	source.ReadAggregate(mColor);
	source.Read(mAlpha);
	source.ReadString(mFontFilename);
	source.Read(mFontWidth);
	source.Read(mFontHeight);
	source.ReadBool(mIsDoubleSide);
	source.ReadPointer(mMtl);
	source.ReadPointer(mMtlInst);
	source.ReadPointer(mFontTex);

	PX2_END_DEBUG_STREAM_LOAD(UIStaticText, source);
}
//----------------------------------------------------------------------------
void UIStaticText::Link (InStream& source)
{
	TriMesh::Link(source);

	source.ResolveLink(mMtl);
	source.ResolveLink(mMtlInst);
	source.ResolveLink(mFontTex);
}
//----------------------------------------------------------------------------
void UIStaticText::PostLink ()
{
	TriMesh::PostLink();

	mFont = UIManager::GetSingleton().GetFontManager()->CreateTypeFont(
		mFontWidth, mFontHeight, mFontFilename.c_str(), CCT_UTF8, mFontStyle);
}
//----------------------------------------------------------------------------
bool UIStaticText::Register (OutStream& target) const
{
	if (TriMesh::Register(target))
	{
		target.Register(mMtl);
		target.Register(mMtlInst);
		target.Register(mFontTex);

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UIStaticText::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	TriMesh::Save(target);

	target.WriteString(mText);
	target.Write(mFontStyle);
	target.Write(mDrawStyle);
	target.WriteAggregate(mColor);
	target.Write(mAlpha);
	target.WriteString(mFontFilename);
	target.Write(mFontWidth);
	target.Write(mFontHeight);
	target.WriteBool(mIsDoubleSide);
	target.WritePointer(mMtl);
	target.WritePointer(mMtlInst);
	target.WritePointer(mFontTex);

	PX2_END_DEBUG_STREAM_SAVE(UIStaticText, target);
}
//----------------------------------------------------------------------------
int UIStaticText::GetStreamingSize () const
{
	int size = TriMesh::GetStreamingSize();
	size += PX2_STRINGSIZE(mText);
	size += sizeof(mFontStyle);
	size += sizeof(mDrawStyle);
	size += sizeof(mColor);
	size += sizeof(mAlpha);
	size += PX2_STRINGSIZE(mFontFilename);
	size += sizeof(mFontWidth);
	size += sizeof(mFontHeight);
	size += PX2_BOOLSIZE(mIsDoubleSide);
	size += PX2_POINTERSIZE(mMtl);
	size += PX2_POINTERSIZE(mMtlInst);
	size += PX2_POINTERSIZE(mFontTex);

	return size;
}
//----------------------------------------------------------------------------