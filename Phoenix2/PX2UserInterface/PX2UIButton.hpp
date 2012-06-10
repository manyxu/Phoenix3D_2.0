/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2UIButton.hpp
*
* 版本		:	1.0 (2011/02/25)
*
* 作者		：	more
*
*/

#ifndef PX2UIBUTTON_HPP
#define PX2UIBUTTON_HPP

#include "PX2UIPrerequisites.hpp"
#include "PX2UIButtonBase.hpp"

namespace PX2
{
	
	class UIButton : public UIButtonBase
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;

	public:
		UIButton (UIElement *parent, int ID, const std::string &name,
			const std::string &normal="",
			const std::string &mouseOver="",
			const std::string &mouseDown="",
			const std::string &mouseDisabled="",
			const std::string &text="button",
			float deltaX=0.0f, float deltaY=0.0f,
			float width=100.0f,	float height=100.0f,
			bool visible=true,
			int tableIndex=0,
			bool tableEnable=false,
			bool bPushed=false);

		virtual ~UIButton ();
	};

}

#endif