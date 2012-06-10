/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIButton.cpp
*
*/

#include "PX2UIButton.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIButtonBase, UIButton);
PX2_IMPLEMENT_DEFAULT_NAMES(UIButtonBase, UIButton);

//----------------------------------------------------------------------------
UIButton::UIButton (UIElement *parent, int ID, const std::string &name,
		  const std::string &normal,
		  const std::string &mouseOver,
		  const std::string &mouseDown,
		  const std::string &mouseDisabled,
		  const std::string &text,
		  float deltaX, float deltaY,
		  float width,	float height,
		  bool visible,
		  int tableIndex,
		  bool tableEnable,
		  bool bPushed)
		  :
UIButtonBase(parent, ID, name, normal, mouseOver, mouseDown, mouseDisabled,
			 text, deltaX, deltaY, width, height, visible, tableIndex, 
			 tableEnable)
{
	mUIType = UT_BUTTON;
}
//----------------------------------------------------------------------------
UIButton::~UIButton ()
{
}
//----------------------------------------------------------------------------