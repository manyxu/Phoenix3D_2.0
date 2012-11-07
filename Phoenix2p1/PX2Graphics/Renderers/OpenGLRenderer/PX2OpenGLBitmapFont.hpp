/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2OpenGLBitmapFont.hpp
*
* 版本		:	1.0 (2011/05/14)
*
* 作者		：	TimeX
*
*/

#ifndef PX2OPENGLBITMAPFONT_HPP
#define PX2OPENGLBITMAPFONT_HPP

#include "PX2OpenGLPrerequisites.hpp"

namespace PX2
{

	class BitmapFontChar
	{
	public:
		BitmapFontChar (int xOrigin, int yOrigin, int xSize, int ySize,
			const unsigned char* bitmap)
		{
			mXOrigin = xOrigin;
			mYOrigin = yOrigin;
			mXSize = xSize;
			mYSize = ySize;
			mBitmap = bitmap;
		}

		int mXOrigin, mYOrigin, mXSize, mYSize;
		const unsigned char* mBitmap;
	};

	class BitmapFont
	{
	public:
		BitmapFont (const char* name, int numCharacters,
			const BitmapFontChar* const* characters)
		{
			mName = name;
			mNumCharacters = numCharacters;
			mCharacters = characters;
		}

		const char* mName;
		int mNumCharacters;
		const BitmapFontChar* const* mCharacters;
	};

	extern const BitmapFont gVerdanaS16B0I0;

}

#endif
