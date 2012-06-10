/*
*
* ÎÄ¼þÃû³Æ	£º	PX2OISEventAdapter.cpp
*
*/

#include "PX2OISEventAdapter.hpp"
#include <iostream>
#include <sstream>
using namespace PX2;
using namespace OIS;

PX2_IMPLEMENT_EVENT(OISEventSpace)
//----------------------------------------------------------------------------
bool OISEventListener::keyPressed (const KeyEvent &arg)
{
	Event *event = 0;
	event = OISEventSpace::CreateEvent(OISEventSpace::KeyPressed);

	if (!event)
		return false;

	OISEventData data;
	data.keyCode = arg.key;
	data.text = arg.text;
	event->SetData<OISEventData>(data);

	if (EventWorld::GetSingletonPtr())
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	return true;
}
//----------------------------------------------------------------------------
bool OISEventListener::keyReleased (const KeyEvent &arg) 
{
	Event *event = 0;
	event = OISEventSpace::CreateEvent(OISEventSpace::KeyReleased);

	if (!event)
		return false;

	OISEventData data;
	data.keyCode = arg.key;
	data.text = arg.text;
	event->SetData<OISEventData>(data);

	if (EventWorld::GetSingletonPtr())
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	return true;
}
//----------------------------------------------------------------------------
bool OISEventListener::mouseMoved (const MouseEvent &arg)
{
	Event *event = 0;
	event = OISEventSpace::CreateEvent(OISEventSpace::MouseMoved);

	if (!event)
		return false;

	OISEventData data;
	data.mouseState = arg.state;
	event->SetData<OISEventData>(data);

	if (EventWorld::GetSingletonPtr())
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	return true;
}
//----------------------------------------------------------------------------
bool OISEventListener::mousePressed (const MouseEvent &arg, MouseButtonID id)
{
	Event *event = 0;
	event = OISEventSpace::CreateEvent(OISEventSpace::MousePressed);

	if (!event)
		return false;

	OISEventData data;
	data.mouseID = id;
	data.mouseState = arg.state;
	event->SetData<OISEventData>(data);

	if (EventWorld::GetSingletonPtr())
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	return true;
}
//----------------------------------------------------------------------------
bool OISEventListener::mouseReleased (const MouseEvent &arg, MouseButtonID id) 
{
	Event *event = 0;
	event = OISEventSpace::CreateEvent(OISEventSpace::MouseReleased);

	if (!event)
		return false;

	OISEventData data;
	data.mouseID = id;
	data.mouseState = arg.state;
	event->SetData<OISEventData>(data);

	if (EventWorld::GetSingletonPtr())
		EventWorld::GetSingleton().BroadcastingLocalEvent(event);

	return true;
}
//----------------------------------------------------------------------------
bool OISEventListener::buttonPressed (const JoyStickEvent &arg, int button)
{
	PX2_UNUSED(arg);
	PX2_UNUSED(button);
	return true;
}
//----------------------------------------------------------------------------
bool OISEventListener::buttonReleased (const JoyStickEvent &arg, int button)
{
	PX2_UNUSED(arg);
	PX2_UNUSED(button);
	return true;
}
//----------------------------------------------------------------------------
bool OISEventListener::axisMoved (const JoyStickEvent &arg, int axis)
{
	PX2_UNUSED(arg);
	PX2_UNUSED(axis);
	return true;
}
//----------------------------------------------------------------------------
bool OISEventListener::povMoved (const JoyStickEvent &arg, int pov)
{
	PX2_UNUSED(arg);
	PX2_UNUSED(pov);
	return true;
}
//----------------------------------------------------------------------------
bool OISEventListener::vector3Moved (const JoyStickEvent &arg, int index)
{
	PX2_UNUSED(arg);
	PX2_UNUSED(index);
	return true;
}
//----------------------------------------------------------------------------
OISEventAdapter::OISEventAdapter ()
{
	mOISEventListener = new0 OISEventListener();
	mInputManager = 0;
	mKeyboard = 0 ;
	mMouse = 0;
	mWidth = 1024;
	mHeight = 768;

	mJoyStick[0] = 0;
	mJoyStick[1] = 0;
	mJoyStick[2] = 0;
	mJoyStick[3] = 0;
}
//----------------------------------------------------------------------------
OISEventAdapter::~OISEventAdapter ()
{
	if (mOISEventListener)
		delete0 (mOISEventListener);
}
//----------------------------------------------------------------------------
void OISEventAdapter::AddParam (int windowID)
{
#if defined OIS_WIN32_PLATFORM
	std::ostringstream wnd;
	wnd << (size_t)windowID;

	mParamList.insert(std::make_pair(std::string("WINDOW"), wnd.str()));
	mParamList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	mParamList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	// ToDo
#elif defined OIS_APPLE_PLATFORM
	// ToDo
#endif
}
//----------------------------------------------------------------------------
bool OISEventAdapter::Initlize (int width, int height)
{
	mInputManager = InputManager::createInputSystem(mParamList);
	mInputManager->enableAddOnFactory(InputManager::AddOn_All);

	DeviceList list = mInputManager->listFreeDevices();

	mKeyboard = (Keyboard*)mInputManager->createInputObject(OISKeyboard, true);
	mKeyboard->setEventCallback(mOISEventListener);

	mMouse = (Mouse*)mInputManager->createInputObject(OISMouse, true);
	mMouse->setEventCallback(mOISEventListener);
	const MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
	mWidth = (float)width; 
	mHeight = (float)height;

	int numSticks = mInputManager->getNumberOfDevices(OISJoyStick);
	if (numSticks > 4)
		numSticks = 4;

	for (int i=0; i<numSticks; ++i)
	{
		mJoyStick[i] = (JoyStick*)mInputManager->createInputObject(OISJoyStick, true);
		mJoyStick[i]->setEventCallback(mOISEventListener);
	}

	return true;
}
//----------------------------------------------------------------------------
bool OISEventAdapter::Ternamate ()
{
	if (mInputManager)
		InputManager::destroyInputSystem(mInputManager);

	return true;
}
//----------------------------------------------------------------------------
void OISEventAdapter::Update ()
{
	if (mKeyboard)
		mKeyboard->capture();

	if (mMouse)
		mMouse->capture();

	for	(int i = 0; i<4; ++i)
	{
		if (mJoyStick[i])
		{
			mJoyStick[i]->capture();
		}
	}
}
//----------------------------------------------------------------------------
OIS::InputManager *OISEventAdapter::GetInputManager ()
{
	return mInputManager;
}
//----------------------------------------------------------------------------
OIS::Keyboard *OISEventAdapter::GetKeyboard ()
{
	return mKeyboard;
}
//----------------------------------------------------------------------------
OIS::Mouse *OISEventAdapter::GetMouse ()
{
	return mMouse;
}
//----------------------------------------------------------------------------
OIS::JoyStick **OISEventAdapter::GetJoyStick ()
{
	return mJoyStick;
}
//----------------------------------------------------------------------------
Float2 OISEventAdapter::CoordinateLeftToRight (Float2 xy, Float2 widthHeight)
{
	Float2 value;
	value[0] = xy[0];
	value[1] = widthHeight[1] - xy[1];

	return value;
}
//----------------------------------------------------------------------------