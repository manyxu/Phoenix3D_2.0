/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIStaticText.hpp
*
*/

#ifndef PX2UISTATICTEXT_HPP
#define PX2UISTATICTEXT_HPP

#include "PX2UIPre.hpp"
#include "PX2Font.hpp"
#include "PX2UIMaterial.hpp"

namespace PX2
{

	class UIStaticText : public TriMesh
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(UIStaticText);

	public:
		UIStaticText ();
		virtual ~UIStaticText ();

		void SetFont (const std::string &fontFilename, int fontWidth,
			int fontHeight,	unsigned int fontStyle=FES_NORMAL);
		Font *GetFont ();

		void SetText (std::string text);
		const std::string &GetText () const;

		// FES_NORMAL
		// FES_ITALIC
		// FES_UNDERLINE
		void SetFontStyle (int style);
		int GetFontStyle ();

		// FD_NORMAL 0
		// FD_SHADOW 1
		// FD_BORDER 2
		void SetDrawStyle (int style);
		int GetDrawStyle ();
		
		void SetColor (Float3 color);
		const Float3 &GetColor () const;

		void SetAlpha (float alpha);
		float GetAlpha ();

		void SetFontWidth (int width);
		int GetFontWidth ();
		void SetFontHeight (int height);
		int GetFontHeight ();

		void SetDoubleSide (bool d);
		bool IsDoubleSide ();

	protected:
		void ReCreate ();

		std::string mText;
		int mFontStyle;
		int mDrawStyle;	
		Float3 mColor;
		float mAlpha;
		std::string mFontFilename;
		int mFontWidth;
		int mFontHeight;
		bool mIsDoubleSide;
		UIMaterialPtr mMtl;
		MaterialInstancePtr mMtlInst;
		Texture2DPtr mFontTex;
		
		FontPtr mFont;
	};

	PX2_REGISTER_STREAM(UIStaticText);
	typedef Pointer0<UIStaticText> UIStaticTextPtr;
#include "PX2UIStaticText.inl"

}

#endif