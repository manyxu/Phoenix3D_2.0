/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ViewCtrl.cpp
*
*/

#include "PX2ViewCtrl.hpp"
#include "PX2RenderViewWindow.hpp"
using namespace PX2Editor;
using namespace PX2;

//----------------------------------------------------------------------------
ViewCtrl::ViewCtrl (ViewCtrlInst *inst)
	:
mWindow(0),
mViewCtrlInst(inst)
{
}
//----------------------------------------------------------------------------
ViewCtrl::~ViewCtrl ()
{
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleLeftDown (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleLeftUp (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleMiddleDown (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleMiddleUp (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleMouseWheel (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleRightDown (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleRightUp (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleMotion (RenderViewWindow *win, wxMouseEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleKeyDown (RenderViewWindow *win, wxKeyEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleKeyUp (RenderViewWindow *win, wxKeyEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::HandleChar (RenderViewWindow *win, wxKeyEvent &e)
{
	PX2_UNUSED(win);
	e.Skip();
}
//----------------------------------------------------------------------------
void ViewCtrl::StartMouseDrag(wxMouseEvent& e)
{
	mPixelToWorld = mWindow->StartMouseDrag(e);
	mLastMousePoint = e.GetPosition();
}
//----------------------------------------------------------------------------
void ViewCtrl::EndMouseDrag(wxMouseEvent& e)
{
	mWindow->EndMouseDrag(e);
}
//----------------------------------------------------------------------------
void ViewCtrl::AttachToWindow (RenderViewWindow *win)
{
	mWindow = win;
}
//----------------------------------------------------------------------------