/*
*
* ÎÄ¼þÃû³Æ	£º	PX2FontManager.hpp
*
*/

#ifndef PX2FONTMANAGER_HPP
#define PX2FONTMANAGER_HPP

#include "PX2UnityPre.hpp"
#include "PX2FontDefine.hpp"
#include "PX2Font.hpp"

namespace PX2
{

	class FontManager
	{
	public:
		FontManager ();
		~FontManager();

		Font *GetDefaultFont ();

		Font *CreateTypeFont (int fontWidth, int fontHeight,
			const char *fontFilename, CharCodingType codingType,
			unsigned int fontExtStyle=FES_NORMAL);

		Font *CreateBitmapFont (const char *fontFilename,
			CharCodingType codingType);

		virtual void RenderText (TriMesh *mesh, Font *font, unsigned int style,
			const char *text, float x, float y, const Float4 &color, 
			float scale=1.0f, bool doTransfer=false, float depth=0.0f);

		virtual void RenderText (TriMesh *mesh, Font *font, unsigned int style,
			const char *text, Rectf &rect, float offsetX, float offsetY, 
			bool autoWrap, const Float4 &color, float scale=1.0f, 
			bool doTransfer=false);

	protected:
		FontPtr mDefaultFont;
		std::vector<FontPtr> mFonts;
		std::vector<Rectf> mClipRects;
	};

#include "PX2FontManager.inl"

}

#endif