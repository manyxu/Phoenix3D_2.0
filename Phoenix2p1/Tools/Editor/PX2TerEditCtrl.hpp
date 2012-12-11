/*
*
* ÎÄ¼þÃû³Æ	£º	PX2TerEditCtrl.hpp
*
*/

#ifndef PX2TEREDITCTRL_HPP
#define PX2TEREDITCTRL_HPP

#include "PX2EditorPre.hpp"
#include "PX2ViewCtrl.hpp"

namespace PX2Editor
{

	class TerEditCtrl : public ViewCtrl
	{
	public:
		TerEditCtrl (ViewCtrlInst *inst);
		virtual ~TerEditCtrl ();

		virtual void HandleLeftDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleLeftUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMiddleDown(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMiddleUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMouseWheel (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMotion (RenderViewWindow *win, wxMouseEvent &e);

	protected:
		void UpdateBrushPos (RenderViewWindow *win, wxMouseEvent &e);

		bool mLeftDown;
		bool mRightDown;
		bool mMiddleDown;
	};

}

#endif