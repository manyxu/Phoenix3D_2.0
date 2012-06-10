/*
*
* ÎÄ¼þÃû³Æ	£º	PX2PaneController.cpp
*
*/

#include "PX2PaneController.hpp"
#include "PX2RenderViewWindow.hpp"
#include "PX2ControllerInstance.hpp"
using namespace PX2Editor;
using namespace PX2;

PaneController::PaneController (ControllerInstance* instance)
{
	mWindow = 0;
	mControllerInstance = instance;
}
//----------------------------------------------------------------------------
PaneController::~PaneController ()
{
}
//----------------------------------------------------------------------------
void PaneController::HandleLeftDown (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void PaneController::HandleLeftUp (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void PaneController::HandleMiddleDown (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void PaneController::HandleMiddleUp (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void PaneController::HandleMouseWheel (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void PaneController::HandleRightDown (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void PaneController::HandleRightUp (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void PaneController::HandleMotion (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void PaneController::HandleKeyDown (RenderViewWindow *win, wxKeyEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void PaneController::HandleKeyUp (RenderViewWindow *win, wxKeyEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void PaneController::HandleChar (RenderViewWindow *win, wxKeyEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
PaneController::PaneController ()
{
}
//----------------------------------------------------------------------------
void PaneController::StartMouseDrag(wxMouseEvent& e)
{
	mPixelToWorld = mWindow->StartMouseDrag(e);
	mLastMousePoint = e.GetPosition();
}
//----------------------------------------------------------------------------
void PaneController::EndMouseDrag(wxMouseEvent& e)
{
	mWindow->EndMouseDrag(e);
}
//----------------------------------------------------------------------------
void PaneController::AttachToWindow (RenderViewWindow *win)
{
	mWindow = win;
}
//----------------------------------------------------------------------------