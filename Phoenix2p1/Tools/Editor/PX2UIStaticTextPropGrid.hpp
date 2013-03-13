/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIStaticTextPropGrid.hpp
*
*/

#ifndef PX2UISTATICTEXTPROPGRID_HPP
#define PX2UISTATICTEXTPROPGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"
#include "PX2UIStaticText.hpp"

namespace PX2Editor
{

	class UIStaticTextPropGrid : public ObjectPropertyGrid
	{
	public:
		UIStaticTextPropGrid (wxWindow *parent);
		virtual ~UIStaticTextPropGrid ();

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		UIStaticTextPropGrid ();

		PX2::UIStaticTextPtr mStaticText;
		std::string mObjectType;
		std::string mText;
		int mFontWidth;
		int mFontHeight;
		bool mIsItalic;
		bool mIsUnderLine;
		bool mDoShader;
		int mDrawStyle;
		PX2::Float3 mColor;
		float mAlpha;
		bool mIsDoubleSide;
	};

}

#endif