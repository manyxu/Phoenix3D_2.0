/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerKeyPoints.cpp
*
*/

#include "PX2ControllerKeyPointsPanel.hpp"
using namespace PX2Editor;

BEGIN_EVENT_TABLE(ControllerKeyPointsPanel, wxPanel)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
ControllerKeyPointsPanel::ControllerKeyPointsPanel (wxWindow *parent)
{
	const bool bSuccess = wxXmlResource::Get()->LoadPanel(this, parent, 
		TEXT("KeyPoints"));
}
//-----------------------------------------------------------------------------
ControllerKeyPointsPanel::~ControllerKeyPointsPanel ()
{
}
//-----------------------------------------------------------------------------