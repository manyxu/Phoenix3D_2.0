/*
*
* ÎÄ¼þÃû³Æ	£º	PX2InspectorWindow.hpp
*
*/

#ifndef PX2INSPECTORWINDOW_HPP
#define PX2INSPECTORWINDOW_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class InspectorWindow : public wxWindow, public PX2::EventHandler
	{
	public:
		InspectorWindow (wxWindow *parent);
		~InspectorWindow ();

		virtual void DoEnter ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()
	};

}

#endif