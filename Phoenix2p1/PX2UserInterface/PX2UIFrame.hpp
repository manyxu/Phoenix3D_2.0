/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIFrame.hpp
*
*/

#ifndef PX2UIFRAME_HPP
#define PX2UIFRAME_HPP

#include "PX2UIPre.hpp"
#include "PX2Node.hpp"
#include "PX2Camera.hpp"
#include "PX2Event.hpp"

namespace PX2
{

	class UIPicBox;

	class UIFrame : public Node
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(UIFrame);

	public:
		UIFrame ();
		virtual ~UIFrame ();

		void RegistScriptHandler (std::string handler);
		void UnRegistScriptHandler ();

		virtual void OnEvent (Event *event);

	public_internal:
		virtual void OnChildPicked (int info, Movable *child);
		virtual void OnChildUIAfterPicked (int info, Movable *child);

	protected:
		std::string mScriptHandler;
	};

	PX2_REGISTER_STREAM(UIFrame);
	typedef Pointer0<UIFrame> UIFramePtr;

}

#endif