/*
*
* ÎÄ¼þÃû³Æ	£º	PX2GeneralCtrl.hpp
*
*/

#ifndef PX2GVIEWCTRL_HPP
#define PX2GVIEWCTRL_HPP

#include "PX2EditorPre.hpp"
#include "PX2ViewCtrl.hpp"
#include "PX2SceneNodeCtrl.hpp"
#include "PX2EditCommand.hpp"

namespace PX2Editor
{

	class GViewCtrl : public ViewCtrl
	{
	public:
		GViewCtrl (ViewCtrlInst *inst);
		~GViewCtrl ();

		virtual void HandleLeftDown (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleLeftUp (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMiddleDown(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMiddleUp(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMouseWheel(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightDown(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleRightUp(RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleMotion (RenderViewWindow *win, wxMouseEvent &e);
		virtual void HandleKeyDown (RenderViewWindow *win, wxKeyEvent &e);
		virtual void HandleKeyUp (RenderViewWindow *win, wxKeyEvent &e);
		virtual void HandleChar (RenderViewWindow *win, wxKeyEvent &e);

	protected:
		virtual void StartMouseDrag (wxMouseEvent &e);
		virtual void EndMouseDrag (wxMouseEvent &e);
		virtual void AttachToWindow (RenderViewWindow *win);

		void FinishClickSelection (wxMouseEvent& e);
		void FinishDragSelection (wxMouseEvent& e);
		void CalcSelectionBox (wxMouseEvent& e, PX2::Vector2f &topLeft, 
			PX2::Vector2f &bottomRight);
		void RightGetSelectPoint (wxMouseEvent& e);
		void DrawSelectBox(const wxPoint &from, const wxPoint &to);

		bool mLeftDown;
		bool mRightDown;
		bool mMiddleDown;
		wxPen* mSelectPen;
		bool mDragRangeSelect;
		wxPoint mLastSelectEnd;
		PX2Editor::SceneNodeCtrl *mAttachedCtrl;

		// State UnDo ReDo
		bool mTransChanged;
		EditCommandPtr mCommand; 
	};

}

#endif