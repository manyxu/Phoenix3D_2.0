/*
*
* ÎÄ¼þÃû³Æ	£º	PX2UIElement.cpp
*
*/

#include "PX2UIElement.hpp"
#include "PX2UIManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, UIElement);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, UIElement);

//----------------------------------------------------------------------------
UIElement::UIElement (UIElement *parent, int ID, const std::string &name,
					  float deltaX, float deltaY, 
					  float width, float height,
					  bool enable, 
					  bool visible,
					  int tableIndex, 
					  bool tableEnable)
					  :
mParent(parent),
mID(ID),
mEnable(enable),
mVisible(visible),
mMouseIn(false),
mTableIndex(tableIndex),
mTableEnable(tableEnable),
mOnFocus(false),
mShowLevel(0),
mPosition(deltaX, deltaY),
mSize(Float2(width, height)),
mUIType(UT_QUANTITY)
{
	SetName(name);
}
//----------------------------------------------------------------------------
UIElement::~UIElement ()
{
}
//----------------------------------------------------------------------------
UIElement::UIType UIElement::GetUIType ()
{
	return mUIType;
}
//----------------------------------------------------------------------------
void UIElement::SetID (int ID)
{
	mID = ID;
}
//----------------------------------------------------------------------------
int UIElement::GetID ()
{
	return mID;
}
//----------------------------------------------------------------------------
void UIElement::SetEnable (bool enable)
{
	mEnable = enable;
}
//----------------------------------------------------------------------------
bool UIElement::IsEnable ()
{
	return mEnable;
}
//----------------------------------------------------------------------------
void UIElement::SetVisible (bool visible)
{
	mVisible = visible;
}
//----------------------------------------------------------------------------
bool UIElement::IsVisible ()
{
	return mVisible;
}
//----------------------------------------------------------------------------
void UIElement::SetFocus (bool focus)
{
	mOnFocus = focus;
}
//----------------------------------------------------------------------------
bool UIElement::IsOnFocus ()
{
	return mOnFocus;
}
//----------------------------------------------------------------------------
bool UIElement::IsMouseIn ()
{
	return mMouseIn;
}
//----------------------------------------------------------------------------
Float2 UIElement::GetMousePosOverSize ()
{
	return mMousePosOverSize;
}
//----------------------------------------------------------------------------
void UIElement::SetPosition (float offsetParentX, float offsetParentY)
{
	mOffsetParent[0] = offsetParentX;
	mOffsetParent[1] = offsetParentY;

	if (mParent)
	{
		mPosition[0] = mParent->GetPosition()[0] + mOffsetParent[0];
		mPosition[1] = mParent->GetPosition()[1] + mOffsetParent[1];
	}
	else
		mPosition = mOffsetParent;
}
//----------------------------------------------------------------------------
void UIElement::Move (float deltaX, float deltaY)
{
	mOffsetParent[0] += deltaX;
	mOffsetParent[1] += deltaY;

	if (mParent)
	{
		mPosition[0] = mParent->GetPosition()[0] + mOffsetParent[0];
		mPosition[1] = mParent->GetPosition()[1] + mOffsetParent[1];
	}
	else
		mPosition = mOffsetParent;
}
//----------------------------------------------------------------------------
const Float2 UIElement::GetPosition () const
{
	return mPosition;
}
//----------------------------------------------------------------------------
Float2 UIElement::GetOffsetParent ()
{
	return mOffsetParent;
}
//----------------------------------------------------------------------------
void UIElement::SetSize (float width, float height)
{
	mSize[0] = width;
	mSize[1] = height;
}
//----------------------------------------------------------------------------
Float2 UIElement::GetSize ()
{
	return mSize;
}
//----------------------------------------------------------------------------
void UIElement::SetParent (UIElement *parent)
{
	mParent = parent;
}
//----------------------------------------------------------------------------
UIElement *UIElement::GetParent ()
{
	return mParent;
}
//----------------------------------------------------------------------------
void UIElement::SetShowLevel (int showLevel)
{
	mShowLevel = showLevel;
}
//----------------------------------------------------------------------------
int UIElement::GetShowLevel ()
{
	return mShowLevel;
}
//----------------------------------------------------------------------------
void UIElement::OnEvent (Event *event)
{
	JudgeMouseIn(event);
}
//----------------------------------------------------------------------------
void UIElement::GetVisibleSet (VisibleSet &set)
{
	PX2_UNUSED(set);
}
//----------------------------------------------------------------------------
void UIElement::Draw (Renderer *renderer)
{
	PX2_UNUSED(renderer);
}
//----------------------------------------------------------------------------
void UIElement::JudgeMouseIn (Event *event)
{
	if (OISEventSpace::IsEqual(event, OISEventSpace::MouseMoved))
	{
		OISEventData data = event->GetData<OISEventData>();

		float x = (float)data.mouseState.X.abs;
		float y = (float)data.mouseState.Y.abs;
		float wndWidth = UIManager::GetSingleton().GetWndWidth();
		float wndHeight = UIManager::GetSingleton().GetWndHeight();

		Float2 value = OISEventAdapter::CoordinateLeftToRight(Float2(x,y),
			Float2(wndWidth,wndHeight));

		mMousePos = value;
		mMousePosOverSize[0] = mMousePos[0]/mSize[0];
		mMousePosOverSize[1] = mMousePos[1]/mSize[1];

		if (value[0] >= mPosition[0] && value[1] >= mPosition[1] && 
			value[0] <= (mPosition[0]+mSize[0]) &&	value[1] <= (mPosition[1]+mSize[1]))
			mMouseIn = true;
		else
			mMouseIn = false;
	}
}
//----------------------------------------------------------------------------