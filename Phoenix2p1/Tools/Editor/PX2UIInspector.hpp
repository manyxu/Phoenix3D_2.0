/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIInspector.hpp
*
*/

#ifndef PX2UIINSPECTOR_HPP
#define PX2UIINSPECTOR_HPP

#include "PX2EditorPre.hpp"
#include "PX2UIPicBox.hpp"
#include "PX2UIStaticText.hpp"
#include "PX2UIButton.hpp"
#include "PX2ObjectPropertyGrid.hpp"

namespace PX2Editor
{

	class UIInspacetor : public wxScrolledWindow
	{
	public:
		UIInspacetor (wxWindow *parent);
		virtual ~UIInspacetor ();

		void SetUIObject (PX2::Movable *mov);

		void OnSize(wxSizeEvent& e);

	protected:
		DECLARE_EVENT_TABLE()

		PX2::MovablePtr mUIObject;
		ObjectPropertyGrid *mGrid;
	};

}

#endif