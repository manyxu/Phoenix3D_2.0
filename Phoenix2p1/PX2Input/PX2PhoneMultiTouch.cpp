/*
*
* ÎÄ¼þÃû³Æ	£º	PX2PhoneMultiTouch.cpp
*
*/

#include "PX2PhoneMultiTouch.hpp"
#include "PX2PhoneInputManager.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PhoneMultiTouch::PhoneMultiTouch (InputManager* creator, bool buffered)
	:
MultiTouch(creator->GetInputSystemName(), buffered, 0, creator)
{
	static_cast<PhoneInputManager*>(mCreator)->SetMultiTouchUsed(true);
}
//----------------------------------------------------------------------------
PhoneMultiTouch::~PhoneMultiTouch ()
{
	static_cast<PhoneInputManager*>(mCreator)->SetMultiTouchUsed(false);
}
//----------------------------------------------------------------------------
void PhoneMultiTouch::Initialize()
{
}
//----------------------------------------------------------------------------
void PhoneMultiTouch::Capture()
{
}
//----------------------------------------------------------------------------