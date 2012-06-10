/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2MVCViewLogWindow.hpp
*
* 版本		:	1.0 (2011/04/02)
*
* 作者		：	more
*
*/

#ifndef PX2VIEWLOGWINDOW_HPP
#define PX2VIEWLOGWINDOW_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class ViewLogWindow : public wxPanel
	{
	public:
		ViewLogWindow ();
		ViewLogWindow (wxWindow* parent);
		virtual ~ViewLogWindow ();

		DECLARE_DYNAMIC_CLASS(ViewLogWindow);

		void AddMessage (const wxString *msg);

	protected:
		wxTextCtrl *mTextCtrl;
	};

}

#endif