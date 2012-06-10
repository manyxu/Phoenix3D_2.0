/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2IOSEventAdapter.hpp
*
* 版本		:	1.0 (2011/02/03)
*
* 作者		：	more
*
*/

#ifndef PX2OISEVENTADAPTER_HPP
#define PX2OISEVENTADAPTER_HPP

#include "PX2Singleton.hpp"
#include "PX2EventHandler.hpp"
#include "PX2EventSpace.hpp"
#include "PX2EventSpaceRegister.hpp"
#include "PX2EventSpaceRegisterMCR.hpp"
#include "PX2EventWorld.hpp"
#include "PX2Float2.hpp"

// 去除OIS中的警告
#pragma warning(disable : 4100)
#pragma warning(disable : 4512)

#include "OISInputManager.h"
#include "OISException.h"
#include "OISKeyboard.h"
#include "OISMouse.h"
#include "OISJoyStick.h"
#include "OISEvents.h"

namespace PX2
{

	/// OIS事件空间
	PX2_DECLARE_EVENT_BEGIN(OISEventSpace)

	PX2_EVENT(KeyPressed)
	PX2_EVENT(KeyReleased)
	PX2_EVENT(MouseMoved)
	PX2_EVENT(MousePressed)
	PX2_EVENT(MouseReleased)
	PX2_EVENT(JoyButtonPressed)
	PX2_EVENT(JoyButtonReleased)
	PX2_EVENT(JoyAxisMoved)
	PX2_EVENT(JoyPovMoved)
	PX2_EVENT(JoyVector3Moved)

	PX2_DECLARE_EVENT_END(OISEventSpace)

	/// OIS数据
	class OISEventData
	{
	public:
		OISEventData ()
			:
		keyCode(OIS::KC_UNASSIGNED),
			text(0)
		{
		}
		~OISEventData ()
		{
		}

		OIS::KeyCode keyCode;
		unsigned int text;

		OIS::MouseButtonID mouseID;
		OIS::MouseState mouseState;

		OIS::JoyStickState joyStickState;
	};

	/// OIS事件监听器类
	class OISEventListener : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener
	{
	public:
		OISEventListener() {}
		~OISEventListener() {}

		bool keyPressed (const OIS::KeyEvent &arg);
		bool keyReleased (const OIS::KeyEvent &arg); 
		bool mouseMoved (const OIS::MouseEvent &arg);
		bool mousePressed (const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool mouseReleased (const OIS::MouseEvent &arg, OIS::MouseButtonID id); 
		bool buttonPressed (const OIS::JoyStickEvent &arg, int button);
		bool buttonReleased (const OIS::JoyStickEvent &arg, int button);
		bool axisMoved (const OIS::JoyStickEvent &arg, int axis);
		bool povMoved (const OIS::JoyStickEvent &arg, int pov);
		bool vector3Moved (const OIS::JoyStickEvent &arg, int index);
	};

	/// OIS事件适配器类
	class OISEventAdapter : public Singleton<OISEventAdapter>
	{
	public:
		OISEventAdapter ();
		~OISEventAdapter ();

		// 使用此函数添加窗口句柄
		void AddParam (int windowID);

		bool Initlize (int width, int height);
		bool Ternamate ();

		void Update ();

		OIS::InputManager *GetInputManager ();
		OIS::Keyboard *GetKeyboard ();
		OIS::Mouse *GetMouse ();
		OIS::JoyStick **GetJoyStick ();

		static Float2 CoordinateLeftToRight (Float2 xy, Float2 widthHeight);

	protected:
		float mWidth, mHeight;
		OIS::ParamList mParamList;
		OIS::InputManager *mInputManager;
		OIS::Keyboard *mKeyboard;
		OIS::Mouse *mMouse;
		OIS::JoyStick *mJoyStick[4];
		OISEventListener *mOISEventListener;
	};

	typedef Pointer0<OISEventAdapter> OISEventAdapterPtr;

}

#endif