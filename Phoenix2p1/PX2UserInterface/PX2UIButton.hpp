/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIButton.hpp
*
*/

#ifndef PX2UIBUTTON_HPP
#define PX2UIBUTTON_HPP

#include "PX2UIButtonBase.hpp"

namespace PX2
{

	class UIButton : public UIButtonBase
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(UIButton);

	public:
		UIButton ();
		virtual ~UIButton ();

		virtual void OnEvent (Event *event);

		void OnPressed ();
		void OnReleased ();

	protected:
		virtual void OnChildPicked (int info, Movable *child);
		virtual void OnNotPicked (int info);
	};

	PX2_REGISTER_STREAM(UIButton);
	typedef Pointer0<UIButton> UIButtonPtr;

}

#endif