/*
*
* ÎÄ¼þÃû³Æ	£º	PX2FontBitmapImpl.cpp
*
*/

#include "PX2FontBitmapImpl.hpp"
#include "PX2CharCodingUTF8.hpp"
#include "PX2CharCodingGBK.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
FontBitmapImpl::FontBitmapImpl ()
	:
Font(Font::FT_BITMAP)
{
	mTexWidth = FONT_TEXSIZE;
	mTexHeight = FONT_TEXSIZE;
	mCharNumMaxCache = 10000;
}
//----------------------------------------------------------------------------
FontBitmapImpl::~FontBitmapImpl ()
{
	if (mCharCodingObj)
	{
		delete0(mCharCodingObj);
		mCharCodingObj = 0;
	}
}
//----------------------------------------------------------------------------
bool FontBitmapImpl::Initlize (const char *fontFilename, 
	CharCodingType codingType)
{
	mFontFilename = fontFilename;

	if (CCT_UTF8 == codingType)
	{
		mCharCodingObj = new0 CharCodingUTF8();
	}
	else if (CCT_GBK == codingType)
	{
		mCharCodingObj = new0 CharCodingGBK();
	}

	mGlyphMap = this;

	return true;
}
//----------------------------------------------------------------------------
bool FontBitmapImpl::IsSame (int fontWidth, int fontHeight,	
	const char *fontFilename, CharCodingType codingType,
	unsigned int fontExtStyle)
{
	PX2_UNUSED(fontWidth);
	PX2_UNUSED(fontHeight);
	PX2_UNUSED(fontExtStyle);

	if (mCodingType != codingType)
		return false;

	return mFontFilename == std::string(fontFilename);
}
//----------------------------------------------------------------------------
void FontBitmapImpl::GetUnicodeCharSize (unsigned short wChar, float &width,
	float &height)
{
	std::map<unsigned int, BitmapFontGlyph>::iterator it
		= mMapGlyph.find(wChar);

	if (it == mMapGlyph.end())
	{
		width = (float)mCharWidth;
		height = (float)mCharHeight;
	}
	else
	{
		width = (float)(*it).second.numWidth;
		height = (float)mCharHeight;
	}
}
//----------------------------------------------------------------------------
unsigned char *FontBitmapImpl::GetUnicodeCharBitmap (unsigned short wChar)
{
	return 0;
}
//----------------------------------------------------------------------------
Texture2D *FontBitmapImpl::TexUVMaping (const unsigned char *character,
	Rectf &rectUV)
{
	unsigned int unicode = mCharCodingObj->ToUnicode(character);
	std::map<unsigned int, BitmapFontGlyph>::iterator it 
		= mMapGlyph.find(unicode);

	if (it == mMapGlyph.end())
	{
		rectUV.Set(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		rectUV = it->second.RectUV;
	}

	return mFontTex;
}
//----------------------------------------------------------------------------