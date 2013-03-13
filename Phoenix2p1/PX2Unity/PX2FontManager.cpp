/*
*
* ÎÄ¼þÃû³Æ	£º	PX2FontManager.cpp
*
*/

#include "PX2FontManager.hpp"
#include "PX2FontGlyphMapFreeType.hpp"
#include "PX2CharCodingGBK.hpp"
#include "PX2CharCodingUTF8.hpp"
#include "PX2FontBitmapImpl.hpp"
#include "PX2FontCommonImpl.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
FontManager::FontManager ()
{
	FontGlyphMapFreeType::InitlizeFreeType();

	mDefaultFont = CreateTypeFont(32, 32, "Data/engine/arial.ttf", CCT_UTF8,
		FES_NORMAL);
}
//----------------------------------------------------------------------------
FontManager::~FontManager()
{
	FontGlyphMapFreeType::TerminateFreeType();
}
//----------------------------------------------------------------------------
Font *FontManager::CreateTypeFont (int fontWidth, int fontHeight, 
	const char *fontFilename, CharCodingType codingType,
	unsigned int fontExtStyle)
{
	for (int i=0; i<(int)mFonts.size(); i++)
	{
		if (mFonts[i]->IsSame(fontWidth, fontHeight, fontFilename,
			codingType, fontExtStyle))
			return mFonts[i];
	}

	FontCommonImpl *font = new0 FontCommonImpl(FontGlyphMap::GT_FREETYPE);
	if (!font->Initlize(fontWidth, fontHeight, fontFilename, codingType,
		fontExtStyle))
	{
		delete0(font);
		font = 0;
		return 0;
	}

	mFonts.push_back(font);

	return font;
}
//----------------------------------------------------------------------------
Font *FontManager::CreateBitmapFont (const char *fontFilename, 
	CharCodingType codingType)
{
	for (int i=0; i<(int)mFonts.size(); i++)
	{
		if (mFonts[i]->IsSame(0, 0, fontFilename,
			codingType, 0))
			return mFonts[i];
	}

	FontBitmapImpl *font = new0 FontBitmapImpl();
	if (!font->Initlize(fontFilename, codingType))
	{
		delete0(font);
		font = 0;
		return 0;
	}

	mFonts.push_back(font);

	return font;
}
//----------------------------------------------------------------------------
void FontManager::RenderText (TriMesh *mesh, Font *font, unsigned int style, 
	const char *text, float x, float y, const Float4 &color, float scale, 
	bool doTransfer, float depth)
{
	if (!font)
		return;

	PX2_UNUSED(scale);

	font->TextOutM(mesh, text, x, y, color, style, doTransfer, depth);
}
//----------------------------------------------------------------------------
void FontManager::RenderText (TriMesh *mesh, Font *font, unsigned int style,
	const char *text, Rectf &rect, float offsetX, float offsetY, bool autoWrap,
	const Float4 &color, float scale, bool doTransfer)
{
	if (!font)
		return;

	if ((int)mClipRects.size() > 0)
	{
		Rectf clipRect = mClipRects[0];

		if (rect.Bottom < clipRect.Bottom)
		{
			rect.Bottom = clipRect.Bottom;
		}
		if (rect.Top > clipRect.Top)
		{
			rect.Top = clipRect.Top;
		}
		if (rect.Left < clipRect.Left)
		{
			rect.Left = clipRect.Left;
		}
		if (rect.Right > clipRect.Right)
		{
			rect.Right = clipRect.Right;
		}
	}

	font->TextOutRect(mesh, text, rect, offsetX, offsetY, autoWrap, color,
		style, doTransfer, scale);
}
//----------------------------------------------------------------------------