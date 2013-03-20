/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIPicBoxPropGrid.hpp
*
*/

#ifndef PX2UIPICBOXPROPGRID_HPP
#define PX2UIPICBOXPROPGRID_HPP

#include "PX2ObjectPropertyGrid.hpp"
#include "PX2UIPicBox.hpp"

namespace PX2Editor
{

	class UIPicBoxPropGrid : public ObjectPropertyGrid
	{
	public:
		UIPicBoxPropGrid (wxWindow *parent);
		virtual ~UIPicBoxPropGrid ();

		virtual void OnSetObject(PX2::Object *object);

		virtual void OnPropertyGridChange (wxPropertyGridEvent &event);
		virtual void OnPropertyGridChanging (wxPropertyGridEvent &event);
		virtual void OnPropertyGridSelect (wxPropertyGridEvent &event);

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		UIPicBoxPropGrid ();

		PX2::UIPicBoxPtr mUIPicBox;
		std::string mObjectType;
		PX2::Float2 mAnchorPoint;
		PX2::Float3 mColor;
		float mAlpha;
		float mWidth;
		float mHeight;
		std::string mTexResPath;
		bool mIsDoubleSide;
	};

}

#endif