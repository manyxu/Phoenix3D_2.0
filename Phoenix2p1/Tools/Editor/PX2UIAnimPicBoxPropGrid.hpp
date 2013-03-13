/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIAnimPicBoxPropGrid.hpp
*
*/

#ifndef PX2UIANIMPICBOXPROPGRID_HPP
#define PX2UIANIMPICBOXPROPGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"
#include "PX2UIAnimPicBox.hpp"

namespace PX2Editor
{

	class UIAnimPicBoxPropGrid : public ObjectPropertyGrid
	{
	public:
		UIAnimPicBoxPropGrid (wxWindow *parent);
		virtual ~UIAnimPicBoxPropGrid ();

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		UIAnimPicBoxPropGrid ();

		PX2::UIAnimPicBoxPtr mUIAnimPicBox;
		std::string mObjectType;
		float mIntervalTime;
		int mRepeatType;
		PX2::Float3 mColor;
		float mAlpha;
		float mWidth;
		float mHeight;
		std::string mTexPack;
		bool mIsDoubleSide;
	};

}

#endif