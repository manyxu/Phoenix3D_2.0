/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	UIElement
*
* 版本		:	1.0 (2011/02/23)
*
* 作者		：	more
*
*/

#ifndef PX2UIELEMENT_HPP
#define PX2UIELEMENT_HPP

#include "PX2UIPrerequisites.hpp"
#include "PX2Object.hpp"
#include "PX2Float2.hpp"
#include "PX2Renderer.hpp"
#include "PX2OISEventAdapter.hpp"

namespace PX2
{

	class UIElement : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;

	public:
		UIElement (UIElement *parent, int ID, const std::string &name,
			float deltaX=0.0f, float deltaY=0.0f, 
			float width=100.0f, float height=100.0f,
			bool enable=true, 
			bool visible=true,
			int tableIndex=0, 
			bool tableEnable=false);
		virtual ~UIElement ();

		// 类型
		enum UIType
		{
			UT_LABEL,
			UT_PICTUREBOX,
			UT_BUTTON,
			UT_CHECKBOX,
			UT_RADIOBUTTON,
			UT_EDITBOX,
			UT_SCROLLBARHORI,
			UT_SCROLLBARVERTI,
			UT_LISTBOX,
			UT_DROPDOWNLIST,
			UT_GROUP,
			UT_PROGRESSBAR,
			UT_FILEFINDER,
			UT_PICTURESET,
			UT_ANIMATION,
			UT_QUANTITY
		};

		UIType GetUIType ();

		// ID
		void SetID (int ID);
		int GetID ();

		// 操作
		void SetEnable (bool enable=true);
		bool IsEnable ();
		void SetVisible (bool visible=true);
		bool IsVisible ();
		void SetFocus (bool focus);
		bool IsOnFocus ();
		bool IsMouseIn (); // 光标是否在控件范围内
		Float2 GetMousePosOverSize ();

		// 大小方位
		virtual void SetPosition (float offsetParentX, float offsetParentY);
		virtual void Move (float deltaX, float deltaY);
		const Float2 GetPosition () const;
		Float2 GetOffsetParent ();
		virtual void SetSize (float width, float height);
		Float2 GetSize ();

		// 层级
		void SetParent (UIElement *parent);
		UIElement *GetParent ();
		void SetShowLevel (int showLevel);
		int GetShowLevel ();

		// 事件
		virtual void OnEvent (Event *event);

		// 加入集合图形
		virtual void GetVisibleSet (VisibleSet &set);

		// 立刻绘制
		virtual void Draw (Renderer *renderer);

	protected:
		UIElement ();
		void JudgeMouseIn (Event *event);

		UIType mUIType;
		int mID;
		bool mEnable;
		bool mVisible;
		bool mOnFocus;
		bool mMouseIn;
		Float2 mMousePos;
		Float2 mMousePosOverSize;

		Float2 mOffsetParent;
		Float2 mPosition;
		Float2 mSize;
		int mShowLevel;	

		bool mTableEnable;
		int mTableIndex;

		UIElement *mParent;
	};

	typedef Pointer0<UIElement> UIElementPtr;

}

#endif