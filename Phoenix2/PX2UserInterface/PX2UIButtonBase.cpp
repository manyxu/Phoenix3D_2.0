/*
*
* ÎÄ¼şÃû³Æ	£º	PX2UIButtonBase.cpp
*
*/

#include "PX2UIButtonBase.hpp"
#include "PX2UIManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIElement, UIButtonBase);
PX2_IMPLEMENT_DEFAULT_NAMES(UIElement, UIButtonBase);

//----------------------------------------------------------------------------
UIButtonBase::UIButtonBase (UIElement *parent, int ID, std::string name,
							const std::string &normal,
							const std::string &mouseOver,
							const std::string &mouseDown,
							const std::string &disabled,
							const std::string &text,
							float deltaX,
							float deltaY,
							float width,
							float height,
							bool visible,
							int tableIndex,
							bool tableEnable)
							:
UIElement(parent, ID, name, deltaX, deltaY, width, height, false, visible, 
		  tableIndex, tableEnable)
{
	int nextID = UIManager::GetSingleton().GetNextID();
	std::string elementName = Help::IntToString(nextID);
	mPicNormal = new0 UIPictureBox(this, nextID, elementName, normal, 
		Float4(1.0f,1.0f,1.0f,1.0f), deltaX, deltaY, width, height, visible);

	nextID = UIManager::GetSingleton().GetNextID();
	elementName = Help::IntToString(nextID);
	mPicMouseOver = new0 UIPictureBox(this, nextID, elementName, mouseOver,
		Float4(1.0f,1.0f,1.0f,1.0f), deltaX, deltaY, width, height, visible);
	
	nextID = UIManager::GetSingleton().GetNextID();
	elementName = Help::IntToString(nextID);
	mPicMouseDown = new0 UIPictureBox(this, nextID, elementName, mouseDown,
		Float4(1.0f,1.0f,1.0f,1.0f), deltaX, deltaY, width, height, visible);

	nextID = UIManager::GetSingleton().GetNextID();
	elementName = Help::IntToString(nextID);
	mPicDisabled = new0 UIPictureBox(this, nextID, elementName, disabled,
		Float4(1.0f,1.0f,1.0f,1.0f), deltaX, deltaY, width, height, visible);

	mButtonState = BS_NORMAL;

	PX2_UNUSED(text);
}
//----------------------------------------------------------------------------
UIButtonBase::~UIButtonBase()
{
	mPicNormal = 0;
	mPicMouseOver = 0;
	mPicMouseDown = 0;
	mPicDisabled = 0;
}
//----------------------------------------------------------------------------
void UIButtonBase::SetPosition (float offsetParentX, float offsetParentY)
{
	UIElement::SetPosition(offsetParentX, offsetParentY);

	if (mPicNormal)
		mPicNormal->Move(0.0f, 0.0f);

	if (mPicMouseOver)
		mPicMouseOver->Move(0.0f, 0.0f);

	if (mPicMouseDown)
		mPicMouseDown->Move(0.0f, 0.0f);

	if (mPicDisabled)
		mPicDisabled->Move(0.0f, 0.0f);
}
//----------------------------------------------------------------------------
void UIButtonBase::SetSize(float width, float height)
{
	UIElement::SetSize(width, height);

	if (mPicNormal)
		mPicNormal->SetSize(width, height);

	if (mPicMouseOver)
		mPicMouseOver->SetSize(width, height);

	if (mPicMouseDown)
		mPicMouseDown->SetSize(width, height);

	if (mPicDisabled)
		mPicDisabled->SetSize(width, height);
}
//----------------------------------------------------------------------------
void UIButtonBase::Move (float deltaX, float deltaY)
{
	UIElement::Move(deltaX, deltaY);

	if (mPicNormal)
		mPicNormal->Move(0.0f, 0.0f);

	if (mPicMouseOver)
		mPicMouseOver->Move(0.0f, 0.0f);

	if (mPicMouseDown)
		mPicMouseDown->Move(0.0f, 0.0f);

	if (mPicDisabled)
		mPicDisabled->Move(0.0f, 0.0f);
}
//----------------------------------------------------------------------------
UIButtonBase::ButtonState UIButtonBase::GetButtonState() const
{
	return mButtonState;
}
//----------------------------------------------------------------------------
void UIButtonBase::SetButtonState (ButtonState buttonState)
{
	mButtonState = buttonState;
}
//----------------------------------------------------------------------------
void UIButtonBase::SetPictureBox(UIButtonBase::ButtonState state, 
								 std::string textureName)
{
	int nextID = UIManager::GetSingleton().GetNextID();
	std::string elementName = Help::IntToString(nextID);

	UIPictureBox *picBox = 0;
	picBox = new0 UIPictureBox(this, nextID, elementName, textureName,
		Float4(1.0f,1.0f,1.0f,1.0f));

	if (!picBox)
		return;

	picBox->SetPosition(0.0f, 0.0f);
	picBox->SetSize(GetSize()[0], GetSize()[1]);

	switch (state)
	{
	case BS_NORMAL:
		mPicNormal = picBox;
		break;
	case BS_MOUSEOVER:
		mPicMouseOver = picBox;
		break;
	case BS_MOUSEDOWN:
		mPicMouseDown = picBox;
		break;
	case BS_DISABLED:
		mPicDisabled = picBox;
	default:
		break;
	}
}
//----------------------------------------------------------------------------
void UIButtonBase::SetPictureBox(UIButtonBase::ButtonState state, 
								 UIPictureBox *pictureBox)
{
	switch (state)
	{
	case BS_NORMAL:
		mPicNormal = pictureBox;
		break;
		
	case BS_MOUSEOVER:
		mPicMouseOver = pictureBox;
		break;

	case BS_MOUSEDOWN:
		mPicMouseDown = pictureBox;

	case BS_DISABLED:
		mPicDisabled = pictureBox;
		break;

	default:
		break;
	}

	if (pictureBox)
	{
		pictureBox->SetPosition(0.0f, 0.0f);
		pictureBox->SetSize(GetSize()[0], GetSize()[1]);
		pictureBox->SetParent(this);
	}
}
//----------------------------------------------------------------------------
UIPictureBox *UIButtonBase::GetPictureBoxAtCurState() const
{
	switch (mButtonState)
	{
	case BS_NORMAL:
		return mPicNormal;

	case BS_MOUSEOVER:
		if (mPicMouseOver)
			return mPicMouseOver;
		else
			return mPicNormal;

	case BS_MOUSEDOWN:
		if (mPicMouseDown)
			return mPicMouseDown;
		else
			return mPicNormal;

	case BS_DISABLED:
		if (mPicDisabled)
			return mPicDisabled;
		else
			return mPicNormal;

	default:
		return 0;
	}
}
//----------------------------------------------------------------------------
UIPictureBox *UIButtonBase::GetPictureBox(UIButtonBase::ButtonState state)
const
{
	switch (state)
	{
	case BS_NORMAL:
		return mPicNormal;

	case BS_MOUSEOVER:
		if (mPicMouseOver)
			return mPicMouseOver;
		else
			return mPicNormal;

	case BS_MOUSEDOWN:
		if (mPicMouseDown)
			return mPicMouseDown;
		else
			return mPicNormal;

	case BS_DISABLED:
		if (mPicDisabled)
			return mPicDisabled;
		else
			return mPicNormal;

	default:
		return 0;
	}
}
//----------------------------------------------------------------------------
void UIButtonBase::OnEvent (Event *event)
{
	UIElement::OnEvent(event);

	if (IsMouseIn())
	{
		bool leftPressed = false;
		bool leftReleased = false;

		if (OISEventSpace::IsEqual(event, OISEventSpace::MousePressed))
		{
			OISEventData data = event->GetData<OISEventData>();

			if (data.mouseID == OIS::MB_Left)
				leftPressed = true;
		}
		else if (OISEventSpace::IsEqual(event, OISEventSpace::MouseReleased))
		{
			OISEventData data = event->GetData<OISEventData>();

			if (data.mouseID == OIS::MB_Left)
				leftReleased = true;
		}

		ButtonState buttonState = GetButtonState();

		switch (buttonState)
		{
		case BS_NORMAL:
			if (!leftPressed)
				SetButtonState(BS_MOUSEOVER);
			break;
		case BS_MOUSEOVER:
			if (leftPressed)
				SetButtonState(BS_MOUSEDOWN);
			break;
		case BS_MOUSEDOWN:
			if (leftReleased)
				SetButtonState(BS_MOUSEOVER);
			break;
		default:
			break;
		}
	} // end if (IsMouseIn())
	else
	{
		SetButtonState(BS_NORMAL);
	}
}
//----------------------------------------------------------------------------
void UIButtonBase::GetVisibleSet (VisibleSet &set)
{
	GetPictureBoxAtCurState()->GetVisibleSet(set);
}
//----------------------------------------------------------------------------
void UIButtonBase::Draw (Renderer *renderer)
{
	UIPictureBox *picBox = 0;
	picBox = GetPictureBoxAtCurState();
	if (picBox)
		picBox->Draw(renderer);
}
//----------------------------------------------------------------------------