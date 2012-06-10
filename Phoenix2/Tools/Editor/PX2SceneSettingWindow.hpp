/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2ShowSettingWindow.hpp
*
* 版本		:	1.0 (2011/02/29)
*
* 作者		：	more
*
*/

#ifndef PX2SCENESETTINGWINDOW_HPP
#define PX2SCENESETTINGWINDOW_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class SceneSettingPropertyGrid;

	class SceneSettingWindow : public wxWindow, public PX2::EventHandler
	{
	public:
		SceneSettingWindow (wxWindow *parent);
		~SceneSettingWindow ();

		void OnSize(wxSizeEvent& e);

		// 事件
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

	protected:
		DECLARE_EVENT_TABLE()

		SceneSettingPropertyGrid *mSettingPropertyGrid;
	};

}

#endif