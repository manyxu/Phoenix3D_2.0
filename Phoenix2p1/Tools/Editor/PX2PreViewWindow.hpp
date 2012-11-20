/*
*
* ÎÄ¼þÃû³Æ	£º	PX2PreViewWindow.hpp
*
*/

#ifndef PX2PREVIEWWINDOW_HPP
#define PX2PREVIEWWINDOW_HPP

#include "PX2EditorPre.hpp"

namespace PX2Editor
{

	class PreViewWindow : public wxWindow, public PX2::EventHandler
	{
	public:
		PreViewWindow ();
		PreViewWindow (wxWindow *parent);
		virtual ~PreViewWindow ();

		DECLARE_DYNAMIC_CLASS(PreViewWindow)
		
		void SetObject (PX2::Object *obj);

		void OnPaint(wxPaintEvent& e);

	protected:
		DECLARE_EVENT_TABLE()
	};

}

#endif