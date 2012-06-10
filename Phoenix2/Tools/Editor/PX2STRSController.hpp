/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2STRSController.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2STRSCONTROLLER_HPP
#define PX2STRSCONTROLLER_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2PaneController.hpp"

namespace PX2Editor
{

	class STRSController : public PaneController
	{
	public:
		STRSController(ControllerInstance *callback);
		~STRSController();

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
		void FinishClickSelection (wxMouseEvent& e);
		void FinishDragSelection (wxMouseEvent& e);
		void CalcSelectionBox (wxMouseEvent& e, PX2::Vector2f &topLeft, 
			PX2::Vector2f &bottomRight);
		void RightGetSelectPoint (wxMouseEvent& e);
		void DrawSelectBox(const wxPoint &from, const wxPoint &to);
		virtual void StartMouseDrag (wxMouseEvent &e);
		virtual void EndMouseDrag (wxMouseEvent &e);
		virtual void AttachToWindow (RenderViewWindow *win);

		bool mLeftDown;
		bool mRightDown;
		bool mMiddleDown;
		wxPen* mSelectPen;
		bool mDragSelect;
		wxPoint mLastSelectEnd;
		PX2Editor::SceneNodeCtrl *mAttachedCtrl;
		
		// State UnDo ReDo
		bool mTransChanged;
		EditCommandPtr mCommand; 
	};

}

#endif