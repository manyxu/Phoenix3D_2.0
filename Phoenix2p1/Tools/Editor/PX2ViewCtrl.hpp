/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ViewCtrl.hpp
*
*/

#ifndef PX2VIEWCONTROLLER_HPP
#define PX2VIEWCONTROLLER_HPP

#include "PX2EditorLibPre.hpp"
#include "PX2EditorParams.hpp"

namespace PX2Editor
{

	class RenderViewWindow;
	class ViewCtrlInst;

	class ViewCtrl
	{
	public:
		ViewCtrl (ViewCtrlInst *inst);
		virtual ~ViewCtrl ();

		virtual void HandleLeftDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleLeftUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMiddleDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMiddleUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMouseWheel (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMotion (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleKeyDown (RenderViewWindow *win, wxKeyEvent &e);
		virtual void HandleKeyUp (RenderViewWindow *win, wxKeyEvent &e);
		virtual void HandleChar (RenderViewWindow *win, wxKeyEvent &e);

	protected:
		virtual void StartMouseDrag (wxMouseEvent &e);
		virtual void EndMouseDrag (wxMouseEvent &e);
		virtual void AttachToWindow (RenderViewWindow *win);

		std::pair<float, float> mPixelToWorld;
		wxPoint mLastMousePoint;
		RenderViewWindow *mWindow;
		ViewCtrlInst *mViewCtrlInst;
	};

}

#endif