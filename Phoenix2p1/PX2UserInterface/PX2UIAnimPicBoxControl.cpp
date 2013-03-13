/*
*
* 文件名称	：	PX2UIAnimPicBoxCtrl.cpp
*
*/

#include "PX2UIAnimPicBoxControl.hpp"
#include "PX2UIAnimPicBox.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, UIAnimPicBoxControl);
PX2_IMPLEMENT_STREAM(UIAnimPicBoxControl);
PX2_IMPLEMENT_FACTORY(UIAnimPicBoxControl);
PX2_IMPLEMENT_DEFAULT_NAMES(Controller, UIAnimPicBoxControl);

//----------------------------------------------------------------------------
UIAnimPicBoxControl::UIAnimPicBoxControl ()
{
	Repeat = RT_WRAP;
}
//----------------------------------------------------------------------------
UIAnimPicBoxControl::~UIAnimPicBoxControl ()
{
}
//----------------------------------------------------------------------------
bool UIAnimPicBoxControl::Update (double applicationTime)
{
	if (applicationTime == 0.0f)
		return true;

	if (!Controller::Update(applicationTime))
	{
		return false;
	}

	double ctrlTime = Controller::GetControlTime(applicationTime);
	double elapsedTime = GetElapsedTime();

	UIAnimPicBox *picBox = DynamicCast<UIAnimPicBox>(mObject);
	if (!picBox)
		return false;

	int animIndex = (int)(ctrlTime/picBox->GetIntervalTime());

	picBox->SetActiveIndex(animIndex);

	return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化
//----------------------------------------------------------------------------
UIAnimPicBoxControl::UIAnimPicBoxControl (LoadConstructor value)
	:
Controller(value)
{
}
//----------------------------------------------------------------------------
void UIAnimPicBoxControl::Load (InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);

	PX2_END_DEBUG_STREAM_LOAD(UIAnimPicBoxControl, source);
}
//----------------------------------------------------------------------------
void UIAnimPicBoxControl::Link (InStream& source)
{
	Controller::Link(source);
}
//----------------------------------------------------------------------------
void UIAnimPicBoxControl::PostLink ()
{
	Controller::PostLink();
}
//----------------------------------------------------------------------------
bool UIAnimPicBoxControl::Register (OutStream& target) const
{
	if (Controller::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UIAnimPicBoxControl::Save (OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);

	PX2_END_DEBUG_STREAM_SAVE(UIAnimPicBoxControl, target);
}
//----------------------------------------------------------------------------
int UIAnimPicBoxControl::GetStreamingSize () const
{
	int size = Controller::GetStreamingSize();
	return size;
}
//----------------------------------------------------------------------------
