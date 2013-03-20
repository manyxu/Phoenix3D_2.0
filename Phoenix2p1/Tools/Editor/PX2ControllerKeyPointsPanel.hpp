/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ControllerKeyPoints.hpp
*
*/

#ifndef PX2CONTROLLERKEYPOINTSPANEL_HPP
#define PX2CONTROLLERKEYPOINTSPANEL_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class ControllerKeyPointsPanel : public wxPanel
	{
	public:
		ControllerKeyPointsPanel (wxWindow *parent);
		virtual ~ControllerKeyPointsPanel ();

	protected:
		DECLARE_EVENT_TABLE();

		ControllerKeyPointsPanel ();
	};

}

#endif