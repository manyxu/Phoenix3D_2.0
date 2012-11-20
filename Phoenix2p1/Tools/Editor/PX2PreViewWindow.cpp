/*
*
* ÎÄ¼þÃû³Æ	£º	PX2PreViewWindow.cpp
*
*/

#include "PX2PreViewWindow.hpp"
using namespace PX2Editor;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(PX2Editor::PreViewWindow, wxWindow)
BEGIN_EVENT_TABLE(PreViewWindow, wxWindow)
EVT_PAINT(PreViewWindow::OnPaint)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
PreViewWindow::PreViewWindow ()
	:wxWindow(0, -1)
{
}
//----------------------------------------------------------------------------
PreViewWindow::PreViewWindow (wxWindow *parent)
	:
wxWindow(parent, -1, wxDefaultPosition, wxSize(200, 150))
{
}
//----------------------------------------------------------------------------
PreViewWindow::~PreViewWindow ()
{
}
//----------------------------------------------------------------------------
void PreViewWindow::OnPaint (wxPaintEvent& e)
{
	wxPaintDC dc(this);
}
//----------------------------------------------------------------------------