/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIAnimPicBoxCtrl.hpp
*
*/

#ifndef PX2UIANIMPICBOXCONTROL_HPP
#define PX2UIANIMPICBOXCONTROL_HPP

#include "PX2UIPre.hpp"
#include "PX2Controller.hpp"
#include "PX2TexPackData.hpp"

namespace PX2
{

	class UIAnimPicBoxControl : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(UIAnimPicBoxControl);

	public:
		UIAnimPicBoxControl ();
		virtual ~UIAnimPicBoxControl ();

		virtual bool Update (double applicationTime);
	};
	PX2_REGISTER_STREAM(UIAnimPicBoxControl);
	typedef Pointer0<UIAnimPicBoxControl> UIAnimPicBoxControlPtr;

}

#endif