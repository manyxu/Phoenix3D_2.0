/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2LightInspector.hpp
*
* 版本		:	1.0 (2012/03/18)
*
* 作者		：	more
*
*/

#ifndef PX2LIGHTINSPECTOR_HPP
#define PX2LIGHTINSPECTOR_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2LightActorPropertyGrid.hpp"

namespace PX2Editor
{

	class LightInspector : public wxWindow, public PX2::EventHandler
	{
	public:
		LightInspector (wxWindow *parent);
		~LightInspector ();

		void OnSize(wxSizeEvent& e);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		LightInspector ();

		DECLARE_EVENT_TABLE()

		wxFoldPanelBar *mFoldPaneBar;
		PropertyGrid *mPropGrid;
	};

}

#endif