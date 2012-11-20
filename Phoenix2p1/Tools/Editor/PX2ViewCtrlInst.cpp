/*
*
* ÎÄ¼þÃû³Æ	£º	PX2ViewCtrlInst.cpp
*
*/

#include "PX2ViewCtrlInst.hpp"
#include "PX2ViewCtrl.hpp"
#include "PX2GViewCtrl.hpp"
#include "PX2EditSystem.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
ViewCtrlInst::ViewCtrlInst()
	:
mViewCtrl(0)
{
}
//-----------------------------------------------------------------------------
ViewCtrlInst::~ViewCtrlInst()
{
	if (mViewCtrl)
	{
		delete0(mViewCtrl);
	}
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::DoSelection (PX2::Renderer *renderer, 
	const PX2::Vector2f &point,	SelectionMode mode)
{
	APoint origin;
	AVector direction;

	float x = renderer->GetWidth() * point.X();
	float y = renderer->GetHeight() * (1.0f - point.Y());

	renderer->GetPickRay((int)x, (int)y, origin, direction);

	Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();

	ActorPicker actorPicker;
	actorPicker.Execute(scene, origin, direction, 0.0f, Mathf::MAX_REAL);

	if (actorPicker.Records.size() > 0)
	{
		const ActorPickRecord &record = actorPicker.GetClosestToZero();
		mSelectPoint = origin + direction*record.T;

		if (mode == SM_REPLACE)
		{
			if (!EditSystem::GetSingleton().GetSelection()->IsActorIn(record.Intersected))
			{
				EditSystem::GetSingleton().GetSelection()->Clear();
				EditSystem::GetSingleton().GetSelection()->AddActor(record.Intersected);
			}
		}
		else if (mode == SM_ADD)
		{
			EditSystem::GetSingleton().GetSelection()->AddActor(record.Intersected);
		}
		else if (mode == SM_SUBTRACT)
		{
			EditSystem::GetSingleton().GetSelection()->RemoveActor(record.Intersected);
		}
	}
	else
	{
		if (EditSystem::GetSingleton().GetSelection()->GetActorQuantity() > 0)
		{
			if (mode == SM_REPLACE)
			{
				EditSystem::GetSingleton().GetSelection()->Clear();
			}
		}
	}
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::DoSelection (PX2::Renderer *renderer, 
	const PX2::Vector2f &topLeft,
	const PX2::Vector2f &bottonRight, 
	SelectionMode mode)
{
}
//-----------------------------------------------------------------------------
PX2::APoint ViewCtrlInst::CalculateSelectPoint (PX2::Renderer *renderer,
	const PX2::Vector2f &point)
{
	APoint origin;
	AVector direction;

	float x = renderer->GetWidth() * point.X();
	float y = renderer->GetHeight() * (1.0f - point.Y());

	renderer->GetPickRay((int)x, (int)y, origin, direction);

	Scene *scene = EditSystem::GetSingleton().GetEditMap()->GetScene();

	ActorPicker actorPicker;
	actorPicker.Execute(scene, origin, direction, 0.0f, Mathf::MAX_REAL);

	mSelectPoint = PX2::APoint::ORIGIN;

	if (actorPicker.Records.size() > 0)
	{
		const ActorPickRecord &record = actorPicker.GetClosestToZero();

		mSelectPoint = origin + direction*record.T;
	}

	return mSelectPoint;
}
//-----------------------------------------------------------------------------
PX2::APoint ViewCtrlInst::GetSelectPoint ()
{
	return mSelectPoint;
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::SetInteractionMode (InteractionMode im)
{
	if (im == mInteractionMode)
		return;

	switch (mInteractionMode)
	{
	case IM_SELECT:
		ExitSelectMode();
		break;
	case IM_TRANSLATE:
		ExitTranslateMode();
		break;
	case IM_ROLATE:
		ExitRolateMode();
		break;
	case IM_SCALE:
		ExitScaleMode();
		break;
	default:
		break;
	}

	mInteractionMode = im;

	switch (mInteractionMode)
	{
	case IM_SELECT:
		EnterSelectMode();
		break;
	case IM_TRANSLATE:
		EnterTranslateMode();
		break;
	case IM_ROLATE:
		EnterRolateMode();
		break;
	case IM_SCALE:
		EnterScaleMode();
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleLeftDown (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	mViewCtrl->HandleLeftDown(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleLeftUp (RenderViewWindow *win,
	wxMouseEvent &e)
{
	mViewCtrl->HandleLeftUp(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleMiddleDown (RenderViewWindow *win,
	wxMouseEvent &e)
{
	mViewCtrl->HandleMiddleDown(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleMiddleUp (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	mViewCtrl->HandleMiddleUp(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleMouseWheel (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	mViewCtrl->HandleMouseWheel(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleRightDown (RenderViewWindow *win,
	wxMouseEvent &e)
{
	mViewCtrl->HandleRightDown(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleRightUp (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	mViewCtrl->HandleRightUp(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::HandleMotion (RenderViewWindow *win, 
	wxMouseEvent &e)
{
	mViewCtrl->HandleMotion(win, e);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::SwitchPaneController (ViewCtrl *ctrl)
{
	if (mViewCtrl)
	{
		delete0(mViewCtrl);
		mViewCtrl = 0;
	}

	mViewCtrl = ctrl;
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::EnterSelectMode ()
{
	SwitchPaneController(new0 GViewCtrl(this));

	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_SELECT);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::ExitSelectMode ()
{
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::EnterTranslateMode ()
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_TRANSLATE);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::ExitTranslateMode ()
{
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::EnterRolateMode ()
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_ROLATE);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::ExitRolateMode ()
{
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::EnterScaleMode ()
{
	EditSystem::GetSingleton().SetEditMode(EditSystem::EM_SCALE);
}
//-----------------------------------------------------------------------------
void ViewCtrlInst::ExitScaleMode ()
{
}
//-----------------------------------------------------------------------------