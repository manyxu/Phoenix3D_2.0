/*
*
* ÎÄ¼þÃû³Æ	£º	PX2InputEventListener.cpp
*
*/

#include "PX2InputEventListener.hpp"
#include "PX2InputEventAdapter.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
InputEventListener::InputEventListener ()
{
}
//----------------------------------------------------------------------------
InputEventListener::~InputEventListener ()
{
}
//----------------------------------------------------------------------------
bool InputEventListener::KeyPressed (const KeyEvent &arg)
{
	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(InputEventSpace::KeyPressed);

	InputEventData data;
	data.KCode = arg.Key;

	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);

	return true;
}
//----------------------------------------------------------------------------
bool InputEventListener::KeyReleased (const KeyEvent &arg)
{
	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(InputEventSpace::KeyReleased);

	InputEventData data;
	data.KCode = arg.Key;

	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);

	return true;
}
//----------------------------------------------------------------------------
bool InputEventListener::MouseMoved (const MouseEvent &arg)
{
	bool converted = InputEventAdapter::GetSingleton().IsConverted2Touch();
	const Sizef &winSize = InputManager::GetSingleton().GetSize();

	Event::EventType entType = InputEventSpace::MouseMoved;
	if (converted)
	{
		if (!arg.State.IsButtonDown(MBID_LEFT) 
			&& !arg.State.IsButtonDown(MBID_RIGHT)
			&& !arg.State.IsButtonDown(MBID_MIDDLE))
			return false;

		entType = InputEventSpace::TouchMoved;
	}

	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);

	InputEventData data;
	data.MState = arg.State;
	InputEventAdapter::CoordinateToPX2(data.MState.Y, winSize);
	if (converted)
	{
		data.TState.X = data.MState.X;
		data.TState.Y = data.MState.Y;
		data.TState.Z = data.MState.Z;
	}

	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);

	return true;
}
//----------------------------------------------------------------------------
bool InputEventListener::MousePressed (const MouseEvent &arg, 
	MouseButtonID id)
{
	bool converted = InputEventAdapter::GetSingleton().IsConverted2Touch();
	const Sizef &winSize = InputManager::GetSingleton().GetSize();

	Event::EventType entType = InputEventSpace::MousePressed;
	if (converted)
	{
		entType = InputEventSpace::TouchPressed;
	}

	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);

	InputEventData data;
	data.MButtonID = id;
	data.MState = arg.State;
	InputEventAdapter::CoordinateToPX2(data.MState.Y, winSize);
	if (converted)
	{
		data.TState.X = data.MState.X;
		data.TState.Y = data.MState.Y;
		data.TState.Z = data.MState.Z;
	}

	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);

	return true;
}
//----------------------------------------------------------------------------
bool InputEventListener::MouseReleased (const MouseEvent &arg,
	MouseButtonID id)
{
	bool converted = InputEventAdapter::GetSingleton().IsConverted2Touch();
	const Sizef &winSize = InputManager::GetSingleton().GetSize();

	Event::EventType entType = InputEventSpace::MouseReleased;
	if (converted)
	{
		entType = InputEventSpace::TouchReleased;
	}

	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);

	InputEventData data;
	data.MButtonID = id;
	data.MState = arg.State;
	InputEventAdapter::CoordinateToPX2(data.MState.Y, winSize);
	if (converted)
	{
		data.TState.X = data.MState.X;
		data.TState.Y = data.MState.Y;
		data.TState.Z = data.MState.Z;
	}

	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);

	return true;
}
//----------------------------------------------------------------------------
bool InputEventListener::TouchMoved (const MultiTouchEvent &arg)
{
	Event::EventType entType = InputEventSpace::TouchMoved;

	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);

	InputEventData data;
	data.TState = arg.State;
	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);

	return true;
}
//----------------------------------------------------------------------------
bool InputEventListener::TouchPressed (const MultiTouchEvent &arg)
{
	Event::EventType entType = InputEventSpace::TouchPressed;

	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);

	InputEventData data;
	data.TState = arg.State;
	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);

	return true;
}
//----------------------------------------------------------------------------
bool InputEventListener::TouchReleased (const MultiTouchEvent &arg)
{
	Event::EventType entType = InputEventSpace::TouchReleased;

	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);

	InputEventData data;
	data.TState = arg.State;
	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);

	return true;
}
//----------------------------------------------------------------------------
bool InputEventListener::TouchCancelled (const MultiTouchEvent &arg)
{
	Event::EventType entType = InputEventSpace::TouchCancelled;

	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);

	InputEventData data;
	data.TState = arg.State;
	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);

	return true;
}
//----------------------------------------------------------------------------
void InputEventListener::TouchMoved(int num, int ids[], float xs[], float ys[])
{
	Sizef size = PX2_IEA.GetSize();

	Event::EventType entType = InputEventSpace::TouchMoved;
	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);
	InputEventData data;

	if (num > 0)
	{
		int id = ids[0];
		int x = (int)xs[0];
		int y = (int)ys[0];
		PX2_UNUSED(id);

#if defined __ANDROID__
		y = size.Height - y;
#endif

		data.TState.X.Absoulate = x;
		data.TState.X.IsAbsoulateOnly = true;
		data.TState.Y.Absoulate = y;
		data.TState.Y.IsAbsoulateOnly = true;
		data.TState.TouchTypes = MTET_MOVED;
	}

	for (int i=0; i<num; i++)
	{
		int id = ids[i];
		int x = (int)xs[0];
		int y = (int)ys[0];
		PX2_UNUSED(id);

#if defined __ANDROID__
		y = size.Height - y;
#endif

		MultiTouchState state;

		state.X.Absoulate = x;
		state.X.IsAbsoulateOnly = true;
		state.Y.Absoulate = y;
		state.Y.IsAbsoulateOnly = true;
		state.TouchTypes = MTET_MOVED;

		data.TStates.push_back(data.TState);
	}

	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void InputEventListener::TouchPressed(int num, int ids[], float xs[], float ys[])
{
	Sizef size = PX2_IEA.GetSize();

	Event::EventType entType = InputEventSpace::TouchPressed;
	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);
	InputEventData data;

	if (num > 0)
	{
		int id = ids[0];
		int x = (int)xs[0];
		int y = (int)ys[0];
		PX2_UNUSED(id);

#if defined __ANDROID__
		y = size.Height - y;
#endif

		data.TState.X.Absoulate = x;
		data.TState.X.IsAbsoulateOnly = true;
		data.TState.Y.Absoulate = y;
		data.TState.Y.IsAbsoulateOnly = true;
		data.TState.TouchTypes = MTET_PRESSED;
	}

	for (int i=0; i<num; i++)
	{
		int id = ids[i];
		int x = (int)xs[0];
		int y = (int)ys[0];
		PX2_UNUSED(id);

#if defined __ANDROID__
		y = size.Height - y;
#endif

		MultiTouchState state;

		state.X.Absoulate = x;
		state.X.IsAbsoulateOnly = true;
		state.Y.Absoulate = y;
		state.Y.IsAbsoulateOnly = true;
		state.TouchTypes = MTET_PRESSED;

		data.TStates.push_back(data.TState);
	}

	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void InputEventListener::TouchReleased(int num, int ids[], float xs[], float ys[])
{
	Sizef size = PX2_IEA.GetSize();

	Event::EventType entType = InputEventSpace::TouchReleased;
	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);
	InputEventData data;

	if (num > 0)
	{
		int id = ids[0];
		int x = (int)xs[0];
		int y = (int)ys[0];
		PX2_UNUSED(id);

#if defined __ANDROID__
		y = size.Height - y;
#endif

		data.TState.X.Absoulate = x;
		data.TState.X.IsAbsoulateOnly = true;
		data.TState.Y.Absoulate = y;
		data.TState.Y.IsAbsoulateOnly = true;
		data.TState.TouchTypes = MTET_RELEASED;
	}

	for (int i=0; i<num; i++)
	{
		int id = ids[i];
		int x = (int)xs[0];
		int y = (int)ys[0];
		PX2_UNUSED(id);

#if defined __ANDROID__
		y = size.Height - y;
#endif

		MultiTouchState state;

		state.X.Absoulate = x;
		state.X.IsAbsoulateOnly = true;
		state.Y.Absoulate = y;
		state.Y.IsAbsoulateOnly = true;
		state.TouchTypes = MTET_RELEASED;

		data.TStates.push_back(data.TState);
	}

	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void InputEventListener::TouchCancelled(int num, int ids[], float xs[], float ys[])
{
	Sizef size = PX2_IEA.GetSize();

	Event::EventType entType = InputEventSpace::TouchCancelled;
	Event *ent = 0;
	ent = InputEventSpace::CreateEventX(entType);
	InputEventData data;

	if (num > 0)
	{
		int id = ids[0];
		int x = (int)xs[0];
		int y = (int)ys[0];
		PX2_UNUSED(id);

#if defined __ANDROID__
		y = size.Height - y;
#endif

		data.TState.X.Absoulate = x;
		data.TState.X.IsAbsoulateOnly = true;
		data.TState.Y.Absoulate = y;
		data.TState.Y.IsAbsoulateOnly = true;
		data.TState.TouchTypes = MTET_CANCELLED;
	}

	for (int i=0; i<num; i++)
	{
		int id = ids[i];
		int x = (int)xs[0];
		int y = (int)ys[0];
		PX2_UNUSED(id);

#if defined __ANDROID__
		y = size.Height - y;
#endif

		MultiTouchState state;

		state.X.Absoulate = x;
		state.X.IsAbsoulateOnly = true;
		state.Y.Absoulate = y;
		state.Y.IsAbsoulateOnly = true;
		state.TouchTypes = MTET_CANCELLED;

		data.TStates.push_back(data.TState);
	}

	ent->SetData<InputEventData>(data);

	EventWorld::GetSingleton().BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void InputEventListener::KeypadMsg (bool back, bool menu)
{
}
//----------------------------------------------------------------------------