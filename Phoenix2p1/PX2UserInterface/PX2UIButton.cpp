/*
*
* 文件名称	：	PX2UIButton.cpp
*
*/

#include "PX2UIButton.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2ScriptManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIButtonBase, UIButton);
PX2_IMPLEMENT_STREAM(UIButton);
PX2_IMPLEMENT_FACTORY(UIButton);
PX2_IMPLEMENT_DEFAULT_NAMES(UIButtonBase, UIButton);

//----------------------------------------------------------------------------
UIButton::UIButton ()
{
	SetName("UIButton");

	UIPicBox *picNormal = new0 UIPicBox();
	picNormal->SetName("Normal");
	picNormal->SetPicBoxType(UIPicBox::PBT_NINE);
	picNormal->SetTexture("Data/engine/common.xml", "buttonNormal");

	UIPicBox *picOver = new0 UIPicBox();
	picOver->SetName("Over");
	picOver->SetPicBoxType(UIPicBox::PBT_NINE);
	picOver->SetTexture("Data/engine/common.xml", "buttonOver");

	UIPicBox *picDown = new0 UIPicBox();
	picDown->SetName("Down");
	picDown->SetPicBoxType(UIPicBox::PBT_NINE);
	picDown->SetTexture("Data/engine/common.xml", "buttonDown");

	SetPicBox(BS_NORMAL, picNormal);
	SetPicBox(BS_OVER, picOver);
	SetPicBox(BS_DOWN, picDown);

	SetButtonState(BS_NORMAL);
}
//----------------------------------------------------------------------------
UIButton::~UIButton ()
{
}
//----------------------------------------------------------------------------
void UIButton::OnEvent (Event *event)
{
	if (InputEventSpace::IsEqual(event, InputEventSpace::TouchReleased))
	{
		if (GetButtonState() == BS_DOWN)
		{
			SetButtonState(BS_NORMAL);
		}
	}
}
//----------------------------------------------------------------------------
void UIButton::OnPressed ()
{
	if ("" == mScriptHandler)
		return;

	char str[256];
	sprintf(str, "%s(%d)", mScriptHandler.c_str(), 1);
	PX2_SM.CallString(str);
}
//----------------------------------------------------------------------------
void UIButton::OnReleased ()
{
	if ("" == mScriptHandler)
		return;

	char str[256];
	sprintf(str, "%s(%d)", mScriptHandler.c_str(), 2);
	PX2_SM.CallString(str);
}
//----------------------------------------------------------------------------
void UIButton::OnChildPicked (int info, Movable *child)
{
	ButtonState state = GetButtonState();

	if (1 == info)
	{
		if (state==BS_NORMAL || state==BS_OVER)
		{
			SetButtonState(BS_DOWN);
			OnPressed();
		}
	}
	else if (1 == info)
	{
		ButtonState state = GetButtonState();

		if (state == BS_DOWN)
		{
			SetButtonState(BS_NORMAL);
			OnReleased();
		}
	}
}
//----------------------------------------------------------------------------
void UIButton::OnNotPicked (int info)
{
	PX2_UNUSED(info);
	SetButtonState(BS_NORMAL);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIButton::UIButton (LoadConstructor value)
	:
UIButtonBase(value)
{
}
//----------------------------------------------------------------------------
void UIButton::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIButtonBase::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(UIButton, source);
}
//----------------------------------------------------------------------------
void UIButton::Link (InStream& source)
{
	UIButtonBase::Link(source);
}
//----------------------------------------------------------------------------
void UIButton::PostLink ()
{
	UIButtonBase::PostLink();
}
//----------------------------------------------------------------------------
bool UIButton::Register (OutStream& target) const
{
	return UIButtonBase::Register(target);
}
//----------------------------------------------------------------------------
void UIButton::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIButtonBase::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(UIButton, target);
}
//----------------------------------------------------------------------------
int UIButton::GetStreamingSize () const
{
	int size = UIButtonBase::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------
