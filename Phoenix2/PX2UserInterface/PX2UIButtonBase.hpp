/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2UIButtonBase.hpp
*
* 版本		:	1.0 (2011/02/25)
*
* 作者		：	more
*
*/

#ifndef PX2UIBUTTONBASE_HPP
#define PX2UIBUTTONBASE_HPP

#include "PX2UIPrerequisites.hpp"
#include "PX2UIPictureBox.hpp"

namespace PX2
{

	class UIButtonBase : public UIElement
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;

	public:
		UIButtonBase (UIElement *parent, int ID, std::string name,
			const std::string &normal="",
			const std::string &mouseOver="",
			const std::string &mouseDown="",
			const std::string &disabled="",
			const std::string &text="button",
			float deltaX=0.0f, float deltaY=0.0f,
			float width=100.0f,	float height=100.0f,
			bool visible=true,
			int tableIndex=0,
			bool tableEnable=false);
		virtual ~UIButtonBase ();

		virtual void SetPosition (float offsetParentX, float offsetParentY);
		virtual void SetSize (float width, float height);
		virtual void Move (float deltaX, float deltaY);

		// 按钮状态
		enum ButtonState
		{
			BS_NORMAL,
			BS_MOUSEOVER,
			BS_MOUSEDOWN,
			BS_DISABLED,
			BS_QUANTITY
		};

		virtual ButtonState GetButtonState () const;
		virtual void SetButtonState (ButtonState buttonState);

		// picturebox
		void SetPictureBox (ButtonState state, std::string textureName);
		void SetPictureBox (ButtonState state, UIPictureBox *pictureBox);
		UIPictureBox *GetPictureBoxAtCurState () const;
		UIPictureBox *GetPictureBox (ButtonState state) const;

		// 事件
		virtual void OnEvent (Event *event);

		virtual void GetVisibleSet (VisibleSet &set);

		virtual void Draw (Renderer *renderer);

	protected:
		// 抽象基类
		UIButtonBase ();

		UIPictureBoxPtr mPicNormal;
		UIPictureBoxPtr mPicMouseOver;
		UIPictureBoxPtr mPicMouseDown;
		UIPictureBoxPtr mPicDisabled;
		ButtonState mButtonState;
	};

}

#endif