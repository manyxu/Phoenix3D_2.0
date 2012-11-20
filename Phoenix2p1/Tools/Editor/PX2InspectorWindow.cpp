/*
*
* ÎÄ¼þÃû³Æ	£º	PX2InspectorWindow.cpp
*
*/

#include "PX2InspectorWindow.hpp"
using namespace PX2Editor;
using namespace PX2;

BEGIN_EVENT_TABLE(InspectorWindow, wxWindow)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
InspectorWindow::InspectorWindow (wxWindow *parent)
	:
wxWindow(parent, wxID_ANY)
{
}
//----------------------------------------------------------------------------
InspectorWindow::~InspectorWindow ()
{
}
//----------------------------------------------------------------------------
void InspectorWindow::DoEnter ()
{
}
//----------------------------------------------------------------------------
void InspectorWindow::DoExecute (PX2::Event *event)
{
	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------
void InspectorWindow::DoLeave ()
{
}
//----------------------------------------------------------------------------