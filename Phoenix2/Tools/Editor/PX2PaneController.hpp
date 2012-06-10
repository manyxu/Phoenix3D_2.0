/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2PaneController.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2PANECONTROLLER_HPP
#define PX2PANECONTROLLER_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2EditorGeneral.hpp"

namespace PX2Editor
{

	class RenderViewWindow;
	class ControllerInstance;

	class PaneController
	{
	public:
		PaneController (ControllerInstance* callback);
		virtual ~PaneController ();

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
		wxPoint mLastMousePoint;
		PixelToWorld mPixelToWorld;
		RenderViewWindow *mWindow;
		ControllerInstance* mControllerInstance;

		PaneController ();
		virtual void StartMouseDrag (wxMouseEvent &e);
		virtual void EndMouseDrag (wxMouseEvent &e);
		virtual void AttachToWindow (RenderViewWindow *win);
	};

}

#endif