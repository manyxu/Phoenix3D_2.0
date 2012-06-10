/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ViewApp.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2VIEWAPP_HPP
#define PX2VIEWAPP_HPP

#include "PX2EditorPrerequisites.hpp"
#include "PX2EditorOptions.hpp"

namespace PX2Editor
{

	class ViewTopFrame;
	class ControllerManager;

	class ViewApp : public wxApp, public PX2::Singleton<ViewApp>
	{
	public:
		ViewApp ();
		~ViewApp ();

		// override
		virtual bool OnInit ();

	protected:
		void AddHandlers ();

		ViewTopFrame *mMainFrame;
		ControllerManager *mControllerManager;
		EditorOptions *mEditorOptions;
	};

	DECLARE_APP(ViewApp)
}

#endif